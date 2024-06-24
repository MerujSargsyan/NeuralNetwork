#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifndef test_len
#define    test_len (int)(sizeof(test) / sizeof(test[0]))
#endif

float test[][3] =  {
    {0,0,0},
    {0,1,0},
    {1,0,0},
    {1,1,1}
};

// using sigmoid function to limit output y to [0, 1]
float map_outputf(float output) {
    return 1.0f/(1.0f + expf(output));
}

float rand_float(void) {
    return (float)rand() / (float) RAND_MAX;
}

float cost(float param1, float param2, float bias) {
    float result = 0.0f;
    for(int i = 0; i < test_len; i++) {
        float x1 = test[i][0];
        float x2 = test[i][1];
        float y = map_outputf(x1*param1 + x2*param2 + bias);
        float diff = test[i][2] - y;
        result += diff*diff;
    }
    return result / test_len;
}

int main(void) {
    srand(time(0));
    float p1 = rand_float();
    float p2 = rand_float();
    float bias = rand_float();

    float lrn_rate = 1e-1;
    float eps = 1e-1;
    
    for(int i = 0; i < 1000*1000; i++) {
        float c = cost(p1, p2, bias);
        float dp1 = (cost(p1 + eps, p2, bias) - c)/eps;
        float dp2 = (cost(p1, p2 + eps, bias) - c)/eps;
        float dbias = (cost(p1, p2, bias+eps) - c)/eps;

        p1 -= lrn_rate*dp1;
        p2 -= lrn_rate*dp2;
        bias -= lrn_rate*dbias;
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d | %d: %f \n", i, j, map_outputf(i*p1 + j*p2 + bias));
        }
    }

    return 0;
}
