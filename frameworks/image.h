#pragma once

#include "matrix.h"

typedef struct{
    mat img_data;
    int label;
}img;

img* imgcsv(char* file_name, int number_of_images);
void imgprint(img image);
