#include "Layer.h"
  
Layer::Layer(size_t size) : m_size{size}
{
    for (auto i = 0; i < m_size; ++i)
    {
        m_neurons.push_back(new Neuron(0.00));
    }

}

Layer::Layer(size_t size, FUNCTION_TYPE activationType) : m_size{size}
{
    for(auto i = 0; i < m_size; i++) 
    {
        m_neurons.push_back(new Neuron(0.000000000, activationType));
    }
}

Layer::~Layer()
{
    for (auto i = 0; i < m_size; ++i){
        delete m_neurons[i];
    }

    m_neurons.clear();
}

void Layer::setValue(int i, double v)
{
    m_neurons.at(i)->setVal(v);
}

Matrix* Layer::matrixifyVals()
{
    Matrix *m = new Matrix(1, m_neurons.size(), false);
    for (auto i = 0; i < m_size; ++i)
    {
        m->setValue(0, i, m_neurons.at(i)->getVal());
    }

    return m;
}

Matrix* Layer::matrixifyActivatedVals()
{
    Matrix *m = new Matrix(1, m_neurons.size(), false);
    for (auto i = 0; i < m_size; ++i)
    {
        m->setValue(0, i, m_neurons.at(i)->getActivatedVal());
    }

    return m;
}

Matrix* Layer::matrixifyDerivedVals()
{
        Matrix *m = new Matrix(1, m_neurons.size(), false);
    for (auto i = 0; i < m_size; ++i)
    {
        m->setValue(0, i, m_neurons.at(i)->getDerivedVal());
    }

    return m;
}

std::vector<double> Layer::getActivatedVals() 
{
  std::vector<double> ret;

  for(int i = 0; i < m_neurons.size(); i++) 
  {
    double v = m_neurons.at(i)->getActivatedVal();
    ret.push_back(v);
  }

  return ret;
}