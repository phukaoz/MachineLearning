#pragma once

#include "../matrix.h"
#include "../image.h"

typedef struct{
    int input;
    int hidden;
    int output;
    double learning_rate;
    mat hidden_weights;
    mat output_weights;
}NeuralNetwork;

NeuralNetwork netinit(int input, int hidden, int output, double learning_rate);
void nettrain(NeuralNetwork net, mat input_data, mat output_size);
void nettrain_batch_img(NeuralNetwork net, img *images, int batch_size);
mat netpredict_img(NeuralNetwork net, img *images);
mat netpredict(NeuralNetwork net, mat input_data);
void netsave(NeuralNetwork net, char* file_name);
NeuralNetwork netload(char* file_name);
void netprint(NeuralNetwork net);