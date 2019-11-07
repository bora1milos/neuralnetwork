#include "Layer.h"

Layer::Layer(){}
   
Layer::Layer(size_t size) : m_size{size}
{
    for (auto i = 0; i < m_size; ++i){
        m_neurons.push_back(new Neuron(0.00));
    }
}

Layer::~Layer()
{
    for (auto i = 0; i < m_size; ++i){
        delete m_neurons[i];
    }

    m_neurons.clear();
}