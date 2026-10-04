#ifndef LOSS_H
#define LOSS_H

#include <string>
using namespace std;

class Loss {
public:
    virtual double error(int target, double output) = 0;
    virtual string name() = 0;
    virtual ~Loss() {}
};

class PerceptronError : public Loss {
public:
    double error(int target, double output) override;
    string name() override;
};

class CrossEntropy : public Loss {
public:
    double error(int target, double output) override;
    string name() override;
};

#endif