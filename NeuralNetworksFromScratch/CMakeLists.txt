# CMakeList.txt : CMake project for NeuralNetworksFromScratch, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (NeuralNetworksFromScratch "NeuralNetworksFromScratch.cpp" "NeuralNetworksFromScratch.h" "reader.h" "reader.cpp" "neuron.cpp" "value.h" "value.cpp" "model.h" "model.cpp" "linear.h" "linear.cpp" "math.h" )

# TODO: Add tests and install targets if needed.
