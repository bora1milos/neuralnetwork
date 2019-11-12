#ifndef _NEURAL_NETWORK_H
#define _NEURAL_NETWORK_H

#include "Layer.h"
#include "Matrix.h"

#include <iostream>
#include <vector>

class NeuralNetwork
{
    public:
        NeuralNetwork();

        explicit NeuralNetwork(std::vector<int> topology);

        void setCurrentInput(std::vector<double> input);

        void printToconsole();

        ~NeuralNetwork();

    private:
        size_t m_topologySize;
        std::vector<int> m_topology;
        std::vector<Layer*> m_layers;
        std::vector<Matrix*> m_weightMatrix;
        std::vector<double> m_currentInput;
};


#endif