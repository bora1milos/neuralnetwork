cmake_minimum_required(VERSION 3.10)

# set the project name
project(NeuralNetwork)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -pthread -std=c++14")

SET(SOURCES main.cpp 
            source/Neuron.cpp
            source/Layer.cpp
            source/Matrix.cpp
            source/NeuralNetwork.cpp
            source/util/Math.cpp
            source/util/Misc.cpp)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)