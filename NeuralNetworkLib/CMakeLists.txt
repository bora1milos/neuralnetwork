cmake_minimum_required(VERSION 3.10)

project(NeuralNetworkLib)

SET(SOURCES source/Neuron.cpp source/Layer.cpp source/Matrix.cpp source/NeuralNetwork.cpp source/util/Math.cpp source/util/Misc.cpp)

# add the executable
add_library(NeuralNetworkLib ${SOURCES})

target_include_directories(NeuralNetworkLib PRIVATE include)