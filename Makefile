MiniPerceptron: main.o Activation.o Loss.o Dataset.o Perceptron.o PerceptronTrainer.o
	g++ main.o Activation.o Loss.o Dataset.o Perceptron.o PerceptronTrainer.o -o MiniPerceptron

main.o: src/main.cpp
	g++ -c src/main.cpp -Iinclude

Activation.o: src/Activation.cpp include/Activation.h
	g++ -c src/Activation.cpp -Iinclude

Loss.o: src/Loss.cpp include/Loss.h
	g++ -c src/Loss.cpp -Iinclude

Dataset.o: src/Dataset.cpp include/Dataset.h
	g++ -c src/Dataset.cpp -Iinclude

Perceptron.o: src/Perceptron.cpp include/Perceptron.h include/Activation.h include/Loss.h
	g++ -c src/Perceptron.cpp -Iinclude

PerceptronTrainer.o: src/PerceptronTrainer.cpp include/PerceptronTrainer.h include/Perceptron.h include/Dataset.h include/Loss.h
	g++ -c src/PerceptronTrainer.cpp -Iinclude

clean:
	rm -f *.o MiniPerceptron
