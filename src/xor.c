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

#define xor_test_len (int)(sizeof(xor_test) / sizeof(xor_test[0]))
#define param_count 9

float xor_test[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0}
};
// construct xor from or, nand, and
typedef struct {
    float params[9];
} Xor;

// using sigmoid function to limit output y to [0, 1]
float map_outputf(float output) {
    return 1.0f/(1.0f + expf(output));
}

// pass in x,y into or,nand then forward into and
float forward(Xor m, float x, float y) {
    float a = map_outputf(m.params[0] * x + m.params[1] * y + m.params[2]);
    float b = map_outputf(m.params[3] * x + m.params[4] * y + m.params[5]);
    return map_outputf(m.params[6]* a + m.params[7] * b + m.params[8]);
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

Xor compute_gradient(Xor m, float eps) {
    Xor newM;
    float c = cost(m);

    float saved;

    for(int i = 0; i < param_count; i++) {
        saved = m.params[i];
        m.params[i] += eps;
        newM.params[i] = (cost(m) - c)/eps;
        m.params[i] = saved;
    }

    return newM;
}

float rand_float() {
    return (float)rand() / (float) RAND_MAX;
}

Xor rand_xor() {
    Xor m;
    for(int i = 0; i < param_count; i++) {
        m.params[i] = rand_float();
    }
    return m;
}

void print_xor(Xor m) {
    printf("-------\n");
    for(int i = 0; i < param_count; i++) {
        printf("%f\n", m.params[i]);
    }
    printf("-------\n");
}

Xor apply_diff(Xor m, Xor newM, float lrn_rate) {
    for(int i = 0; i < param_count; i++) {
        m.params[i] -= lrn_rate*newM.params[i];
    }
    return m;
}

int main(void) {
    srand(420);
    float eps = 1e-2;
    float lrn_rate = 1e-1;

    Xor m = rand_xor();
    print_xor(m);

    for(int i = 0; i < 1000*100; i++) {
        Xor newM = compute_gradient(m, eps);
        m = apply_diff(m, newM, lrn_rate);
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d | %d: %f \n", i, j, forward(m, i, j));
        }
    }
}
