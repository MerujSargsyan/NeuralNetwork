#include <stdio.h>
#include <stdlib.h>

#define test_len (int)(sizeof(test) / sizeof(test[0]))

// this does not work for adding
float test[][5] = {
    {0, 0, 0}, 
    {1, 1, 1},
    {0, 1, 0},
    {1, 0, 0},
};
int param_size = 2;

float sum(float a, float b) {
    return a + b;
}
float mult(float a, float b) {
    return a * b;
}

// isolate index of current guess
float cost(float* params, int idx, float eps, float (*operation)(float, float)) {
    float result = 0.0f;
    for(int i = 0; i < test_len; i++) {
        float total = 0.0f;
        for(int j = 0; j < param_size; j++) {
            float current = params[j];
            if(j == idx) {
                current += eps;
            }
            total += operation(current, test[i][j]);
        }
        float diff = test[i][param_size] - total;
        result += diff*diff;
    }
    return result / test_len;
}

float rand_float() {
    float output = (float) rand() / (float) RAND_MAX;
    return output * 10.0f;
}

float* generate_perams(int num) {
    float* arr = malloc(sizeof(float) * num);
    for(int i = 0; i < num; i++) {
        arr[i] = rand_float();
    }
    return arr;
}

void print_perams(float* perams) {
    for(int i = 0; i < param_size; i++) {
        printf("%f ", perams[i]);
    }
    printf("\n");
}

int main(void) {
    srand(69);
    float* perams = generate_perams(param_size);

    float eps = 1e-3;
    float lrn_rate = 1e-2;

    // approcimate gradient using finite difference
    for(int i = 0; i < 500; i++) {
        for(int j = 0; j < param_size; j++) {
            float dperam = (cost(perams, j, eps, sum) - cost(perams, -1, eps, sum)) / eps;
            perams[j] -= lrn_rate * dperam;
        }
    }

    print_perams(perams);
    free(perams);

    return 0;
}
