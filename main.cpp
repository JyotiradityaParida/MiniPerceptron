#include <iostream>
#include <cstdlib>
#include "Activation.h"
#include "Dataset.h"
#include "Perceptron.h"
#include "PerceptronTrainer.h"
using namespace std;

void displayPredictions(Perceptron& perceptron, const Dataset& data) {
    for (int i=0;i<data.getInputs().size();i++) {
        cout << "[" << data.getInputs()[i][0] << ","
             << data.getInputs()[i][1] << "] -> "
             << perceptron.predict(data.getInputs()[i])
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

    char mode = getTrainingChoice();

    while (!trainer.isConverged(perceptron, data)) {
        epoch++;

        cout << endl;
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

            break;
        }

        if (mode == 'n')
            mode = getTrainingChoice();
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
                throw "Invalid choice! Please enter 1 or 2.";

            string gate;

            if (choice == 1)
                gate = "AND";
            else
                gate = "OR";

            while (true) {
                cout << endl;
                cout << "Select Activation Function" << endl;
                cout << "1. Step Activation" << endl;
                cout << "2. Sigmoid Activation" << endl;
                cout << "Enter choice: ";
                cin >> choice;

                try {
                    if (choice != 1 && choice != 2)
                        throw "Invalid choice! Please enter 1 or 2.";

                    break;
                }
                catch (const char* message) {
                    cout << message << endl;
                }
            }

            runGate(gate, choice);
        }
        catch (const char* message) {
            cout << message << endl;
        }
    }
}