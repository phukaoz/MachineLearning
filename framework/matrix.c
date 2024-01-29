#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* private */
double uniform_distribution(double low, double high){
    double difference = high - low;
    int scale = 10000;
    int scale_difference = (int)(difference * scale);
    return low + (1.0f * (rand() % scale_difference) / scale);
}

int dimensions_match(mat a, mat b){
    return (a.cols == b.cols && a.rows == b.rows);
}

void error(char* output){
    fprintf(stderr, output);
    exit(EXIT_FAILURE);
}

/* public */
mat matinit(size_t row, size_t col){
    mat Matrix = {.rows = row, .cols = col};
    Matrix.entries = malloc(row * sizeof(double*));
    for(size_t i = 0; i < row; i++){
        Matrix.entries[i] = malloc(col * sizeof(double));
    }
    return Matrix;
}

mat matclone(mat m){
    mat Matrix = matinit(m.rows, m.cols);
    for(size_t i=0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            Matrix.entries[i][j] = m.entries[i][j]; 
        }
    }
    return Matrix;
}

mat matrow(mat m, size_t at){
    mat Matrix = matinit(1, m.cols);
    for(size_t i=0;i<m.cols;i++){
        Matrix.entries[0][i] = m.entries[at][i];
    }
    return Matrix;
}

void matfill(mat m, double val){
    for(size_t i = 0;i<m.rows;i++){
        for(size_t j = 0;j<m.cols;j++){
            m.entries[i][j] = val;
        }
    }
}

void matprintf(mat m, char* s){
    printf("Matrix: %s  Rows: %d  Columns: %d\n",s,m.rows,m.cols);
    for(size_t i = 0;i<m.rows;i++){
        for(size_t j = 0;j<m.cols;j++){
            printf("%.3f  ",m.entries[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matfree(mat m){
    for(size_t i = 0;i<m.rows;i++){
        free(m.entries[i]);
    }
    free(m.entries);
}

void matcpy(mat dest, mat src){
    if(dimensions_match(dest, src)){
        for(size_t i=0;i<dest.rows;i++){
            for(size_t j=0;j<dest.cols;j++){
                dest.entries[i][j] = src.entries[i][j];
            }
        }
    }else{
        error("Dimensions mismatch for matcpy().\n");
    }
}

void matrand(mat m, int val){
    double min = -1.0 / sqrt(val);
    double max = 1.0 / sqrt(val);
    for(size_t i=0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            m.entries[i][j] = uniform_distribution(min, max);
        }
    }
}

size_t matargm(mat m){
    double max = 0;
    size_t index = 0;
    for(size_t i = 0; i < m.rows;i++){
        if(m.entries[i][0] > max){
            max = m.entries[i][0];
            index = i;
        }
    }
    return index;
}

mat matflat(mat m, size_t axis){
    mat Matrix;
    if (axis == 0){
        Matrix = matinit(m.rows * m.cols, 1);
    }else if(axis == 1){
        Matrix = matinit(1, m.rows * m.cols);
    }else{
        error("Invalid argument for matflat(). Must be 0 or 1.\n");
    }
    for(size_t i = 0; i < m.rows; i++){
        for(size_t j = 0; j < m.cols; j++){
            if(axis == 0) Matrix.entries[i*m.cols + j][0] = m.entries[i][j];
            else if(axis == 1) Matrix.entries[0][i*m.cols + j] = m.entries[i][j];
        }
    }
    return Matrix;
}

mat matmul(mat m1, mat m2){
    mat Matrix;
    if(dimensions_match(m1, m2)){
        Matrix = matclone(m1);
        for(size_t i=0;i<m1.rows;i++){
            for(size_t j=0;j<m1.cols;j++){
                Matrix.entries[i][j] = m1.entries[i][j] * m2.entries[i][j];
            }
        }
    }else{
        error("Dimension mismatch for matmul().");
    }
    return Matrix;
}

mat matadd(mat m1, mat m2){
    mat Matrix;
    if(dimensions_match(m1, m2)){
        Matrix = matclone(m1);
        for(size_t i=0;i<m1.rows;i++){
            for(size_t j=0;j<m1.cols;j++){
                Matrix.entries[i][j] = m1.entries[i][j] + m2.entries[i][j];
            }
        }
    }else{
        error("Dimension mismatch for matadd().");
    }
    return Matrix;
}

mat matsub(mat m1, mat m2){
    mat Matrix;
    if(dimensions_match(m1, m2)){
        Matrix = matclone(m1);
        for(size_t i=0;i<m1.rows;i++){
            for(size_t j=0;j<m1.cols;j++){
                Matrix.entries[i][j] = m1.entries[i][j] - m2.entries[i][j];
            }
        }
    }else{
        error("Dimension mismatch for matsub().");
    }
    return Matrix;
}

mat matapply(mat m, double (*func)(double)){
    mat Matrix;
    Matrix = matclone(m);
    for(size_t i=0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            Matrix.entries[i][j] = (*func)(m.entries[i][j]);
        }
    }
}

mat matdot(mat m1, mat m2){
    mat Matrix;
    if(m1.cols == m2.rows){
        Matrix = matinit(m1.rows, m2.cols);
        matfill(Matrix, 0.0);
        for(size_t i=0;i<m1.rows;i++){
            for(size_t k=0;k<m2.rows;k++){
                for(size_t j=0;j<m2.cols;j++){
                    Matrix.entries[i][j] += m1.entries[i][k] * m2.entries[k][j];
                }
            }
        }
    }else{
        error("Dimension mismath for matdot().");
    }
    return Matrix;
}

mat mattran(mat m){
    mat Matrix = matinit(m.cols, m.rows);
    for(size_t i=0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            Matrix.entries[j][i] = m.entries[i][j];
        }
    }
    return Matrix;
}

mat matscale(mat m, double val){
    mat Matrix = matclone(m);
    for(size_t i =0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            Matrix.entries[i][j] *= val;
        }
    }
    return Matrix;
}

mat matscalar(mat m, double val){
    mat Matrix = matclone(m);
    for(size_t i =0;i<m.rows;i++){
        for(size_t j=0;j<m.cols;j++){
            Matrix.entries[i][j] += val;
        }
    }
    return Matrix;
}