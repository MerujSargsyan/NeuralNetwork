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

#include "aihelper.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define xor_test_len (int)(sizeof(xor_test) / sizeof(xor_test[0]))
#define PARAM_COUNT 3
#define WEIGHT_COUNT 2

float xor_test[][3] = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
};

// pass in x,y into or,nand then forward into and
float forward(Model m, float x, float y) { 
    float asum = m.params[0].weights[0] * x + m.params[0].weights[1] * y + m.params[0].bias;
    float a = sigmoid(asum);

    float bsum = m.params[1].weights[0] * x + m.params[1].weights[1] * y + m.params[1].bias;
    float b = sigmoid(bsum);

    return sigmoid(m.params[2].weights[0] * a + m.params[2].weights[1] * b + m.params[2].bias);
}

float cost(Model m) {
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

Model compute_gradient(Model m, float eps) {
    Model newM = init_model(PARAM_COUNT, WEIGHT_COUNT);
    float c = cost(m);
    float saved;

    for(int i = 0; i < m.param_count; i++) {
        for(int j = 0; j < m.params[i].weight_count; j++) {
            saved = m.params[i].weights[j];
            m.params[i].weights[j] += eps;
            newM.params[i].weights[j] = (cost(m) - c)/eps;
            m.params[i].weights[j] = saved;
        }
        saved = m.params[i].bias;
        m.params[i].bias += eps;
        newM.params[i].bias = (cost(m) - c)/eps;
        m.params[i].bias = saved;
    }

    return newM;
}

void print_model(Model m) {
    printf("------------------------------\n");
    for(int c = 0; c < m.param_count; c++) {
        printf("Cell %d:", c+1);
        Cell cell = m.params[c];
        for(int w = 0; w < cell.weight_count; w++) {
            printf(" weight %d: %f ", w+1, cell.weights[w]);
            printf(" bias: %f", cell.bias);
        }
        printf("\n");
    }
    printf("------------------------------\n");
}

int main(void) {
    srand(time(0));
    float eps = 1e-1;
    float lrn_rate = 0.5;

    Model m = init_model(PARAM_COUNT, WEIGHT_COUNT);

    printf("param count: %d\n", m.param_count);
    for(int i = 0; i < 100*100; i++) {
        Model newM = compute_gradient(m, eps);
        teach_model(&m, &newM, lrn_rate);
    }

    print_model(m);
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d | %d: %f \n", i, j, forward(m, i, j));
        }
    }
}
