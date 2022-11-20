#pragma once
#include <string>
#include <iostream>
#include <fstream> 
#include <vector>
#include "value.h"

typedef std::vector<std::vector<value*>> mat;


int reverseINT(int i);

mat read_images(const std::string& file_loc, int training_count);
std::vector<value*> read_labels(const std::string& file_loc, int training_count);
