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

        Matrix *getNeuronMatrix(int index) { return m_layers.at(index)->matrixifyVals(); }
        Matrix *getActivatedNeuronMatrix(int index) { return m_layers.at(index)->matrixifyActivatedVals(); }
        Matrix *getDerivedNeuronMatrix(int index) { return m_layers.at(index)->matrixifyDerivedVals(); }
        //Matrix *getWeightMatrix(int index) { return new Matrix(m_weightMatrices.at(index)); }

    private:
        size_t m_topologySize;
        std::vector<int> m_topology;
        std::vector<Layer*> m_layers;
        std::vector<Matrix*> m_weightMatrices;
        std::vector<double> m_currentInput;
        std::vector<double> m_inputs;
        std::vector<double> m_targets;
        double m_error;
        std::vector<double> m_errors;
        std::vector<double> m_historicalError;
    

};


#endif