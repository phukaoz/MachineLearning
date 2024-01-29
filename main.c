#include <stdio.h>
#include "framework/matrix.h"

int main(void){
    mat m1 = matinit(2, 4);
    matfill(m1,0);
    matprint(m1);
    mat m2 = matscalar(m1, 2.5);
    matprint(m2);
    mat m3 = mattran(m2);
    matprint(m3);
    return 0;
}