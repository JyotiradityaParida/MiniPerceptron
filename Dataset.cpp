#include "Dataset.h"

Dataset::Dataset(string gate) {
    inputs = {{0,0}, {0,1}, {1,0}, {1,1}};

    if (gate == "AND")
        outputs = {0,0,0,1};
    else if (gate == "OR")
        outputs = {0,1,1,1};
}

const vector<vector<double>>& Dataset::getInputs() const {
    return inputs;
}

const vector<int>& Dataset::getOutputs() const {
    return outputs;
}