#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(ANNConfig config){}

NeuralNetwork::NeuralNetwork(std::vector<int> topology): m_topology{topology}
{
    m_topologySize = topology.size();
    for(auto i = 0; i < m_topologySize; ++i)
    {
        Layer *l = new Layer(topology.at(i));
        m_layers.push_back(l);
    }

    for(auto i = 0; i < m_topologySize - i; ++i)
    {
        Matrix *m = new Matrix(topology.at(i), topology.at(i +1), true);
        m_weightMatrices.push_back(m);
    }
}

NeuralNetwork::~NeuralNetwork()
{
    for(auto i = 0; i < m_topologySize; ++i)
    {
        delete m_layers[i];
    }

    for(auto i = 0; i < m_topologySize - i; ++i)
    {
        delete m_weightMatrices[i];
    }

}

void NeuralNetwork::setCurrentInput(std::vector<double> input)
{
    m_currentInput = input;  
    for (auto i = 0; i < input.size(); ++i)
    {
        m_layers.at(0)->setValue(i, input.at(i));
    }
}

void NeuralNetwork::printToconsole()
{
    for(auto i = 0; i <m_layers.size(); ++i)
    {
        std::cout << "LAYER: " << i << std::endl;
        if (i==0){
            Matrix *m = m_layers.at(i)->matrixifyVals();
            m->printToConsole();
        }
        else
        {
            Matrix* m = m_layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }
    }
}

void  NeuralNetwork::setErrorMSE(){}