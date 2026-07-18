#include <stdio.h>
#include <stdlib.h>
#define NN_weights 16

/*
W = [
  3.23, 93.23, 0.5,   // neuron 0
  1.1,  2.2,   3.3    // neuron 1
]
  Rule = each 3 floats = 1 neuran
*/
/*
W = [
  3.23, 93.23, 0.5,   // neuron 0
  1.1,  2.2,   3.3    // neuron 1, layer 1
  3.22, 92.23, 0.5,   // neuron 0
  1.0,  4.2,   4.3    // neuron 1, layer 2
]
  *Rule = each n floats = layer = each 3 = 1 neuran
   n = stored layer size
*/

// typedef struct Network
// {
//     float **weights;
//     float *biases;

// };

const int layer1_size = 2; // n1
const int layer2_size = 4; // n2
const int layer3_size = 2; // n3
int layer_nodes[3] = {
    2,
    4,
    2
};

int node_weights[3];

const int node_weights = 2;

float NN[NN_weights] = {
    0.f,
    0.f, // node 1
    0.f,
    0.f, // node 2 // layer1
    0.f,
    0.f, // node 1
    0.f,
    0.f, // node 2
    0.f,
    0.f, // node 3
    0.f,
    0.f, // node 4 // layer2
    0.f,
    0.f, // node 1
    0.f,
    0.f, // node 2 // layer3
};

void forward()
{
    int node_count = 0;
    int layer_count = 1;
    int layer_count_index = 0;

    for (int i = 0; i < NN_weights; i += node_weights)
    {
        int current_layer_size = layers[layer_count_index];
        node_count++;
        if (node_count > current_layer_size)
        {
            layer_count++;
            layer_count_index++;
            node_count = 1;
        }
        printf("%f, %f: node%d, layer%d\n", NN[(int)i / 2], NN[i], node_count, layer_count);
    }
}

int main()
{
    forward();
    return 0;
}