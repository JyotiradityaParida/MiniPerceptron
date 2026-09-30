#include "Activation.h"
#include <cmath>

double StepActivation::activate(double x) {
    if (x >= 0) return 1;
    return 0;
}

double Sigmoid::activate(double x) {
    return 1.0 / (1.0 + exp(-x));
}