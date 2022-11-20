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
	int EPOCHS = 20;
	int NUM_IMAGES = 3;

	mat train_images = read_images("C:\\coding\\NeuralNetworksFromScratch\\data\\t10k-images-idx3-ubyte", NUM_IMAGES);
	std::vector<value*> train_labels = read_labels("C:\\coding\\NeuralNetworksFromScratch\\data\\t10k-labels-idx1-ubyte", NUM_IMAGES);

	assert(train_images.size() == train_labels.size());

	Linear layer1 = Linear(784, 256);
	Linear layer2 = Linear(256, 128);
	Linear layer3 = Linear(128, 10);

	std::vector<Linear> layers = { layer1, layer2, layer3 };


	Model model = Model(layers);


	for (int epoch = 0; epoch < EPOCHS; epoch++) {
		std::cout << "========= EPOCH: " << epoch + 1 << " ==============\n";
		mat preds = model.forward(train_images);

		mat softmax_preds = Math::softmax(preds);

		value* train_loss = Math::categorical_cross_entropy(softmax_preds, train_labels);

		std::cout << "train loss: " << train_loss->data << '\n';


		model.zero_grad();
		train_loss->backward();

		for (auto val: model.parameters())
		{

		 	val->data -= LEARNING_RATE * val->grad;
		}

	}










}


