#include "Perceptron.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Perceptron::Perceptron(int inputSize, Activation* activation) {
    weights.resize(inputSize);

    for (int i=0;i<inputSize;i++)
        weights[i] = (rand() % 201 - 100) / 100.0;

    bias = (rand() % 201 - 100) / 100.0;
    act = activation;
}

int Perceptron::predict(const vector<double>& input) {
    if (output(input) >= 0.5) return 1;
    return 0;
}

double Perceptron::output(const vector<double>& input) {
    double sum = bias;

    for(int i=0; i<input.size(); i++)
        sum += weights[i] * input[i];

    return act->activate(sum);
}

void Perceptron::adjust(const vector<double>& input, double error, double learningRate) {
    for (int i=0;i<input.size();i++)
        weights[i] += learningRate * error * input[i];

    bias += learningRate * error;
}

void Perceptron::update(const vector<double>& input, int target, double learningRate) {
    adjust(input, target - predict(input), learningRate);
}

void Perceptron::update(const vector<double>& input, int target, double learningRate, Loss* loss) {
    adjust(input, loss->error(target, output(input)), learningRate);
}

void Perceptron::display() {
    cout << "Weights: ";

    for (double weight : weights)
        cout << weight << " ";

    cout << endl;
    cout << "Bias: " << bias << endl;
}

Perceptron::~Perceptron() {
    delete act;
}

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