#ifndef ACTIVATION_H
#define ACTIVATION_H

class Activation {
public:
    virtual double activate(double x) = 0;
    virtual ~Activation() {}
};

class StepActivation : public Activation {
public:
    double activate(double x) override;
};

class Sigmoid : public Activation {
public:
    double activate(double x) override;
};

#endif