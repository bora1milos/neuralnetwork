#include "NeuralNetwork.h"
#include "util/Math.h"

#include <algorithm>

// Constructor
NeuralNetwork::NeuralNetwork(ANNConfig config)
 {
  m_config        = config;
  m_topology      = config.topology;
  m_topologySize  = config.topology.size();
  m_learningRate  = config.learningRate;
  m_momentum      = config.momentum;
  m_bias          = config.bias;

  m_hiddenActivationType  = config.hActivation;
  m_outputActivationType  = config.oActivation;
  m_costFunctionType      = config.cost;

  for(int i = 0; i < m_topologySize; i++) 
  {
    if(i > 0 && i < (m_topologySize - 1)) 
    {
      Layer *l  = new Layer(m_topology.at(i), m_hiddenActivationType);
      m_layers.push_back(l);
    } 
    else if(i == (m_topologySize - 1)) 
    {
      Layer *l  = new Layer(m_topology.at(i), m_outputActivationType);
      m_layers.push_back(l);
    } 
    else 
    {
      Layer *l  = new Layer( m_topology.at(i));
      m_layers.push_back(l);
    }
  }

  for(int i = 0; i < ( m_topologySize - 1); i++) {
    Matrix *m = new Matrix( m_topology.at(i),  m_topology.at(i + 1), true);

     m_weightMatrices.push_back(m);
  }

  // Initialize empty errors
  for(int i = 0; i <  m_topology.at( m_topology.size() - 1); i++) {
     m_errors.push_back(0.00);
     m_derivedErrors.push_back(0.00);
  }

   m_error = 0.00;
}

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

void NeuralNetwork::feedForward() {
  Matrix *a;  // Matrix of neurons to the left
  Matrix *b;  // Matrix of weights to the right of layer
  Matrix *c;  // Matrix of neurons to the next layer

  for(int i = 0; i < (this->m_topologySize - 1); i++) {
    a = getNeuronMatrix(i);
    b = getWeightMatrix(i);
    c = new Matrix(
          a->getNumRows(),
          b->getNumCols(),
          false
        );

    if(i != 0) {
      a = getActivatedNeuronMatrix(i);
    }

    utils::Math::multiplyMatrix(a, b, c);

    for(int c_index = 0; c_index < c->getNumCols(); c_index++) 
    {
        setNeuronValue(i + 1, c_index, c->getValue(0, c_index) + m_bias);
    }

    delete a;
    delete b;
    delete c;
  }
}

void NeuralNetwork::setErrors()
{
  switch(m_costFunctionType) 
  {
    case(COST_MSE): 
        this->setErrorMSE(); 
    break;
    
    default: 
        this->setErrorMSE(); 
    break;
  }
}

void NeuralNetwork::setErrorMSE() {
  int outputLayerIndex            = m_layers.size() - 1;
  vector<Neuron *> outputNeurons  = m_layers.at(outputLayerIndex)->getNeurons();

  m_error = 0.00;

  for(int i = 0; i < m_target.size(); i++) {
    double t  = m_target.at(i);
    double y  = outputNeurons.at(i)->getActivatedVal();

    m_errors.at(i)        = 0.5 * pow(abs((t - y)), 2);
    m_derivedErrors.at(i) = (y - t);

    m_error += m_errors.at(i);
  }
}

void NeuralNetwork::train(
  std::vector<double> input, 
  std::vector<double> target, 
  double bias, 
  double learningRate, 
  double momentum
) {
  m_learningRate  = learningRate;
  m_momentum      = momentum;
  m_bias          = bias;

  setCurrentInput(input);
  setCurrentTarget(target);

  feedForward();
  setErrors();
  backPropagation();
}

void NeuralNetwork::backPropagation() {
  vector<Matrix *> newWeights;
  Matrix *deltaWeights;
  Matrix *gradients;
  Matrix *derivedValues;
  Matrix *gradientsTransposed;
  Matrix *zActivatedVals;
  Matrix *tempNewWeights;
  Matrix *pGradients;
  Matrix *transposedPWeights;
  Matrix *hiddenDerived;
  Matrix *transposedHidden;

  /**
   *  PART 1: OUTPUT TO LAST HIDDEN LAYER
   */
  int indexOutputLayer  = m_topology.size() - 1;

  gradients = new Matrix(
                1,
                m_topology.at(indexOutputLayer),
                false
              );

  derivedValues = m_layers.at(indexOutputLayer)->matrixifyDerivedVals();

  for(int i = 0; i < m_topology.at(indexOutputLayer); i++) {
    double e  = m_derivedErrors.at(i);
    double y  = derivedValues->getValue(0, i);
    double g  = e * y;
    gradients->setValue(0, i, g);
  }

  // Gt * Z
  gradientsTransposed = gradients->transpose();
  zActivatedVals      = m_layers.at(indexOutputLayer - 1)->matrixifyActivatedVals();

  deltaWeights  = new Matrix(
                    gradientsTransposed->getNumRows(),
                    zActivatedVals->getNumCols(),
                    false
                  );

  ::utils::Math::multiplyMatrix(gradientsTransposed, zActivatedVals, deltaWeights);

  /**
   * COMPUTE FOR NEW WEIGHTS (LAST HIDDEN <-> OUTPUT)
   */
  tempNewWeights  = new Matrix(
                      m_topology.at(indexOutputLayer - 1),
                      m_topology.at(indexOutputLayer),
                      false
                    );

  for(int r = 0; r < m_topology.at(indexOutputLayer - 1); r++) {
    for(int c = 0; c < m_topology.at(indexOutputLayer); c++) {

      double originalValue  = m_weightMatrices.at(indexOutputLayer - 1)->getValue(r, c);
      double deltaValue     = deltaWeights->getValue(c, r);

      originalValue = m_momentum * originalValue;
      deltaValue    = m_learningRate * deltaValue;
      
      tempNewWeights->setValue(r, c, (originalValue - deltaValue));
    }
  }

  newWeights.push_back(new Matrix(*tempNewWeights));

  delete gradientsTransposed;
  delete zActivatedVals;
  delete tempNewWeights;
  delete deltaWeights;
  delete derivedValues;

  ///////////////////////////

  /**
   *  PART 2: LAST HIDDEN LAYER TO INPUT LAYER
   */
  for(int i = (indexOutputLayer - 1); i > 0; i--) {
    pGradients  = new Matrix(*gradients);
    delete gradients;

    transposedPWeights  = m_weightMatrices.at(i)->transpose();

    gradients   = new Matrix(
                    pGradients->getNumRows(),
                    transposedPWeights->getNumCols(),
                    false
                  );

    ::utils::Math::multiplyMatrix(pGradients, transposedPWeights, gradients);

    hiddenDerived       = m_layers.at(i)->matrixifyDerivedVals();

    for(int colCounter = 0; colCounter < hiddenDerived->getNumRows(); colCounter++) {
      double  g = gradients->getValue(0, colCounter) * hiddenDerived->getValue(0, colCounter);
      gradients->setValue(0, colCounter, g);
    }

    if(i == 1) {
      zActivatedVals  = m_layers.at(0)->matrixifyVals();
    } else {
      zActivatedVals  = m_layers.at(0)->matrixifyActivatedVals();
    }

    transposedHidden  = zActivatedVals->transpose();

    deltaWeights      = new Matrix(
                          transposedHidden->getNumRows(),
                          gradients->getNumCols(),
                          false
                        );

    ::utils::Math::multiplyMatrix(transposedHidden, gradients, deltaWeights);

    // update weights
    tempNewWeights  = new Matrix(
                        m_weightMatrices.at(i - 1)->getNumRows(),
                        m_weightMatrices.at(i - 1)->getNumCols(),
                        false
                      );

    for(int r = 0; r < tempNewWeights->getNumRows(); r++) {
      for(int c = 0; c < tempNewWeights->getNumCols(); c++) {
        double originalValue  = m_weightMatrices.at(i - 1)->getValue(r, c);
        double deltaValue     = deltaWeights->getValue(r, c);

        originalValue = m_momentum * originalValue;
        deltaValue    = m_learningRate * deltaValue;
        
        tempNewWeights->setValue(r, c, (originalValue - deltaValue));
      }
    }

    newWeights.push_back(new Matrix(*tempNewWeights));

    delete pGradients;
    delete transposedPWeights;
    delete hiddenDerived;
    delete zActivatedVals;
    delete transposedHidden;
    delete tempNewWeights;
    delete deltaWeights;
  }

  for(int i = 0; i < m_weightMatrices.size(); i++) {
    delete m_weightMatrices[i];
  }

  m_weightMatrices.clear();

  std::reverse(newWeights.begin(), newWeights.end());

  for(int i = 0; i < newWeights.size(); i++) {
    m_weightMatrices.push_back(new Matrix(*newWeights[i]));
    delete newWeights[i];
  }
}