#include "aihelper.h"

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
    if(learner->param_count != teacher->param_count) {
        printf("Parmeter size mistach\n");
        return;
    }
    for(int i = 0; i < learner->param_count; i++) {
        Cell* currentL = learner->params + i;
        Cell* currentT = teacher->params + i;

        if(currentL->weight_count != currentT->weight_count) {
            printf("Unmatched weight counts");
            return;
        }

        for(int j = 0; j < currentL->weight_count; j++) {
            currentL->weights[j] -= lrn_rate*currentT->weights[j];
        }
        currentL->bias -= currentT->bias;

    }
}

Model init_model(int param_count, int weight_count) {
    Model m;
    m.param_count = param_count;
    m.params = malloc(sizeof(Cell) * param_count);
    for(int i = 0; i < param_count; i++) {
        Cell c;
        c.weight_count = weight_count;
        c.weights = malloc(sizeof(float) * weight_count);
        rand_init(c.weights, c.weight_count);
        c.bias = rand_float();
        m.params[i] = c;
    }
    return m;
}

void print_model(Model m) {
    printf("------------------------------\n");
    for(int c = 0; c < m.param_count; c++) {
        printf("Cell %d:", c+1);
        Cell cell = m.params[c];
        for(int w = 0; w < cell.weight_count; w++) {
            printf(" weight %d: %f ", w+1, cell.weights[w]);
        }
        printf(" bias: %f", cell.bias);
        printf("\n");
    }
    printf("------------------------------\n");
}

void free_model(Model m) {
    for(int p = 0; p < m.param_count; p++) {
        free(m.params[p].weights);
    }
    free(m.params);
}
