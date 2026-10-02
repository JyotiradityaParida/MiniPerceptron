#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include "Activation.h"
using namespace std;

class Perceptron {
private:
    vector<double> weights;
    double bias;
    Activation* act;

public:
    Perceptron(int inputSize, Activation* activation);
    int predict(const vector<double>& input);
    void update(const vector<double>& input, int target, double learningRate);
    void display();
    ~Perceptron();
};

#endif