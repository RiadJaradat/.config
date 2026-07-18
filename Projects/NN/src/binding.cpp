#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "NN.hpp"  // your header file

namespace py = pybind11;

PYBIND11_MODULE(NN, m)
{
    m.doc() = "Python bindings for the NN neural network library";

    // -------------------------
    // Enums
    // -------------------------
    py::enum_<NN::actType>(m, "ActType", "Activation function types")
        .value("Sigmoid", NN::actType::Sigmoid)
        .value("ReLU",    NN::actType::ReLU)
        .export_values();

    // -------------------------
    // Free functions
    // -------------------------
    m.def("random_float", &NN::randomFloat,
          py::arg("min"), py::arg("max"),
          "Generate a random float in [min, max]");

    m.def("sigmoid", &NN::sigmoid,
          py::arg("x"),
          "Sigmoid activation function");

    m.def("sigmoid_derivative", &NN::sigmoid_derivative,
          py::arg("z"),
          "Derivative of the sigmoid function");

    m.def("relu", &NN::relu,
          py::arg("x"),
          "ReLU activation function");

    m.def("relu_derivative", &NN::relu_derivative,
          py::arg("z"),
          "Derivative of the ReLU function");

    m.def("run_activation", &NN::Run,
          py::arg("func_type"), py::arg("z"), py::arg("is_derivative") = false,
          "Run an activation function (or its derivative) by type");

    m.def("tokenizer", &NN::tokenizer,
          py::arg("sentence"),
          "Hash-based word tokenizer — maps each whitespace-separated word to a float in [0, 1)");

    m.def("advance_tokenizer", &NN::advanceTokenizer,
          py::arg("text"),
          "Character-level tokenizer — returns raw byte values as floats");

    m.def("advance_detokenizer", &NN::advanceDetokenizer,
          py::arg("vec"),
          "Convert a list of float byte values back into a string");

    // -------------------------
    // Node
    // -------------------------
    py::class_<NN::Node>(m, "Node",
        "A single neuron with a bias and a weight vector")
        .def(py::init<>())
        .def_readwrite("bias",    &NN::Node::bias,    "Bias term")
        .def_readwrite("weights", &NN::Node::weights, "Weight vector")
        .def("pass_input", &NN::Node::pass,
             py::arg("inputs"),
             "Compute the weighted sum of inputs plus bias (pre-activation)");

    // -------------------------
    // Layer
    // -------------------------
    py::class_<NN::Layer>(m, "Layer",
        "A fully-connected layer of nodes with a shared activation function")
        .def(py::init<size_t, NN::actType>(),
             py::arg("size"), py::arg("activation"))
        .def_readwrite("nodes",       &NN::Layer::nodes)
        .def_readwrite("last_input",  &NN::Layer::last_input,  "Cached input from the last forward pass")
        .def_readwrite("last_output", &NN::Layer::last_output, "Cached output from the last forward pass")
        .def_readwrite("last_z",      &NN::Layer::last_z,      "Cached pre-activation values from the last forward pass")
        .def_readwrite("activate",    &NN::Layer::activate,    "Activation function type")
        .def("pass_input", &NN::Layer::pass,
             py::arg("inputs"),
             "Forward-pass inputs through all nodes and return activated outputs");

    // -------------------------
    // Network
    // -------------------------
    py::class_<NN::Network>(m, "Network",
        "A sequential multi-layer feedforward neural network")
        .def(py::init<>())
        .def_readwrite("layers", &NN::Network::layers)

        .def("add_layer", &NN::Network::addLayer,
             py::arg("size"), py::arg("activation"),
             "Append a new layer of `size` nodes with the given activation function")

        .def("forward", &NN::Network::forward,
             py::arg("input"),
             "Run a forward pass and return the output vector")

        .def("backpropagation", &NN::Network::backpropagation,
             py::arg("target"), py::arg("lr"),
             "Run one backpropagation step given the target vector and learning rate")

        .def("train", &NN::Network::trainLoop,
             py::arg("inputs"), py::arg("targets"),
             py::arg("epochs"), py::arg("lr") = 0.1f,
             "Train on parallel lists of input/target vectors for the given number of epochs")

        .def("train_map",
             [](NN::Network &self,
                std::map<std::vector<float>, std::vector<float>> inputs_and_targets,
                int epochs, float lr)
             {
                 self.trainLoop_map(inputs_and_targets, epochs, lr);
             },
             py::arg("inputs_and_targets"),
             py::arg("epochs"),
             py::arg("lr") = 0.1f,
             "Train using a dict mapping input vectors to target vectors")

        .def("save", &NN::Network::dump_nn,
             py::arg("filename"),
             "Serialize the network weights and biases to a JSON file")

        .def("load", &NN::Network::import_nn,
             py::arg("filename") = "model.json",
             "Load network weights and biases from a JSON file");
}