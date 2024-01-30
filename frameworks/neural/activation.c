#include "activation.h"
#include <math.h>
#include "../matrix.h"

double sigmoid(double input){
    return 1.0f / (1.0f + exp(-1.0f * input));
}

mat sigmoidPrime(mat m){
    mat Ones = matinit(m.rows, m.cols);
    matfill(Ones,1);
    mat Substracted = matsub(Ones, m);
    mat Multiplied = matmul(m, Substracted);
    matfree(Substracted);
    matfree(Ones);
    return Multiplied;
}

mat softmax(mat m){
    double total = 0;
    for(size_t i = 0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            total += exp(m.entries[i][j]);
        }
    }
    mat Matrix =  matinit(m.rows, m.cols);
    for(size_t i=0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            Matrix.entries[i][j] = exp(m.entries[i][j]) / total;
        }
    }
    return Matrix;
}