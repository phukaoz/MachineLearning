#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 5000

img* imgcsv(char* filename, int nums){
    FILE *fp;
    img* images = malloc(nums*sizeof(img));
    char row[MAXLEN];
    fp = fopen(filename, "r");

    fgets(row, MAXLEN, fp);
    size_t i = 0;
    while(feof(fp) != 1 && i < nums){
        size_t j = 0;
        fgets(row, MAXLEN, fp);
        char* token = strtok(row, ",");
        images[i].img_data = matinit(28, 28);
        while(token != NULL){
            if(j == 0){
                images[i].label = atoi(token);
            }else{
                images[i].img_data.entries[(j-1)/28][(j-1)%28] = atoi(token) / 256.0f;
            }
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(fp);
    return images;
}

void imgprint(img images){
    char buffer[MAXLEN];
    matprintf(images.img_data, itoa(images.label,buffer,MAXLEN));
}