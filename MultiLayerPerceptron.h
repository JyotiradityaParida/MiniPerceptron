#ifndef MULTILAYERPERCEPTRON_H
#define MULTILAYERPERCEPTRON_H

#include <vector>
#include "Activation.h"
#include "Dataset.h"
using namespace std;

class MultiLayerPerceptron {
private:
    int hiddenSize;
    vector<vector<double>> hiddenWeights;
    vector<double> hiddenBias;
    vector<double> outputWeights;
    double outputBias;
    Activation* act;

    double randomWeight();
    double forward(const vector<double>& input, vector<double>& hiddenOutput);

public:
    MultiLayerPerceptron(int inputSize, int hiddenSize, Activation* activation);
    int predict(const vector<double>& input);
    void update(const vector<double>& input, int target, double learningRate);
    void trainEpoch(const Dataset& data, double learningRate);
    bool isConverged(const Dataset& data);
    void display();
    ~MultiLayerPerceptron();
};

#endif