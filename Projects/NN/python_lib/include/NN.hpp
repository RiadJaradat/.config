#pragma once
#include <vector>
#include <math.h>
#include <random>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include "json.hpp"
#include <functional>
#include <map>

using floatvec = std::vector<float>;
using json = nlohmann::json;

namespace NN
{
    std::hash<std::string> hasher;

    float randomFloat(float min, float max)
    {
        static std::random_device rd;
        static std::mt19937 gen(0); // rd() as seed to get random res
        std::uniform_real_distribution<float> dist(min, max);

        return dist(gen);
    }

    void init_weights(floatvec &weights, size_t input_size)
    {
        float limit = std::sqrt(1.0f / input_size);

        for (auto &w : weights)
            w = randomFloat(-limit, limit);
    }

    double sigmoid(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }
    double sigmoid_derivative(double z)
    {
        z = sigmoid(z);
        return z * (1.0f - z);
    }
    double relu(double x)
    {
        return (x > 0.0f) ? x : 0.0f;
    }
    double relu_derivative(double z)
    {
        return (z > 0.0f) ? 1.0f : 0.0f;
    }

    float sum(floatvec a)
    {
        float res = 0.f;
        for (float n : a)
            res += n;

        return res;
    }

    floatvec operator*(floatvec a, floatvec b)
    {
        // if (a.size() != b.size())
        // std::cerr << "incorrect usage" << std::endl;

        floatvec res;

        for (size_t i = 0; i < a.size(); i++)
            res.push_back(a[i] * b[i]);

        return res;
    }

    floatvec tokenizer(const std::string &sentence)
    {
        floatvec tokens;

        std::stringstream ss(sentence);
        std::string word;

        while (ss >> word)
        {
            tokens.push_back(static_cast<float>(hasher(word) % 1000) / 1000.0f);
        }

        return tokens;
    }

    // this advanceTokenizer does not remove any of the texts value to get better results
    std::vector<float> advanceTokenizer(const std::string &text)
    {
        std::vector<float> result;
        result.reserve(text.size());

        for (unsigned char c : text)
        {
            result.push_back(static_cast<float>(c));
        }

        return result;
    }

    // converts tokens back into string!
    std::string advanceDetokenizer(const std::vector<float> &vec)
    {
        std::string result;
        result.reserve(vec.size());

        for (float f : vec)
        {
            result.push_back(static_cast<unsigned char>(f));
        }

        return result;
    }

    enum actType
    {
        Sigmoid,
        ReLU,
        // softmax
    };

    auto Run(actType funcType, double z, bool isDer = false)
    {
        switch (funcType)
        {
        case actType::Sigmoid:
        {
            return isDer? sigmoid_derivative(z): sigmoid(z);
        }
        case actType::ReLU:
        {
            return isDer? relu_derivative(z): relu(z);
        }
        default:
        {
            std::cout << "invalid" << std::endl;
            exit(1);
        }
        }
    }

    class Node
    {
    public:
        float bias;
        floatvec weights;

        Node()
        {
            bias = randomFloat(-0.5f, 0.5f);
        }

        float pass(const floatvec &inputs)
        {
            // FIX: ensure size match every time safely
            if (weights.size() != inputs.size())
            {
                weights.resize(inputs.size());
                init_weights(weights, inputs.size());
            }

            float res = 0.0f;

            for (size_t i = 0; i < inputs.size(); i++)
                res += inputs[i] * weights[i];

            return res + bias;
        }
    };

    class Layer
    {
    public:
        std::vector<Node> nodes;

        floatvec last_input;
        floatvec last_output;
        floatvec last_z;
        actType activate;

        Layer(size_t size, actType activation)
        {
            for (size_t i = 0; i < size; i++)
                nodes.emplace_back();

            activate = activation;
        }

        floatvec pass(const floatvec &inputs)
        {
            floatvec out;
            out.reserve(nodes.size());
            last_z.clear();

            for (auto &node : nodes)
            {
                float z = node.pass(inputs);
                last_z.push_back(z);
                out.push_back(Run(activate, z));
            }
            last_input = inputs;
            last_output = out;

            return out;
        }
    };

    class Network
    {
    public:
        std::vector<Layer> layers;

        Network()
        {
        }

        void addLayer(size_t size, actType act)
        {
            layers.emplace_back(size, act);
        }

        floatvec forward(const floatvec &input)
        {
            floatvec out = input;

            for (Layer &layer : layers)
                out = layer.pass(out);

            return out;
        }

        void backpropagation(const floatvec &target, float lr)
        {
            Layer &last = layers.back();

            floatvec error;
            error.reserve(last.last_output.size());

            // ----------------------------
            // 1. OUTPUT ERROR (MSE style)
            // ----------------------------
            for (size_t i = 0; i < last.last_output.size(); i++)
            {
                error.push_back(last.last_output[i] - target[i]);
            }

            // ----------------------------
            // 2. BACKWARD PASS
            // ----------------------------
            for (int l = (int)layers.size() - 1; l >= 0; l--)
            {
                Layer &layer = layers[l];

                floatvec next_error(layer.last_input.size(), 0.0f);

                for (size_t n = 0; n < layer.nodes.size(); n++)
                {
                    Node &node = layer.nodes[n];

                    float out = layer.last_output[n];

                    float d_act = Run(layer.activate, layer.last_z[n]);

                    float grad = error[n] * d_act;

                    for (size_t w = 0; w < node.weights.size(); w++)
                    {
                        float input = layer.last_input[w];
                        float old_w = node.weights[w];

                        // propagate error backward
                        next_error[w] += grad * old_w;

                        // update weights
                        node.weights[w] -= lr * grad * input;
                    }

                    // update bias
                    node.bias -= lr * grad;
                }

                error = next_error;
            }
        }

        // this is temperary and will be changed
        void trainLoop(
            std::vector<floatvec> &inputs,
            std::vector<floatvec> &targets,
            int epochs,
            float lr = 0.1f)
        {
            for (int e = 0; e < epochs; e++)
            {
                for (size_t i = 0; i < inputs.size(); i++)
                {
                    floatvec out = forward(inputs[i]);
                    backpropagation(targets[i], lr);
                }

                std::cout << e << " out of: " << epochs << std::endl;
            }
        }
        void trainLoop_map(std::map<floatvec, floatvec> &inputs_and_targets, int epochs, float lr = 0.1f)
        {
            for (int e = 0; e < epochs; e++)
            {
                for (auto &[input, target] : inputs_and_targets)
                {
                    floatvec out = forward(input);
                    backpropagation(target, lr);
                }

                std::cout << e << " out of: " << epochs << std::endl;
            }
        }

        // loads a network without extra setup
        void import_nn(const std::string &filename = "model.json")
        {
            std::ifstream file(filename);

            json j;
            file >> j;

            auto biases = j["biases"];
            auto weights = j["weights"];
            auto Layers = j["layers"];
            auto activation = j["acts"];
            int layer_count = j["layer_count"];

            // empty init

            layers.clear();

            for (size_t i = 0; i < layer_count; i++)
                addLayer(Layers[i], activation[i]);

            for (size_t i = 0; i < layers.size(); i++)
            {
                Layer &l = layers[i];
                for (size_t j = 0; j < l.nodes.size(); j++)
                {
                    Node &node = l.nodes[j];

                    node.bias = biases[i][j].get<float>();
                    node.weights = weights[i][j].get<floatvec>();
                }
            }
        }

        // dumps a network weights and biass in a json formate that is readable by 'import_nn()'
        void dump_nn(std::string filename)
        {
            json j;

            j["layer_count"] = layers.size();

            // layer sizes
            j["layers"] = json::array();
            for (auto &layer : layers)
                j["layers"].push_back(layer.nodes.size());
            
            // activations
            j["acts"] = json::array();

            // weights
            j["weights"] = json::array();

            for (auto &layer : layers)
            {
                json layer_weights = json::array();

                for (auto &node : layer.nodes)
                {
                    layer_weights.push_back(node.weights);
                }

                j["weights"].push_back(layer_weights);
                j["acts"].push_back(layer.activate);
            }

            // biases
            j["biases"] = json::array();

            for (auto &layer : layers)
            {
                json layer_biases = json::array();

                for (auto &node : layer.nodes)
                {
                    layer_biases.push_back(node.bias);
                }

                j["biases"].push_back(layer_biases);
            }

            std::ofstream file(filename);
            file << j.dump(4); // pretty print
            file.close();
        }
    };
}
