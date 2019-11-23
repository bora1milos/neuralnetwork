#include <vector>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>
#include "json.h"
#include "NeuralNetwork.h"
#include "util/Misc.h"

using namespace std;
using json = nlohmann::json;

void printSyntax() {
  cout << "Syntax:" << endl;
  cout << "autoencoder_classify [configFile]" << endl;
}

int main(int argc, char **argv) {

  if(argc != 2) {
    printSyntax();
    exit(-1);
  }

  ANNConfig annConfig;

  ifstream configFile(argv[1]);
  string str((std::istreambuf_iterator<char>(configFile)),
              std::istreambuf_iterator<char>());

  auto config = json::parse(str);

  annConfig.bias           = config["bias"];
  annConfig.weightsFile    = config["weightsFile"];
  annConfig.testFile       = config["testFile"]; 

  vector<int> topology  = config["topology"];

  cout << "Topology: " << endl;
  for(int i = 0; i < topology.size(); i++) {
    cout << topology.at(i) << "\t";
  }
  cout << endl;

  NeuralNetwork *n  = new NeuralNetwork(annConfig);
  n->loadWeights(annConfig.weightsFile);

  vector< vector<double> > testData = utils::Misc::fetchData(annConfig.testFile);

  for(int i = 0; i < testData.size(); i++) {
    n->setCurrentInput(testData.at(i));
    n->setCurrentTarget(testData.at(i));
    n->feedForward();
    n->setErrors();

    double error = n->getError();
    //cout << "Error for datapoint " << i << ": " << error << endl;
    cout << error << endl;
  }

  return 0;
}