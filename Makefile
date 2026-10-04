MiniPerceptron: main.o Activation.o Loss.o Dataset.o Perceptron.o PerceptronTrainer.o
	g++ main.o Activation.o Loss.o Dataset.o Perceptron.o PerceptronTrainer.o -o MiniPerceptron

main.o: main.cpp
	g++ -c main.cpp

Activation.o: Activation.cpp Activation.h
	g++ -c Activation.cpp

Loss.o: Loss.cpp Loss.h
	g++ -c Loss.cpp

Dataset.o: Dataset.cpp Dataset.h
	g++ -c Dataset.cpp

Perceptron.o: Perceptron.cpp Perceptron.h Activation.h Loss.h
	g++ -c Perceptron.cpp

PerceptronTrainer.o: PerceptronTrainer.cpp PerceptronTrainer.h Perceptron.h Dataset.h Loss.h
	g++ -c PerceptronTrainer.cpp

clean:
	rm -f *.o MiniPerceptron