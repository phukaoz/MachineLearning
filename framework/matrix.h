#pragma once

#include <stddef.h>

#define matprint(x) matprintf(x, #x)

typedef struct{
    double** entries;
    size_t rows;
    size_t cols;
}mat;

mat matinit(size_t row, size_t col);
mat matclone(mat matrix);
void matfill(mat dest, double value);
void matfree(mat dest);
void matprintf(mat matrix, char* name);
void matcpy(mat dest, mat src);
void matrand(mat dest, int value);
size_t matargm(mat matrix);
mat matflat(mat matrix, size_t axis);

mat matmul(mat first, mat second);
mat matadd(mat first, mat second);
mat matsub(mat first, mat second);
mat matapply(mat dest, double (*func)(double));
mat matdot(mat first, mat second);
mat mattran(mat dest);
mat matscale(mat dest, double delta);
mat matscalar(mat dest, double delta);
