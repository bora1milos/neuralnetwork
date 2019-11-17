#include "Neuron.h"
#include <cstdlib> 
#include <math.h> 

Neuron::Neuron(){}

Neuron::Neuron(double val) : m_activationType {TANH}
{
    setVal(val);
}

Neuron::Neuron(double val, FUNCTION_TYPE functionType) :  m_activationType {functionType}
{
   setVal(val); 
}

void Neuron::init()
{
    activate();
    derive();
}
        
Neuron::~Neuron(){}

void Neuron::activate()
{
    switch(m_activationType)
    {
        case TANH: 
        {
            m_activatedVal = tanh(m_val);
        }break; 
    
        case RELU: 
        {
            if(m_val > 0) 
            {
                m_activatedVal = m_val;
            } 
            else 
            {
             m_activatedVal = 0;
            }
        }break;

        case SIGM: 
        {
            m_activatedVal = (1 / (1 + exp(-m_val)));
        }break; 
        
        
        default:
        {
            m_activatedVal = (1 / (1 + exp(-m_val)));
        }break;
  }

}

void Neuron::derive()
{
     switch(m_activationType)
    {
        case TANH: 
        {
            m_derivedVal = (1.0 - (m_activatedVal * m_activatedVal));
        }
        break; 
  
        case RELU: 
        {
            if(m_val > 0) 
            {
                m_derivedVal = 1;
            } 
            else 
            {
                m_derivedVal = 0;
            }
        }
        break;

        case SIGM: 
        {
            m_derivedVal = (m_activatedVal * (1 - m_activatedVal));
        }
        break; 
        
        default:
        {
            m_derivedVal = (m_activatedVal * (1 - m_activatedVal));
        }
        break;
    }   
}

void Neuron::setVal(double val) 
{ 
    m_val = val; 
    init();
}