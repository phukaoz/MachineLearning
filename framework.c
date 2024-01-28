#define FRAMEWORK_IMPLEMENTATION
#include "framework.h"
#include <time.h>

typedef struct{
    mat a0;
    mat w1, b1, a1;
    mat w2, b2, a2;
}Xor;

void forward_xor(Xor m){
    matmul(m.a1, m.a0, m.w1);
    matsum(m.a1, m.b1);
    matsig(m.a1);

    matmul(m.a2, m.a1, m.w2);
    matsum(m.a2, m.b2);
    matsig(m.a2);
}

float cost(Xor m, mat ti, mat to){
    assert(ti.rows == to.rows);
    assert(to.cols == m.a2.cols);
    size_t n = ti.rows;
    
    float c = 0;
    for (size_t i = 0; i < n; ++i){
        mat x = matrow(ti, i);
        mat y = matrow(to, i);
        
        matcpy(m.a0, x);
        forward_xor(m);

        size_t q = to.cols;
        for (size_t j = 0; j < q; ++j){
            float d = matat(m.a2,0,j) - matat(y, 0, j);
            c += d*d;
        }
    }
    return c/n;
}

int main(void){
    srand(time(0));
    Xor m;
    m.a0 = matalloc(1,2);
    m.w1 = matalloc(2,2);
    m.b1 = matalloc(1,2);
    m.a1 = matalloc(1,2);
    m.w2 = matalloc(2,1);
    m.b2 = matalloc(1,1);
    m.a2 = matalloc(1,1);

    matrand(m.w1, 0, 1);
    matrand(m.b1, 0, 1);
    matrand(m.w2, 0, 1);
    matrand(m.b2, 0, 1);

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            matat(m.a0, 0, 0) = i;
            matat(m.a0, 0, 1) = j;
            forward_xor(m);
            float y = *m.a2.es;

            printf("%zu ^ %zu = %f\n", i, j, y);
        }
    }

    return 0;
}