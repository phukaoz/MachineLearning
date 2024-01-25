#define FRAMEWORK_IMPLEMENTATION
#include "framework.h"
#include <time.h>

int main(void){
    srand(time(0));
    Mat m = mat_alloc(10, 10);
    mat_rand(m,0,10);
    mat_print(m);
    return 0;
}