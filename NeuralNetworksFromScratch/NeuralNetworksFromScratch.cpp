// NeuralNetworksFromScratch.cpp : Defines the entry point for the application.
//

#include "NeuralNetworksFromScratch.h"

#include <iostream>
#include "reader.h"
#include "assert.h"
#include "math.h"
#include "linear.h"
#include "model.h"

int main() {
	float LEARNING_RATE = 0.001f;
	int EPOCHS = 10;

	mat train_images = read_images("C:\\coding\\NeuralNetworksFromScratch\\data\\t10k-images-idx3-ubyte");
	std::vector<value*> train_labels = read_labels("C:\\coding\\NeuralNetworksFromScratch\\data\\t10k-labels-idx1-ubyte");

	assert(train_images.size() == train_labels.size());

	Linear layer1 = Linear(784, 1);
	//Linear layer2 = Linear(10, 1);


	std::vector<Linear> layers = { layer1 };


	Model model = Model(layers);


	for (int epoch = 0; epoch < EPOCHS; epoch++) {
		std::cout << "========= EPOCH: " << epoch + 1 << " ==============\n";
		mat preds = model.forward(train_images);

		model.zero_grad();

		value* train_loss = Math::categorical_cross_entropy(preds, train_labels);

		std::cout << "train loss" << train_loss->data << '\n';

		// for (auto x: train_loss.children){std::cout << x.grad << " ";}
		// std::cout << '\n';

		train_loss->backward();

		// for (auto x: train_loss.children){std::cout << x.grad << ' ';}
		// std::cout << '\n' << '\n';

		for (auto val: model.parameters())
		{
			//std::cout << "---------------" << '\n';
			//std::cout << val->data << '\n';
		 	val->data -= LEARNING_RATE * val->grad;
			//std::cout << val->data << '\n';
		}

		//std::cout << train_loss.data << '\n';
	}










}


