#include "MultiLayerPerceptron.h"
#include <iostream>
#include <cstdlib>
using namespace std;

MultiLayerPerceptron::MultiLayerPerceptron(int inputSize, int hiddenSize, Activation* activation) {
    this->hiddenSize = hiddenSize;
    act = activation;
    hiddenWeights.resize(hiddenSize);
    hiddenBias.resize(hiddenSize);
    outputWeights.resize(hiddenSize);

    for (int j = 0; j < hiddenSize; j++) {
        hiddenWeights[j].resize(inputSize);

        for (int i = 0; i < inputSize; i++)
            hiddenWeights[j][i] = randomWeight();

        hiddenBias[j] = randomWeight();
        outputWeights[j] = randomWeight();
    }

    outputBias = randomWeight();
}

double MultiLayerPerceptron::randomWeight() {
    return (rand() % 201 - 100) / 100.0;
}

double MultiLayerPerceptron::forward(const vector<double>& input, vector<double>& hiddenOutput) {
    hiddenOutput.assign(hiddenSize, 0.0);

    for (int j = 0; j < hiddenSize; j++) {
        double sum = hiddenBias[j];

        for (int i = 0; i < input.size(); i++)
            sum += hiddenWeights[j][i] * input[i];

        hiddenOutput[j] = act->activate(sum);
    }

    double sum = outputBias;

    for (int j = 0; j < hiddenSize; j++)
        sum += outputWeights[j] * hiddenOutput[j];

    return act->activate(sum);
}

int MultiLayerPerceptron::predict(const vector<double>& input) {
    vector<double> hiddenOutput;

    if (forward(input, hiddenOutput) >= 0.5) return 1;
    return 0;
}

void MultiLayerPerceptron::update(const vector<double>& input, int target, double learningRate) {
    vector<double> hiddenOutput;
    double error = target - forward(input, hiddenOutput);

    for (int j = 0; j < hiddenSize; j++) {
        double delta = error * outputWeights[j] * hiddenOutput[j] * (1.0 - hiddenOutput[j]);

        for (int i = 0; i < input.size(); i++)
            hiddenWeights[j][i] += learningRate * delta * input[i];

        hiddenBias[j] += learningRate * delta;
    }

    for (int j = 0; j < hiddenSize; j++)
        outputWeights[j] += learningRate * error * hiddenOutput[j];

    outputBias += learningRate * error;
}

void MultiLayerPerceptron::trainEpoch(const Dataset& data, double learningRate) {
    vector<vector<double>> input = data.getInputs();
    vector<int> output = data.getOutputs();
    int n = input.size();

    for (int i = 0; i < n; i++)
        update(input[i], output[i], learningRate);
}

bool MultiLayerPerceptron::isConverged(const Dataset& data) {
    vector<vector<double>> input = data.getInputs();
    vector<int> output = data.getOutputs();
    int n = input.size();

    for (int i = 0; i < n; i++) {
        if (predict(input[i]) != output[i])
            return false;
    }

    return true;
}

void MultiLayerPerceptron::display() {
    cout << "Hidden Layer:" << endl;

    for (int j = 0; j < hiddenSize; j++) {
        cout << "  weights ";

        for (int i = 0; i < hiddenWeights[j].size(); i++)
            cout << hiddenWeights[j][i] << " ";

        cout << "| bias " << hiddenBias[j] << endl;
    }

    cout << "Output Layer: weights ";

    for (int j = 0; j < hiddenSize; j++)
        cout << outputWeights[j] << " ";

    cout << "| bias " << outputBias << endl;
}

MultiLayerPerceptron::~MultiLayerPerceptron() {
    delete act;
}