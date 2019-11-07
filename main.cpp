#include <iostream>
#include <memory>

#include "Neuron.h"
#include "Layer.h"

int main(int argc, char** arvg)
{
   std::unique_ptr<Neuron> n  {new Neuron(1.5)};
   std::unique_ptr<Layer> layer {new Layer(5)};
 
   std::cout <<  n->getVal() << std::endl;
   std::cout <<  n->getActivatedVal() << std::endl;
   std::cout <<  n->getDerivedVal() << std::endl;

   return 0;
}