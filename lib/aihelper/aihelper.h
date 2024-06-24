#ifndef AIHELPER_H
#define AIHELPER_h
typedef struct  {
    float* weights;
    float bias;
    int weight_count;
} Cell;

typedef struct {
    Cell* params;
    int param_count;
} Model;

Model compute_gradient(Model m, float eps, float (*cost)(Model));
float sigmoid(float input);
float rand_init(float* arr);
void teach_model(Model* learned, Model* teacher, float lrn_rate);

#endif
