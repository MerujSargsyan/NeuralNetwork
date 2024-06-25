#ifndef AIHELPER_H
#define AIHELPER_H
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
void teach_model(Model* learner, Model* teacher, float lrn_rate);
Model init_model(int param_count, int weight_count);

#endif
