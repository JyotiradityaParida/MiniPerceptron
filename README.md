Mini Perceptron Project
We made a simple C++ OOP project that demonstrates neural networks learning Boolean logic gates from scratch.

Two models are implemented:

Perceptron — a single-layer network used for the linearly separable AND and OR gates.
MultiLayerPerceptron — a network with a hidden layer used for the non-linearly separable XOR gate and for arbitrary user-defined truth tables.
Two activation functions and two loss functions are supported-

Step Activation
Sigmoid Activation
Perceptron Error Loss
Cross Entropy Loss
Weights and bias start from random values and are updated from the prediction error. Training is displayed epoch by epoch until the model converges.

Directory Structure
MiniPerceptron/
│
├── include/
│   ├── Activation.h
│   ├── Dataset.h
│   ├── Loss.h
│   ├── Perceptron.h
│   └── PerceptronTrainer.h
├── src/
│   ├── Activation.cpp
│   ├── Dataset.cpp
│   ├── Loss.cpp
│   ├── Perceptron.cpp
│   ├── PerceptronTrainer.cpp
│   └── main.cpp
├── UML.png
├── report.pdf
├── Makefile
└── README.md

Features
AND / OR gates with a single-layer perceptron
XOR gate and custom truth tables with a multi-layer perceptron
Step / Sigmoid activation functions
Perceptron Error / Cross Entropy loss functions
Random initialization of weights and bias
Epoch-by-epoch or run-to-convergence training modes
Convergence detection and final weights/bias display
Object-oriented class structure
Separate modules for activation, loss, dataset, model and training
Usage
The program is interactive. On start it shows a menu:

========== MiniPerceptron ==========
1. AND Gate
2. OR Gate
3. XOR Gate
4. Custom Output
5. Exit
Enter choice:

Choice	Model	Notes
1. AND Gate	Single-layer perceptron	Asks for activation, then loss
2. OR Gate	Single-layer perceptron	Asks for activation, then loss
3. XOR Gate	2-3-1 network	Runs directly
4. Custom Output	2-3-1 network	Prompts for a 4-digit pattern
5. Exit	—	Quits the program
Before training starts you choose how the epochs are displayed:

n — run a single epoch, print its weights and predictions, then ask again
a — run every remaining epoch until convergence without pausing
Custom Output
Option 4 accepts any 4-digit binary pattern describing the outputs for the inputs 00, 01, 10, 11 in that order:

Enter the output for inputs 00, 01, 10, 11 (e.g. 0001):

So 0001 is AND, 0111 is OR, 0110 is XOR, 1000 is NOR, and 1110 is NAND. The pattern is trained with the same 2-3-1 network used for XOR. Patterns that a single perceptron cannot represent still work here because of the hidden layer.

Activation Functions
Step Activation
The Step Activation produces a binary output:

x >= 0  →  1
x < 0   →  0

Sigmoid Activation
The Sigmoid function is:

1 / (1+e^(-x))

It produces a value between 0 and 1. A threshold of 0.5 is used to obtain the binary prediction.

Training
During each epoch, every sample in the dataset is processed once and the weights and bias are updated according to the prediction error. The model is considered converged when all predictions match the expected outputs.

Single-layer	Multi-layer
Learning rate	0.1	0.2
Epoch limit	none	10000
Because the multi-layer network is not guaranteed to converge on an arbitrary pattern, it stops at the epoch limit and reports MAX EPOCHS REACHED instead of MODEL CONVERGED!.

Requirements
A C++ compiler (g++)
The Make utility
No external libraries are required
Setup Instructions
Clone the repository
Open a terminal inside the project folder
Run the command 'make' to compile necessary files
Run './MiniPerceptron' to run the program
Run the command 'make clean' to clean the compiled files
