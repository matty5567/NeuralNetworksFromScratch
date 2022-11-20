#pragma once

#include <vector>
#include <assert.h>
#include <iostream>
#include "value.h"

typedef std::vector<std::vector<value*>> mat;

class Math {

public:

	Math() {};

	static value* categorical_cross_entropy(mat preds, std::vector<value*> labels)
	{
		assert(preds.size() == labels.size());

		value* loss = new value(0.0f, "loss");

		// iterate over training examples in batch
		for (int img = 0; img < preds.size(); img++) {

			int correctPred = labels[img]->data;
			loss = *loss - preds[img][correctPred]->log();
		}
		return loss;
	};

	static mat softmax(mat input) 
	{

		int num_categories = input[0].size();

		mat out;
		out.resize(input.size());

		for (int i=0; i<input.size(); i++)
		{
			
			value* exp_sum = new value();
			
			for (value* prob : input[i])
			{
				value* exp_prob = prob->exp();
				exp_sum = *exp_sum + exp_prob;
			}

			for (int idx=0; idx < num_categories; idx++)
			{
				out[i].resize(num_categories);
				value* exp_pred = input[i][idx]->exp();
				value* recp_total_exp = exp_sum->pow(-1);
				out[i][idx] = *exp_pred * recp_total_exp;
			}
		}
		return out;
	}
};
