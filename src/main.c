#include <stdio.h>
#include <stdlib.h>

float test[][2] = {
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {0, 0},
    {5, 10},
};

int main(void) {
    srand(69);
    float peram1 = (float) rand() / (float) RAND_MAX;
    peram1 *= 10.0f;
    printf("%f\n", peram1);

    return 0;
}
