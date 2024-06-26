#include "aihelper.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

float sigmoid(float input) {
    return 1.0f/(1.0f + expf(input));
}

float rand_float() {
    return (float)rand() / (float)RAND_MAX;
}

void rand_init(float* arr, int arr_len) {
    srand(time(0));
    for(int i = 0; i < arr_len; i++) {
        arr[i] = rand_float();
    }
}

void teach_model(Model* learner, Model* teacher, float lrn_rate) {
    if(learner->param_count != teacher->param_count) return;
    for(int i = 0; i < learner->param_count; i++) {

        Cell* currentL = learner->params + i;
        Cell* currentT = teacher->params + i;
        if(currentL->weight_count != currentT->weight_count) {
            printf("Unmatched weight counts");
        }

        for(int j = 0; j < currentL->weight_count; j++) {
            currentL->weights[j] -= lrn_rate*currentT->weights[j];
        }

        currentT->bias -= currentL->bias;
    }
}

Model init_model(int param_count, int weight_count) {
    Model m;
    m.params = malloc(sizeof(Cell) * param_count);
    for(int i = 0; i < param_count; i++) {
        Cell c;
        c.weights = malloc(sizeof(float) * weight_count);
        rand_init(c.weights, c.weight_count);
        c.bias = rand_float();
        c.weight_count = weight_count;
        m.params[i] = c;
    }
    return m;
}



