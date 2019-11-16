cmake_minimum_required(VERSION 3.10)

# set the project name
project(NeuralNetwork)

SET(SOURCES main.cpp 
            source/Neuron.cpp
            source/Layer.cpp
            source/Matrix.cpp
            source/NeuralNetwork.cpp)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)