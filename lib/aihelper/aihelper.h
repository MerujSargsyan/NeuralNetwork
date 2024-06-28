#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#ifndef AIHELPER_H
#define AIHELPER_H

/**
 * Each cell has a certain number of weights defined
 * by the weights array and a bias
 */
typedef struct  {
    float* weights;
    float bias;
    int weight_count;
} Cell;

/**
 * The model contains a certain number of brain cells
 * defined by the params array with the Cell struct
 * defined above
 */
typedef struct {
    Cell* params;
    int param_count;
} Model;

/**
 * The sigmoid function is a mathematical function
 * used to map a number into the range (0, 1) where
 * infinitely large inputs approach the output 1 and
 * infinitely small inputs approach the output 0
 *
 * @return number mapped to range (0,1)
 */
float sigmoid(float input);

/**
 * Uses a model with different (more ideal) input to
 * adjust the learner model using a learning rate
 *
 * requirements: 
 *      learner->param_count == teacher->param_count
 *      for each Cell,
 *          learner_cell->weight_count == teacher_cell->weight_count
 */
void teach_model(Model* learner, Model* teacher, float lrn_rate);

/**
 * Initializes a model with random values, with param_count cells
 * and each cell having weight_count number of weights
 */
Model init_model(int param_count, int weight_count);

/**
 * Prints the model in the format:
 * -----------------------------------------
 * Cell n: weight m: val_m... bias: cell_bias 
 * Cell k: ...
 */
void print_model(Model m);

void free_model(Model m);

#endif
