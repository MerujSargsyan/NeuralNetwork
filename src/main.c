#include <stdio.h>
#include <stdlib.h>
#define test_len (int)(sizeof(test) / sizeof(test[0]))

// this does not work for adding
float test[][3] = {
    {1, 1, 5},
    {2, 1, 7},
    {3, 4, 18},
    {4, 2, 14},
    {0, 2, 6},
    {4, 0, 8}
};

float cost(float guess1, float guess2) {
    float result = 0.0f;
    for(int i = 0; i < test_len; i++) {
        float diff = test[i][2] - (guess1 * test[i][0] + guess2 * test[i][1]);
        result += diff*diff;
    }
    return result / test_len;
}

float rand_float() {
    float output = (float) rand() / (float) RAND_MAX;
    return output * 10.0f;
}

int main(void) {
    srand(69);
    float peram1 = rand_float();
    float peram2 = rand_float();

    float eps = 1e-3;
    float lrn_rate = 1e-2;

    // approcimate gradient using finite difference
    for(int i = 0; i < 200; i++) {
        float dperam1 = (cost(peram1 + eps, peram2) - cost(peram1, peram2))/eps;
        float dperam2 = (cost(peram1, peram2 + eps) - cost(peram1, peram2))/eps;
        peram1 -= lrn_rate * dperam1;
        peram2 -= lrn_rate * dperam2;
    }
    printf("%f, %f\n", peram1, peram2);

    return 0;
}
