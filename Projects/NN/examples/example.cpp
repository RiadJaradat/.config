#include "NN.hpp"

/*
simple usage off the NN header file in C++
*/

int main()
{
    // --------------- node level controll ---------------
    NN::Node node;

    /*
    node has the core basics of what a neural network is.
    for example:
    */

    // NN::Node::pass(inputs: {...})
    node.pass({1.f, 2.4, 3.7});
    // NN::Node::std::vector<float> weights
    node.weights;
    // the initial weights for the node
    // NN::Node::float bias
    node.bias;
    // the initial bias for the node
    /*
    this function does the simple work of taking inputs,
    multiplying the inputs by a random set off weights,
    adding the finall sum off both to a random bias
    */

    // this is the core block for building the neural network
    // ---------------------------------------------------

    // --------------- layer level control ---------------
    NN::Layer network_layer{1}; // NN::Layer{int layer_size}

    // NN::Layer::pass(std::vector<float> inputs)
    network_layer.pass({1.2, 3.4, 2.0});
    // NN::Layer::std::vector<NN::Node> nodes
    network_layer.nodes;
    // this vector stores each NN::Node that is in the Layer
    // *Note in the initializer this vector will be filled with new NN::Node
    //  meaning that it automaticly fills the vector
    // NN::Layer::std::vector<float> last_input
    network_layer.last_input;
    // this vector stores the last given inputs to the layer
    // NN::Layer::std::vector<float> last_output
    network_layer.last_output;
    // this vector stores the last output from the layer
    // ---------------------------------------------------
    // --------------- neural network level control ---------------
    NN::Network net;

    // NN::Network::addLayer(size_t size)
    // adds a layer with "size" nodes
    net.addLayer(3); // first layer (takes input)
    net.addLayer(2); // output layer

    // NN::Network::forward(std::vector<float> input)
    // feeds input through all layers
    floatvec output = net.forward({1.0f, 2.0f, 3.0f});

    // NN::Network::std::vector<NN::Layer> layers
    net.layers;
    // stores all layers in order

    // NN::Network::backpropegation(target, learning_rate)
    // adjusts weights based on error
    net.backpropegation({0.0f, 1.0f}, 0.1f);

    // NN::Network::trainLoop(inputs, targets, epochs, lr)
    // trains the network over dataset
    std::vector<floatvec> inputs = {
        {1.0f, 2.0f, 3.0f},
        {0.5f, 1.5f, 2.5f}};

    std::vector<floatvec> targets = {
        {0.0f, 1.0f},
        {1.0f, 0.0f}};

    net.trainLoop(inputs, targets, 100, 0.1f);

    // NN::Network::dump_nn(filename)
    // saves weights + biases to JSON file
    net.dump_nn("model.json");

    // NN::Network::import_nn(filename)
    // loads weights + biases from JSON file
    net.import_nn("model.json");

    // -----------------------------------------------------------
    // --------------- utility / helper functions ---------------

    // std::hash<std::string> hasher
    // used to convert strings into numeric values (used in tokenizer)
    NN::hasher("hello");

    // NN::randomFloat(min, max)
    // returns a random float between min and max
    float r = NN::randomFloat(-1.0f, 1.0f);

    // NN::init_weights(weights, input_size)
    // initializes weights using Xavier-like initialization
    floatvec weights(3);
    NN::init_weights(weights, 3);

    // NN::sigmoid(x)
    // activation function (used in neurons)
    double s = NN::sigmoid(0.5);

    // NN::sum(vector)
    // sums all values in a vector
    float total = NN::sum({1.0f, 2.0f, 3.0f});

    // NN::operator*(a, b)
    // element-wise multiplication of two vectors
    using NN::operator*;
    floatvec result = floatvec{1, 2, 3} * floatvec{4, 5, 6};
    // or
    floatvec result = NN::operator*(floatvec{1, 2, 3}, floatvec{4, 5, 6}); // without the need of using NN::operator*;
    // result = {4, 10, 18}

    // NN::tokenizer(sentence)
    // converts a sentence into numeric tokens
    floatvec tokens = NN::tokenizer("hello world");

    // ---------------------------------------------------------

    return 0;
}