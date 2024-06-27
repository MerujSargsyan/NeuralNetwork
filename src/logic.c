#include "aihelper.h"

#ifndef test_len
#define    test_len (int)(sizeof(test) / sizeof(test[0]))
#endif

float test[][3] =  {
    {0,0,0},
    {0,1,0},
    {1,0,0},
    {1,1,1}
};

float cost(Model m) {
    float result = 0.0f;
    for(int i = 0; i < test_len; i++) {
        float x1 = test[i][0];
        float x2 = test[i][1];
        Cell c = m.params[0];
        float y = sigmoid(x1 * c.weights[0] + x2 * c.weights[1] + c.bias);
        float diff = test[i][2] - y;
        result += diff*diff;
    }
    return result / test_len;
}

Model compute_gradient(Model m, float eps) {
    Model newM = init_model(1,2);
    float m_cost = cost(m);
    float saved;

    Cell c = m.params[0];
    for(int w = 0; w < c.weight_count; w++) {
        saved = c.weights[w];
        m.params[0].weights[w] += eps;
        newM.params[0].weights[w] = (cost(m) - m_cost)/eps;
        m.params[0].weights[w] = saved;
    }
    saved = c.bias;
    m.params[0].bias += eps;
    newM.params[0].bias = (cost(m) - m_cost)/eps;
    m.params[0].bias = saved;

    return newM;
}

int main(void) {
    srand(time(0));
    // one cell with 2 weights
    Model m = init_model(1, 2);
    
    float lrn_rate = 1e-1;
    float eps = 0.5;
    
    for(int i = 0; i < 100*100; i++) {
        Model newM = compute_gradient(m, eps);
        teach_model(&m, &newM, lrn_rate);
    }

    Cell c = m.params[0];
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d | %d: %f \n", i, j, sigmoid(i * c.weights[0] + j * c.weights[1] + c.bias));
        }
    }

    return 0;
}
