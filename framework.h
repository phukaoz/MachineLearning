#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

#include <stddef.h>
#include <stdio.h>
#include <math.h>

#ifndef FRAMEWORK_MALLOC
#include <stdlib.h>
#define FRAMEWORK_MALLOC malloc
#endif //FRAMEWORK_MALLOC

#ifndef FRAMEWORK_ASSERT
#include <assert.h>
#define FRAMEWORK_ASSERT assert
#endif //FRAMEWORK_ASSERT

typedef struct {
    size_t rows;
    size_t cols;
    size_t stride;
    float *es;
} mat;

#define matat(m,i,j) (m).es[(i)*(m).stride + (j)]

float rand_float(void);
float sigmoid(float x);

mat matalloc(size_t rows, size_t cols);
void matfill(mat dest, float val);
void matmul(mat dest, mat a, mat b);
void matsum(mat dest, mat a);
void matprint(mat m);
void matrand(mat m, float low, float high);
void matcpy(mat dest, mat src);
void matsig(mat m);
mat matrow(mat src, size_t i);

#endif //FRAMEWORK_H_

#ifdef FRAMEWORK_IMPLEMENTATION

float rand_float(void){
    return (float)rand() / (float)RAND_MAX;
}

float sigmoid(float x){
    return 1.f/(1.f + expf(-x));
}

mat matalloc(size_t rows, size_t cols){
    mat ret;
    ret.rows = rows;
    ret.cols = cols;
    ret.stride = cols;
    ret.es = FRAMEWORK_MALLOC(sizeof(*ret.es)*rows*cols);
    FRAMEWORK_ASSERT(ret.es != NULL);
    return ret;
}

void matsig(mat m){
    for(size_t i = 0;i<m.rows;i++){
        for(size_t j =0;j<m.cols;j++){
            matat(m,i,j) = sigmoid(matat(m,i,j));
        }
    }
}

void matfill(mat dest,float val){
    for(size_t i=0;i<dest.rows; i++){
        for(size_t j=0;j<dest.cols; j++){
            matat(dest,i,j) = val;
        }
    }
}

void matmul(mat dest, mat a, mat b){
    FRAMEWORK_ASSERT(a.cols == b.rows);
    FRAMEWORK_ASSERT(dest.rows == a.rows);
    FRAMEWORK_ASSERT(dest.cols == b.cols);
    mat_fill(dest,0);
    for(size_t i=0;i<a.rows;i++){
        for(size_t k=0;k<a.cols;k++){
            for(size_t j=0;j<b.cols;j++){
                matat(dest,i,j) += matat(a,i,k) + matat(b,k,j);
            }
        }
    }
}

void matcpy(mat dest, mat src){
    FRAMEWORK_ASSERT(dest.cols == src.cols);
    FRAMEWORK_ASSERT(dest.rows == src.rows);
    for(size_t i = 0; i < dest.rows;i++){
        for(size_t j=0;j < dest.cols;j++){
            matat(dest,i,j) = matat(src,i,j);
        }
    }
}

void matsum(mat dest, mat a){
    FRAMEWORK_ASSERT(dest.rows == a.rows);
    FRAMEWORK_ASSERT(dest.cols == a.cols);
    for(size_t i = 0; i < dest.rows; i++){
        for(size_t j=0; j < dest.cols; j++){
            matat(dest,i,j) += matat(a,i,j);
        }
    }
}

mat matrow(mat src, size_t row){
    FRAMEWORK_ASSERT(row < src.rows);
    return (mat){
        .rows = 1,
        .cols = src.cols,
        .stride = src.stride,
        .es = &matat(src, row, 0),
    };
}

void matprint(mat m){
    for(size_t i = 0; i < m.rows; i++){
        for(size_t j=0; j < m.cols; j++){
            printf("%f ",matat(m,i,j));
        }
        printf("\n");
    }
}

void matrand(mat m, float low, float high){
    for(size_t i = 0; i < m.rows; i++){
        for(size_t j=0; j < m.cols; j++){
            matat(m,i,j) = rand_float()*(high-low) +low;
        }
    }
}

#endif //FRAMEWORK_IMPLEMENTATION