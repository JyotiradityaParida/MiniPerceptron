#include <iostream>
#include <cstdlib>
#include "Activation.h"
#include "Dataset.h"
#include "Loss.h"
#include "Perceptron.h"
#include "PerceptronTrainer.h"
#include "MultiLayerPerceptron.h"
using namespace std;

template <typename Network>
void displayPredictions(Network& network, const Dataset& data) {
    for (int i=0;i<data.getInputs().size();i++) {
        cout << "[" << data.getInputs()[i][0] << ","
             << data.getInputs()[i][1] << "] -> "
             << network.predict(data.getInputs()[i])
             << " (expected " << data.getOutputs()[i] << ")" << endl;
    }
}

char getTrainingChoice() {
    char choice;

    while (true) {
        cout << endl;
        cout << "Enter n to show next epoch" << endl;
        cout << "Enter a to show all epochs till convergence" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        try {
            if (choice != 'a' && choice != 'n')
                throw "Invalid choice! Please enter a or n.";

            return choice;
        }
        catch (const char* message) {
            cout << message << endl;
        }
    }
}

void runGate(string gate, int activationChoice, Loss* loss) {
    Dataset data(gate);
    PerceptronTrainer trainer;

    Activation* activation;

    if (activationChoice == 1)
        activation = new StepActivation();
    else
        activation = new Sigmoid();

    Perceptron perceptron(2, activation);

    double learningRate = 0.1;
    int epoch = 0;

    cout << endl;
    cout << "========================================" << endl;
    cout << gate << " Gate - ";

    if (activationChoice == 1)
        cout << "Step Activation";
    else
        cout << "Sigmoid Activation";

    if (loss != NULL)
        cout << " - " << loss->name();

    cout << endl;
    cout << "========================================" << endl;

    cout << endl;
    cout << "Initial Weights and Bias (random)" << endl;
    perceptron.display();

    cout << endl;
    cout << "Initial Predictions" << endl;
    displayPredictions(perceptron, data);

    char mode = getTrainingChoice();

    while (!trainer.isConverged(perceptron, data)) {
        epoch++;

        cout << endl;
        cout << "Epoch " << epoch << endl;
        cout << "----------------" << endl;

        if (loss == NULL)
            trainer.trainEpoch(perceptron, data, learningRate);
        else
            trainer.trainEpoch(perceptron, data, learningRate, loss);

        cout << "Weights and Bias" << endl;
        perceptron.display();

        cout << endl;
        cout << "Predictions" << endl;
        displayPredictions(perceptron, data);

        if (trainer.isConverged(perceptron, data)) {
            cout << endl;
            cout << "MODEL CONVERGED!" << endl;

            cout << endl;
            cout << "Final Weights and Bias" << endl;
            perceptron.display();

            cout << endl;
            cout << "Final Predictions" << endl;
            displayPredictions(perceptron, data);

            break;
        }

        if (mode == 'n')
            mode = getTrainingChoice();
    }
}

void runNetwork(Dataset& data, string title) {
    srand(1);

    int hiddenSize = 3;
    MultiLayerPerceptron network(2, hiddenSize, new Sigmoid());

    double learningRate = 0.2;
    int epoch = 0;
    int maxEpoch = 10000;

    cout << endl;
    cout << "========================================" << endl;
    cout << title << " - 2-" << hiddenSize << "-1 Network with Hidden Layer" << endl;
    cout << "Sigmoid Activation" << endl;
    cout << "========================================" << endl;

    cout << endl;
    cout << "Initial Weights and Bias (random)" << endl;
    network.display();

    cout << endl;
    cout << "Initial Predictions" << endl;
    displayPredictions(network, data);

    char mode = getTrainingChoice();

    while (!network.isConverged(data) && epoch < maxEpoch) {
        epoch++;

        cout << endl;
        cout << "Epoch " << epoch << endl;
        cout << "----------------" << endl;

        network.trainEpoch(data, learningRate);

        cout << "Weights and Bias" << endl;
        network.display();

        cout << endl;
        cout << "Predictions" << endl;
        displayPredictions(network, data);

        if (mode == 'n')
            mode = getTrainingChoice();
    }

    cout << endl;

    if (network.isConverged(data))
        cout << "MODEL CONVERGED!" << endl;
    else
        cout << "MAX EPOCHS REACHED (" << maxEpoch << ") WITHOUT CONVERGING" << endl;

    cout << endl;
    cout << "Final Weights and Bias" << endl;
    network.display();

    cout << endl;
    cout << "Final Predictions" << endl;
    displayPredictions(network, data);
}

void runXor() {
    Dataset data("XOR");
    runNetwork(data, "XOR Gate");
}

void runCustom() {
    string pattern;

    cout << endl;
    cout << "Enter the output for inputs 00, 01, 10, 11 (e.g. 0001): ";
    cin >> pattern;

    if (pattern.size() != 4 || pattern.find_first_not_of("01") != string::npos) {
        cout << "Invalid output! Please enter exactly 4 digits using only 0 and 1." << endl;
        return;
    }

    vector<int> outputs;

    for (int i = 0; i < 4; i++)
        outputs.push_back(pattern[i] - '0');

    Dataset data(outputs);
    runNetwork(data, "Custom Output");
}

int main() {
    srand(1);

    int choice;

    while (true) {
        cout << endl;
        cout << "========== MiniPerceptron ==========" << endl;
        cout << "1. AND Gate" << endl;
        cout << "2. OR Gate" << endl;
        cout << "3. XOR Gate" << endl;
        cout << "4. Custom Output" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        try {
            if (choice == 5)
                break;

            if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
                throw "Invalid choice! Please enter 1, 2, 3 or 4.";

            if (choice == 3) {
                runXor();
                continue;
            }

            if (choice == 4) {
                runCustom();
                continue;
            }

            string gate;

            if (choice == 1)
                gate = "AND";
            else
                gate = "OR";

            int activationChoice = 0;
            Loss* loss = NULL;

            while (true) {
                cout << endl;
                cout << "Select Activation Function" << endl;
                cout << "1. Step Activation" << endl;
                cout << "2. Sigmoid Activation" << endl;
                cout << "Enter choice: ";
                cin >> activationChoice;

                try {
                    if (activationChoice != 1 && activationChoice != 2)
                        throw "Invalid choice! Please enter 1 or 2.";

                    if (activationChoice == 1)
                        break;

                    int lossChoice;

                    while (true) {
                        cout << endl;
                        cout << "Select Loss Function" << endl;
                        cout << "1. Perceptron Error Loss" << endl;
                        cout << "2. Cross Entropy Loss" << endl;
                        cout << "Enter choice: ";
                        cin >> lossChoice;

                        try {
                            if (lossChoice != 1 && lossChoice != 2)
                                throw "Invalid choice! Please enter 1 or 2.";

                            if (lossChoice == 1)
                                loss = new PerceptronError();
                            else
                                loss = new CrossEntropy();

                            break;
                        }
                        catch (const char* message) {
                            cout << message << endl;
                        }
                    }

                    break;
                }
                catch (const char* message) {
                    cout << message << endl;
                }
            }

            runGate(gate, activationChoice, loss);

            delete loss;
        }
        catch (const char* message) {
            cout << message << endl;
        }
    }
}