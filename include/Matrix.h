#ifndef _MATRIX_H
#define _MAYTIX_H

#include "Neuron.h"
#include <iostream>
#include <vector>

class Matrix
{
    public:
        Matrix();

        explicit Matrix(unsigned int numRows, unsigned int numCols, bool isRandom);

        ~Matrix();

        Matrix* transpose();

        void setvalue(unsigned int r, unsigned int c, double v);

        double getValue(unsigned int r, unsigned int c);

        double generateRandomNumber();

    private:

        unsigned int m_numRows; 
        unsigned int m_numCols;
        bool m_isRandom;

        std::vector <  std::vector<double> > m_values;
};


#endif