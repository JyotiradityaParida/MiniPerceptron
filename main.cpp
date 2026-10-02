#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "Activation.h"
#include "Dataset.h"
#include "Perceptron.h"
#include "PerceptronTrainer.h"
using namespace std;

class InvalidChoiceException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid choice! Please enter 1 or 2.";
    }
};

void displayPredictions(Perceptron& perceptron, const Dataset& data) {
    for (int i=0;i<data.getInputs().size();i++) {
        cout << "[" << data.getInputs()[i][0] << ","
             << data.getInputs()[i][1] << "] -> "
             << perceptron.predict(data.getInputs()[i])
             << " (expected " << data.getOutputs()[i] << ")" << endl;
    }
}

void waitForContinue() {
    char choice;
    cout << endl;
    cout << "Press n to continue: ";
    cin >> choice;
    cout << endl;
}

void runGate(string gate, int activationChoice) {
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

    cout << endl;
    cout << "========================================" << endl;

    cout << endl;
    cout << "Initial Weights and Bias (random)" << endl;
    perceptron.display();

    cout << endl;
    cout << "Initial Predictions" << endl;
    displayPredictions(perceptron, data);

    waitForContinue();

    while (!trainer.isConverged(perceptron, data)) {
        epoch++;

        cout << "Epoch " << epoch << endl;
        cout << "----------------" << endl;

        trainer.trainEpoch(perceptron, data, learningRate);

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

            waitForContinue();
            break;
        }

        waitForContinue();
    }
}

int main() {
    srand(1);

    int choice;

    while (true) {
        cout << endl;
        cout << "========== MiniPerceptron ==========" << endl;
        cout << "1. AND Gate" << endl;
        cout << "2. OR Gate" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        try {
            if (choice == 3)
                break;

            if (choice != 1 && choice != 2)
                throw InvalidChoiceException();

            string gate;

            if (choice == 1)
                gate = "AND";
            else
                gate = "OR";

            cout << endl;
            cout << "Select Activation Function" << endl;
            cout << "1. Step Activation" << endl;
            cout << "2. Sigmoid Activation" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            if (choice != 1 && choice != 2)
                throw InvalidChoiceException();

            runGate(gate, choice);
        }
        catch (const InvalidChoiceException& e) {
            cout << e.what() << endl;
        }
    }
}