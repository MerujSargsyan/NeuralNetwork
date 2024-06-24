/*
*   XOR model will be defined as:
*   
*   x ----> or -
*     -- --^    -
*       --        -> and ---> XOR output
*     --  -->   -
*   y ----> nand
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define    xor_test_len (int)(sizeof(xor_test) / sizeof(xor_test[0]))

float xor_test[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0}
};
// construct xor from or, nand, and
typedef struct {
    float or_w1;
    float or_w2;
    float or_bias;

    float and_w1;
    float and_w2;
    float and_bias;

    float nand_w1;
    float nand_w2;
    float nand_bias;
} Xor;

// using sigmoid function to limit output y to [0, 1]
float map_outputf(float output) {
    return 1.0f/(1.0f + expf(output));
}

// pass in x,y into or,nand then forward into and
float forward(Xor m, float x, float y) {
    float a = map_outputf(m.or_w1 * x + m.or_w2 * y + m.or_bias);
    float b = map_outputf(m.nand_w1 * x + m.nand_w2 * y + m.nand_bias);
    return map_outputf(m.and_w1 * a + m.and_w2 * b + m.and_bias);
}

float cost(Xor m) {
    float result = 0.0f;
    for(int i = 0; i < xor_test_len; i++) {
        float x1 = xor_test[i][0];
        float x2 = xor_test[i][1];
        float y = forward(m, x1, x2);
        float diff = xor_test[i][2] - y;
        result += diff*diff;
    }
    return result / xor_test_len;
}

// TODO use arrays to shorten this
Xor compute_gradient(Xor m, float eps) {
    Xor newM;
    float c = cost(m);

    float saved;

    saved = m.or_w1;
    m.or_w1 += eps;
    newM.or_w1 = (cost(m) - c)/eps;
    m.or_w1 = saved;

    saved = m.or_w2;
    m.or_w2 += eps;
    newM.or_w2 = (cost(m) - c)/eps;
    m.or_w2 = saved;

    saved = m.or_bias;
    m.or_bias+= eps;
    newM.or_bias = (cost(m) - c)/eps;
    m.or_bias = saved;

    saved = m.and_w1;
    m.and_w1 += eps;
    newM.and_w1 = (cost(m) - c)/eps;
    m.and_w1 = saved;

    saved = m.and_w2;
    m.and_w2 += eps;
    newM.and_w2 = (cost(m) - c)/eps;
    m.and_w2 = saved;

    saved = m.and_bias;
    m.and_bias += eps;
    newM.and_bias = (cost(m)-c)/eps;
    m.and_bias = saved;

    saved = m.nand_w1;
    m.nand_w1 += eps;
    newM.nand_w1 = (cost(m) - c)/eps;
    m.nand_w1 = saved;

    saved = m.nand_w2;
    m.nand_w2 += eps;
    newM.nand_w2 = (cost(m) - c)/eps;
    m.nand_w2 = saved;

    saved = m.nand_bias;
    m.nand_bias += eps;
    newM.nand_bias = (cost(m) - c)/eps;
    m.nand_bias = saved;
    return newM;
}



float rand_float() {
    return (float)rand() / (float) RAND_MAX;
}

Xor rand_xor() {
    Xor m;
    m.or_w1 = rand_float();
    m.or_w2 = rand_float();
    m.or_bias= rand_float();

    m.and_w1 = rand_float();
    m.and_w2 = rand_float();
    m.and_bias= rand_float();

    m.nand_w1 = rand_float();
    m.nand_w2 = rand_float();
    m.nand_bias = rand_float();
    return m;
}

void print_xor(Xor m) {
    printf("-------\n");
    printf("%f\n", m.or_w1);
    printf("%f\n", m.or_w2);
    printf("%f\n", m.or_bias);
    printf("%f\n", m.and_w1);
    printf("%f\n", m.and_w2);
    printf("%f\n", m.and_bias);
    printf("%f\n", m.nand_w1);
    printf("%f\n", m.nand_w2);
    printf("%f\n", m.nand_bias);
    printf("-------\n");
}

Xor apply_diff(Xor m, Xor newM, float lrn_rate) {
    m.or_w1 -= lrn_rate*newM.or_w1;
    m.or_w2 -= lrn_rate*newM.or_w2;
    m.or_bias -= lrn_rate*newM.or_bias;
              
    m.and_w1 -= lrn_rate*newM.and_w1;
    m.and_w2 -= lrn_rate*newM.and_w2;
    m.and_bias -= lrn_rate*newM.and_bias;
              
    m.nand_w1 -= lrn_rate*newM.nand_w1;
    m.nand_w2 -= lrn_rate*newM.nand_w2;
    m.nand_bias -= lrn_rate*newM.nand_bias;
    return m;
}
int main(void) {
    srand(420);
    float eps = 1e-2;
    float lrn_rate = 1e-1;

    Xor m = rand_xor();

    for(int i = 0; i < 100*1000; i++) {
        Xor newM = compute_gradient(m, eps);
        m = apply_diff(m, newM, lrn_rate);
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d | %d: %f \n", i, j, forward(m, i, j));
        }
    }
}
