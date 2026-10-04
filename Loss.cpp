#include "Loss.h"

double PerceptronError::error(int target, double output) {
    if (output >= 0.5) return target - 1;
    return target;
}

string PerceptronError::name() {
    return "Perceptron Error Loss";
}

double CrossEntropy::error(int target, double output) {
    return target - output;
}

string CrossEntropy::name() {
    return "Cross Entropy Loss";
}