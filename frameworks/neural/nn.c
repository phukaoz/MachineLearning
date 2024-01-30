#include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../matrix.h"
#include "activation.h"

#define MAXLEN 5000

NeuralNetwork netinit(int in, int hid, int out, double lr){
    NeuralNetwork Network = {
        .input = in,
        .hidden = hid,
        .output = out,
        .learning_rate = lr,
    };
    mat hidden_layer = matinit(hid, in);
    mat output_layer = matinit(out, hid);
    matrand(hidden_layer, hid);
    matrand(output_layer, out);
    Network.hidden_weights = hidden_layer;
    Network.output_weights = output_layer;
    return Network;
}

void nettrain(NeuralNetwork net, mat in, mat out){
    
}