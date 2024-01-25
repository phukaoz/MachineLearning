#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

#include <stddef.h>
#include <stdio.h>

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
    float *es;
} Mat;

#define MAT_AT(m,i,j) (m).es[(i)*(m).cols + (j)]

float rand_float(void);

Mat mat_alloc(size_t rows, size_t cols);
void mat_dot(Mat dest, Mat a, Mat b);
void mat_sum(Mat dest, Mat a);
void mat_print(Mat m);
void mat_rand(Mat m, float low, float high);

#endif //FRAMEWORK_H_

#ifdef FRAMEWORK_IMPLEMENTATION

float rand_float(void){
    return (float)rand() / (float)RAND_MAX;
}

Mat mat_alloc(size_t rows, size_t cols){
    Mat ret;
    ret.rows = rows;
    ret.cols = cols;
    ret.es = FRAMEWORK_MALLOC(sizeof(*ret.es)*rows*cols);
    FRAMEWORK_ASSERT(ret.es != NULL);
    return ret;
}

void mat_dot(Mat dest, Mat a, Mat b){
    (void) dest;
    (void) a;
    (void) b;
}

void mat_sum(Mat dest, Mat a){
    FRAMEWORK_ASSERT(dest.rows == a.rows);
    FRAMEWORK_ASSERT(dest.cols == a.cols);
    for(size_t i = 0; i < dest.rows; i++){
        for(size_t j=0; j < dest.cols; j++){
            MAT_AT(dest,i,j) += MAT_AT(a,i,j);
        }
    }
}

void mat_print(Mat m){
    for(size_t i = 0; i < m.rows; i++){
        for(size_t j=0; j < m.cols; j++){
            printf("%f ",MAT_AT(m,i,j));
        }
        printf("\n");
    }
}

void mat_rand(Mat m, float low, float high){
    for(size_t i = 0; i < m.rows; i++){
        for(size_t j=0; j < m.cols; j++){
            MAT_AT(m,i,j) = rand_float()*(high-low) +low;
        }
    }
}

#endif //FRAMEWORK_IMPLEMENTATION