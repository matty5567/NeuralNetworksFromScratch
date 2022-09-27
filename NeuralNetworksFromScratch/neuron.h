#include "value.h"
#include <time.h>

class Neuron {

public:
    Neuron(int input_size);

    value* forward(std::vector<value*> input);

    std::vector<value*> parameters(){
        std::vector<value*> params = weights;
        params.push_back(bias);
        return params;
    };

private: 

    std::vector<value*> weights;
    value* bias = new value(1.0f);

};