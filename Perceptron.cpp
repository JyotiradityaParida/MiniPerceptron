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