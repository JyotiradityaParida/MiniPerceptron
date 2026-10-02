#ifndef PERCEPTRONTRAINER_H
#define PERCEPTRONTRAINER_H

#include "Perceptron.h"
#include "Dataset.h"

class PerceptronTrainer {
public:
    void trainEpoch(Perceptron& perceptron, const Dataset& data, double learningRate);
    bool isConverged(Perceptron& perceptron, const Dataset& data);
};

#endif