#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>
#include <memory>
#include "json.h"
#include "NeuralNetwork.h"
#include "util/Misc.h"

using namespace std;
using json = nlohmann::json;

void printSyntax() {
  cout << "Syntax:" << endl;
  cout << "train [configFile]" << endl;
}

ANNConfig buildConfig(json configObject) {
  ANNConfig config;

  double learningRate   = configObject["learningRate"];
  double momentum       = configObject["momentum"];
  double bias           = configObject["bias"];
  int epoch             = configObject["epoch"];
  string trainingFile   = configObject["trainingData"];
  string labelsFile     = configObject["labelData"];
  string weightsFile    = configObject["weightsFile"];
  vector<int> topology  = configObject["topology"];

  FUNCTION_TYPE hActivation  = configObject["hActivation"];
  FUNCTION_TYPE oActivation  = configObject["oActivation"];

  config.topology     = topology;
  config.bias         = bias;
  config.learningRate = learningRate;
  config.momentum     = momentum;
  config.epoch        = epoch;
  config.hActivation  = hActivation;
  config.oActivation  = oActivation;
  config.trainingFile = trainingFile;
  config.labelsFile   = labelsFile;
  config.weightsFile  = weightsFile;

  return config;
}

int main(int argc, char **argv) {

  if(argc != 2) {
    printSyntax();
    exit(-1);
  }

  stringstream str; 
  ifstream stream(argv[1]);
  
  if(stream.is_open())
  {
    while(stream.peek() != EOF)
    {
      str << static_cast<char>(stream.get());
    }
    stream.close();
  }

  std::cout << str.str() << std::endl;

  std::unique_ptr<NeuralNetwork> n (new NeuralNetwork(buildConfig(json::parse(str.str()))));

  vector< vector<double> > trainingData = utils::Misc::fetchData(n->getConfig().trainingFile);
  vector< vector<double> > labelData    = utils::Misc::fetchData(n->getConfig().labelsFile);

  cout << "Training Data Size: " << trainingData.size() << endl;
  cout << "Label Data Size: " << labelData.size() << endl;

  for(int i = 0; i < n->getConfig().epoch; i++) {
    for(int tIndex = 0; tIndex < trainingData.size(); tIndex++) {
      vector<double> input    = trainingData.at(tIndex);
      vector<double> target   = labelData.at(tIndex);

      n->train(
        input,
        target,
        n->getConfig().bias,
        n->getConfig().learningRate,
        n->getConfig().momentum
      );
    }
    cout << n->getError() << endl;

    //cout << "Error at epoch " << i+1 << ": " << n->error << endl;
  }

  cout << "Done! Writing to " << n->getConfig().weightsFile << "..." << endl;
  n->saveWeights(n->getConfig().weightsFile);

  return 0;
}