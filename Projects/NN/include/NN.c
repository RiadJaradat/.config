#include <stdio.h>
#include <stdlib.h>

/*
layer;
input = 1.2, 2.6

// in normal node struct
waights size = input size

float *weights = {
    00.f 00.f // node1
    00.f 00.f // node2
};

// store:
    how many weights each node has
    how many weights in toatal
    how many biases in toatal
*/

typedef struct Layer
{
    size_t weights_size;
    float *weights;
    size_t biases_size;
    float *biases;
    int node_weights_size;
} Layer;

// args: self, nodes 
void INIT_Layer(Layer *layer, size_t nodes_size)
{
    layer->biases_size = nodes_size;
    layer->biases = malloc(nodes_size * sizeof(float));
}

void pass(Layer *layer, float *inputs, size_t inputs_size, size_t node_count)
{
    layer->node_weights_size = inputs_size;
    layer->weights_size = inputs_size * node_count;
    layer->weights = malloc(layer->weights_size * sizeof(float)); // total weights size

    for (size_t i = 0; i < layer->weights_size; i++)
    {
        layer->weights[i] = (float)rand()/RAND_MAX;
    }

}

int main()
{
    srand(0);

    Layer layer;
    INIT_Layer(&layer, 2);
    size_t size = 2;
    float *inputs = malloc(size * sizeof(float));
    inputs[0] = 1.5;
    inputs[1] = 3.2;
    pass(&layer, inputs, size, 4);
    for (size_t i = 0; i < layer.weights_size; i++)
    {
        printf("%f\n", layer.weights[i]);
    }

    return 0;
}