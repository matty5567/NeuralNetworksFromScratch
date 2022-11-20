#pragma once

#include <unordered_set>
#include <vector>
#include <functional>
#include <iostream>
#include <cmath>
#include<algorithm>

class value {

private:

    struct hash
    {
        size_t operator()(const value* value) const
        {
            return ((std::hash<float>()(value->data) ^ (std::hash<float>()(value->grad) << 1)));
        };
    };


    std::function<void(void)> _backward;
    std::string _name;


public:
    double data = 0.0f;
    float grad = 0.0f;
    std::vector<value*> children;

    value(float data, std::string name) : data(data), _name(name) {
        _backward = []() {};
        children = {};
        
    };
    
    value(value& val) : data(val.data), children(val.children), _backward(val._backward), _name(val._name){};

    value() { 
        data = 0.0f; 
        _backward = []() {};
        children = {};
    
    };


    value* operator + (value* other) {
        value* out = new value(data + other->data, "addition");

        out->children.push_back(this);
        out->children.push_back(other);

        out->_backward = [this, other, out]() mutable {
            this->grad += out->grad;
            other->grad += out->grad;
        };

        return out;
    }

    value* operator - (value* other) {
        value* out = new value(data - other->data, "subtraction");

        out->children.push_back(this);
        out->children.push_back(other);

        out->_backward = [this, other, out]() mutable {
            this->grad -= out->grad;
            other->grad -= out->grad;
        };

        return out;
    }


    value* operator * (value* other) {

        value* out = new value(data * other->data, "mult");

        out->children.push_back(this);
        out->children.push_back(other);


        out->_backward = [this, other, out]()  mutable {
            this->grad += other->data * out->grad;
            other->grad += this->data * out->grad;
        };

        return out;
    }

    bool operator==(const value& other) const {
        return (data == other.data && grad == other.grad && children == other.children);
    }

    value* leaky_relu(float leak) {
        
        float outval = this->data > 0 ? this->data : this->data*leak;
        value* out = new value(outval, "relu");

        out->children.push_back(this);

        out->_backward = [this, out, leak]() {
            this->grad +=  out->data > 0? out->data * out->grad : out->data * out->grad * leak;
        };

        return out;
    }



    value* log() {
        float out_val = std::log(this->data);
        value* out = new value(out_val, "log");

        out->children.push_back(this);

        out->_backward = [this, out]() {
            this->grad += (1 / this->data) * out->grad;
        };

        return out;
    }

    value* exp() {
        float out_val = std::exp(this->data);
        value* out = new value(out_val, "exp");

        out->children.push_back(this);

        out->_backward = [this, out, out_val]() {
            this->grad += out_val * out->grad;
        };
        return out;
    }

    value* pow(int power) {
        float out_val = std::pow(this->data, power);
        value* out = new value(out_val, "pow");

        out->children.push_back(this);

        out->_backward = [this, out, power]() {
            this->grad += (power * std::pow(this->data, power-1)) * out->grad;
        };
        return out;
    }


    void backward() {

        std::vector<value*> topo;
        std::unordered_set<value*> visited{};

        std::function<void(value*)> build_topo = [&](value* v) {
            if (!visited.count(v)) {
                visited.insert(v);
                
                for (value* child : v->children) {

                    build_topo(child);
                }
                topo.push_back(v);
            }
        };


        build_topo(this);

        this->grad = 1.0f;
        std::reverse(topo.begin(), topo.end());
        for (auto value : topo) {
            value->_backward();
        }
    }
};




