#include "aihelper.h"

#define test_len (int)(sizeof(test) / sizeof(test[0]))
#define WEIGHT_COUNT 2

// this does not work for adding
float test[][3] = {
    {1, 1, 5},
    {5, 2, 16},
    {3, 2, 12},
    {1, 8, 26},
    {2, 4, 16},
    {2, 2, 10},
    {1, 4, 14},
};

float sum(float a, float b) {
    return a + b;
}

float mult(float a, float b) {
    return a * b;
}

// isolate index of current guess
float cost(Model m, float (*operation)(float, float)) {
    float result = 0.0f;
    for(int i = 0; i < test_len; i++) {
        float total = 0.0f;
        Cell c = m.params[0];
        for(int w = 0; w < c.weight_count; w++) {
            float current = c.weights[w];
            total += operation(current, test[i][w]);
        }
        float diff = test[i][WEIGHT_COUNT] - total;
        result += diff*diff;
    }
    return result / test_len;
}

Model compute_gradient(Model m, float eps) {
    Model newM = init_model(1, WEIGHT_COUNT);
    newM.params[0].bias = 0;
    float c = cost(m, mult);
    float saved;

    Cell cell = m.params[0];
    for(int w = 0; w < cell.weight_count; w++) {
        saved = cell.weights[w];
        m.params[0].weights[w] += eps;
        newM.params[0].weights[w] = (cost(m, mult) - c)/eps;
        m.params[0].weights[w] = saved;
    }
    
    return newM;
}

int main(void) {
    srand(69);
    Model m = init_model(1, WEIGHT_COUNT);
    m.params[0].bias = 0;

    float eps = 1e-3;
    float lrn_rate = 1e-2;

    for(int i = 0; i < 100; i++) {
        Model newM = compute_gradient(m, eps);
        teach_model(&m, &newM, lrn_rate);
    }

    print_model(m);
    printf("%f\n", cost(m, mult));

    return 0;
}
