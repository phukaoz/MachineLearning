#include <stdio.h>
#include "frameworks/matrix.h"
#include "frameworks/image.h"
#include <stdlib.h>

int main(void){
    img *img = imgcsv("data/train.csv", 10);
    imgprint(img[2]);

    return 0;
}