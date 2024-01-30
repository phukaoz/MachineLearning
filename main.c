#include <stdio.h>
#include "frameworks/matrix.h"

int main(void){
    mat m1 = matinit(2, 4);
    matfill(m1,0);
    matprint(m1);
    return 0;
}