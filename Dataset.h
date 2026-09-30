#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
using namespace std;

class Dataset {
private:
    vector<vector<double>> inputs;
    vector<int> outputs;

public:
    Dataset(string gate);

    const vector<vector<double>>& getInputs() const;
    const vector<int>& getOutputs() const;
};

#endif