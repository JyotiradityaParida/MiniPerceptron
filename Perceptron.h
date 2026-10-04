#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include "Activation.h"
#include "Loss.h"
using namespace std;

class Perceptron {
private:
    vector<double> weights;
    double bias;
    Activation* act;

    void adjust(const vector<double>& input, double error, double learningRate);

public:
    Perceptron(int inputSize, Activation* activation);
    double output(const vector<double>& input);
    int predict(const vector<double>& input);
    void update(const vector<double>& input, int target, double learningRate);
    void update(const vector<double>& input, int target, double learningRate, Loss* loss);
    void display();
    ~Perceptron();
};

#endif