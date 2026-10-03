# Mini Perceptron Project

We made a simple C++ OOP project that demonstrates a single-layer perceptron learning basic Boolean logic gates.

The project supports the AND and OR logic gates and uses two activation functions:
- Step Activation
- Sigmoid Activation

The perceptron starts with randomly initialized weights and bias, and learns by updating them based on prediction errors. The training process is displayed epoch by epoch until the model converges.

## Directory Structure

```text
MiniPerceptron/
│
├── Activation.h
├── Activation.cpp
├── Dataset.h
├── Dataset.cpp
├── Perceptron.h
├── Perceptron.cpp
├── PerceptronTrainer.h
├── PerceptronTrainer.cpp
├── main.cpp
├── Makefile
└── README.md
```

## Features

- AND/OR logic gates
- Step/Sigmoid activation functions
- Random initialization of weights and bias
- Epoch-by-epoch training
- Final weights and bias display
- Object-oriented class structure
- Separate modules for activation, dataset, perceptron and training

## Perceptron Model

The perceptron calculates a weighted sum of its inputs:

```text
z = w1*x1 + w2*x2 + bias
```

The weighted sum is passed through an activation function to produce the output.

The prediction is compared with the expected output and the weights and bias are updated using the prediction error.

## Supported Logic Gates

### AND Gate

```text
Input       Output

0 0    →      0
0 1    →      0
1 0    →      0
1 1    →      1
```

### OR Gate

```text
Input       Output

0 0    →      0
0 1    →      1
1 0    →      1
1 1    →      1
```

## Activation Functions

### Step Activation

The Step Activation produces a binary output:

```text
x >= 0  →  1
x < 0   →  0
```

### Sigmoid Activation

The Sigmoid function is:

```text
1 / (1+e^(-x))
```

It produces a value between 0 and 1. A threshold of 0.5 is used to obtain the binary prediction.

## Training

During each epoch, the training data is processed and the weights and bias are updated according to the prediction error. When all predictions match the expected outputs, the model is considered converged.

## Requirements

- Make utility
- No external libraries are required

## Setup Instructions

- Clone the repository
- Open a terminal inside the project folder
- Run the command 'make' to compile necessary files
- Run './MiniPerceptron' to run the program
- Run the command 'make clean' to clean the compiled files
