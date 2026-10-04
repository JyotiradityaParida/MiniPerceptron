#include "PerceptronTrainer.h"

void PerceptronTrainer::trainEpoch(Perceptron& perceptron, const Dataset& data, double learningRate) {
    vector<vector<double>> input = data.getInputs();
    vector<int> output = data.getOutputs();
    int n = input.size();
    for (int i=0;i <n; i++)
        perceptron.update(input[i], output[i], learningRate);
}

void PerceptronTrainer::trainEpoch(Perceptron& perceptron, const Dataset& data, double learningRate, Loss* loss) {
    vector<vector<double>> input = data.getInputs();
    vector<int> output = data.getOutputs();
    int n = input.size();
    for (int i=0; i < n; i++)
        perceptron.update(input[i], output[i], learningRate, loss);
}

bool PerceptronTrainer::isConverged(Perceptron& perceptron, const Dataset& data) {
    vector<vector<double>> input = data.getInputs();
    vector<int> output = data.getOutputs();
    int n = input.size();
    for (int i=0; i<n; i++) {
        if (perceptron.predict(input[i]) != output[i])
            return false;
    }

    return true;
}