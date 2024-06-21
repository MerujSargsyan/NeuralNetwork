#include <stdio.h>
#include <stdlib.h>

#define test_len (int)(sizeof(test) / sizeof(test[0]))

float test[][2] = {
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {0, 0},
    {5, 10},
};

float cost(float guess) {
    float result = 0.0f;
    for(int i = 0; i < test_len; i++) {
        float diff = test[i][1] - guess * test[i][0];
        result += diff*diff;
    }
    return result / test_len;
}


int main(void) {
    srand(69);
    float peram1 = (float) rand() / (float) RAND_MAX;
    peram1 *= 10.0f;

    float eps = 1e-2;
    float lrn_rate = 1e-2;

    // approcimate gradient using finite difference
    for(int i = 0; i < 100; i++) {
        float dperam = (cost(peram1 + eps) - cost(peram1))/eps;
        peram1 -= lrn_rate * dperam;
    }
    printf("%f\n", peram1);

    return 0;
}
