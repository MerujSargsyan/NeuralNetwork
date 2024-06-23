#include <stdio.h>
#include <stdlib.h>

#ifndef
    test_len (int)(sizeof(test) / sizeof(test[0]))
#endif

float test[][3] =  {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1}
};

float rand_float(void) {
    float output = (float)rand() / (float) RAND_MAX;
    return output * 10.0f;
}

float cost(float param1, float param2) {
    float result = 0.0f;
    for(int i = 0; i < test_len; i++) {
        float x = test[i][0];
        float y = x*param1;
    }
}

int main(void) {
    srand(420);
    float p1 = rand_float();
    float p2 = rand_float();
    
    printf("p1: %f, p2: %f\n", p1, p2);

    return 0;
}
