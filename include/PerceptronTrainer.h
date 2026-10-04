#ifndef PERCEPTRONTRAINER_H
#define PERCEPTRONTRAINER_H

#include "Perceptron.h"
#include "Dataset.h"

class PerceptronTrainer {
public:
    void trainEpoch(Perceptron& perceptron, const Dataset& data, double learningRate);
    void trainEpoch(Perceptron& perceptron, const Dataset& data, double learningRate, Loss* loss);
    bool isConverged(Perceptron& perceptron, const Dataset& data);
    void trainEpoch(MultiLayerPerceptron& network, const Dataset& data, double learningRate);
    bool isConverged(MultiLayerPerceptron& network, const Dataset& data);
};

#endif