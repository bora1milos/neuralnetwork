#include <iostream>
#include <memory>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>


#include "Neuron.h"
#include "Layer.h"
#include "Matrix.h"
#include "NeuralNetwork.h"

int main(int argc, char** arvg)
{
   std::vector<int> topology;
   std::vector<double> input;

   topology.push_back(3);
   topology.push_back(2);
   topology.push_back(3);


   input.push_back(1.0);
   input.push_back(0.0);
   input.push_back(1.0);

   std::unique_ptr<Neuron> n  {new Neuron(1.5)};
   std::unique_ptr<Layer> layer {new Layer(5)};
   std::unique_ptr<Matrix> matrix (new Matrix(3, 2, true));
   std::unique_ptr<NeuralNetwork> nn (new NeuralNetwork(topology));

   nn->setCurrentInput(input);


   std::cout <<  n->getVal() << std::endl;
   std::cout <<  n->getActivatedVal() << std::endl;
   std::cout <<  n->getDerivedVal() << std::endl;
   
   matrix->printToConsole();
   auto a = matrix->transpose();
   a->printToConsole();

   nn->printToconsole();

   return 0;
}