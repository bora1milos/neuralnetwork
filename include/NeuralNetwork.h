#ifndef _NEURAL_NETWORK_H
#define _NEURAL_NETWORK_H

#include "Layer.h"
#include "Matrix.h"

#include <iostream>
#include <vector>

enum ANN_COST { COST_MSE };

typedef struct {
  std::vector<int> topology;
  double bias;
  double learningRate;
  double momentum;
  int epoch;
  FUNCTION_TYPE hActivation;
  FUNCTION_TYPE oActivation;
  ANN_COST cost;
  std::string trainingFile;
  std::string labelsFile;
  std::string weightsFile;
}ANNConfig;

class NeuralNetwork
{
    public:
        NeuralNetwork(ANNConfig config);

        explicit NeuralNetwork(std::vector<int> topology);

        void setCurrentTarget(std::vector<double> target) { m_target = target; };
        void setCurrentInput(std::vector<double> input);
        void train(std::vector<double> input, std::vector<double> target, double bias, double learningRate, double momentum);
        void feedForward();
        void backPropagation();
        void setErrors();

        void printToconsole();

        ~NeuralNetwork();

        std::vector<double> getActivatedVals(int index) { return m_layers.at(index)->getActivatedVals(); }
        void setNeuronValue(int indexLayer, int indexNeuron, double val) { m_layers.at(indexLayer)->setValue(indexNeuron, val); }



        Matrix *getNeuronMatrix(int index) { return m_layers.at(index)->matrixifyVals(); }
        Matrix *getActivatedNeuronMatrix(int index) { return m_layers.at(index)->matrixifyActivatedVals(); }
        Matrix *getDerivedNeuronMatrix(int index) { return m_layers.at(index)->matrixifyDerivedVals(); }
        Matrix *getWeightMatrix(int index) { return m_weightMatrices.at(index); }

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

          
        FUNCTION_TYPE m_hiddenActivationType  = RELU;
        FUNCTION_TYPE m_outputActivationType  = SIGM;

        int m_costFunctionType      = COST_MSE;

        double m_bias  { 1 };
        double m_momentum;
        double m_learningRate;

        std::vector<Matrix *> m_gradientMatrices;

        std::vector<double> m_input;
        std::vector<double> m_target;
        std::vector<double> m_derivedErrors;

        void setErrorMSE();

        ANNConfig m_config;

};


#endif