#include "Neuron.h"
#include <cstdlib> 

Neuron::Neuron(){}

Neuron::Neuron(double val) : m_val{val}
{

}

void Neuron::init()
{
    activate();
    derive();
}
        
Neuron::~Neuron(){}

void Neuron::activate()
{
    m_activatedVal = m_val / (1 + abs(m_val));
}

void Neuron::derive()
{
    m_derivedVal = m_activatedVal * (1 - m_activatedVal);
}

void Neuron::setVal(double val) 
{ 
    m_val = val; 
    init();
}