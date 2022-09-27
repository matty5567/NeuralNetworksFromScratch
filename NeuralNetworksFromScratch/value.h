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


    std::function<void(void)> _backward = []() {};


public:
    float data;
    float grad = 0.0f;
    std::vector<value*> children = {};

    value(float data) : data(data) {};
    value(value& val) 
    {
        this->data = val.data;
        this->children = val.children;
    };
    value() { data = 0.0f; };


    value operator + (value& other) {
        value* out = new value(data + other.data);

        out->children.push_back(this);
        out->children.push_back(&other);

        out->_backward = [this, &other, &out]() mutable {
            this->grad += out->grad;
            other.grad += out->grad;
        };

        return *out;
    }

    value operator - (value& other) {
        value* out = new value(data - other.data);

        out->children.push_back(this);
        out->children.push_back(&other);

        out->_backward = [this, &other, &out]() mutable {
            this->grad -= out->grad;
            other.grad -= out->grad;
        };

        return *out;
    }


    value operator * (value& other) {

        value* out = new value(data * other.data);

        out->children.push_back(this);
        out->children.push_back(&other);


        out->_backward = [this, &other]()  mutable {
            this->grad += other.grad;
            other.grad += this->grad;
        };

        return *out;
    }

    bool operator==(const value& other) const {
        return (data == other.data && grad == other.grad && children == other.children);
    }

    value* log() {
        float out_val = std::log(this->data);
        value* out = new value(out_val);

        out->children.push_back(this);

        out->_backward = [this, &out]() {
            this->grad += 1 / out->data;
        };

        return out;
    }

    value exp() {
        float out_val = std::exp(this->data);
        value* out = new value(out_val);

        out->children.push_back(this);

        out->_backward = [this, &out]() {
            this->grad += std::exp(out->data);
        };
        return *out;
    }


    void backward() {

        std::vector<value*> topo = {};
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




