cmake_minimum_required(VERSION 3.10)

# set the project name
project(NeuralNetwork)

add_subdirectory(NeuralNetworkLib)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -pthread -std=c++14")

# add the executable
add_executable(train train.cpp)
add_executable(run run.cpp)

target_link_libraries(train NeuralNetworkLib)
target_link_libraries(run  NeuralNetworkLib)
target_include_directories(train PUBLIC ${PROJECT_SOURCE_DIR}/NeuralNetworkLib/include)
target_include_directories(run PUBLIC ${PROJECT_SOURCE_DIR}/NeuralNetworkLib/include)