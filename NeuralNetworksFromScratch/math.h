#pragma once

#include <vector>
#include <assert.h>
#include <iostream>
#include "value.h"

typedef std::vector<std::vector<value*>> mat;

class Math {

public:

	Math() {};

	static mat matmul(mat a, mat b) 
	{
		int a_rows = a.size();
		int b_rows = b.size();
		int a_cols = a[0].size();
		int b_cols = b[0].size();

		assert(a_cols == b_rows);

		std::cout << a_rows << " " << b_rows;

		mat out;
		out.resize(a_rows);
		for (int i = 0; i < a_rows; i++) {
			out[i].resize(b_cols);
		}


		for (int row = 0; row < a_rows; row++)
		{
			for (int col = 0; col < b_cols; col++)
			{
				for (int i = 0; i < a_cols; i++)
				{
					*out[row][col] = *out[row][col] + *(a[row][i]) * *(b[i][col]);
				}
			}
		}
		return out;
	};

	//static mat relu(tensor* x);

	static value* categorical_cross_entropy(mat preds, std::vector<value*> labels)
	{
		assert(preds.size() == labels.size());

		value* loss = new value();

		for (int i = 0; i < preds.size(); i++) {
			value* log_pred = preds[i][0]->log();
			value* single_loss = new value(*log_pred * *(labels[i]));

			//std::cout << (preds[i][0].log() * labels[i]).data << '\n';
			loss = new value(*loss - *single_loss);
		}

		return loss;
	};

	//static value softmax(mat input);

	
};
