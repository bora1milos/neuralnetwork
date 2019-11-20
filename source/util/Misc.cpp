#include "util/Misc.h"

std::vector< std::vector<double> > utils::Misc::fetchData(std::string path) 
{
  std::vector< std::vector<double> > data;

  std::ifstream infile(path);

  std::string line;
  while(getline(infile, line)) 
  {
    std::vector<double>  dRow;
    std::string          tok;
    std::stringstream    ss(line);

    while(getline(ss, tok, ',')) 
    {

      dRow.push_back(stof(tok));
    }

    data.push_back(dRow);
  }

  return data;
}