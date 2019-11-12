#ifndef _MATRIX_H
#define _MATRIX_H

#include "Neuron.h"
#include <iostream>
#include <vector>

class Matrix
{
    public:
 
         Matrix(size_t numRows, size_t numCols, bool isRandom);

        ~Matrix();

        Matrix* transpose();

        void setvalue(size_t r, size_t c, double v);

        double getValue(size_t r, size_t c);

        double generateRandomNumber();

        void printToConsole();

        void init();

        size_t getNumRows(){return m_numRows;}
        size_t getNumCols(){return m_numCols;}

    private:

        size_t m_numRows; 
        size_t m_numCols;
        bool m_isRandom;

        std::vector <  std::vector<double> > m_values;

        Matrix* m_transpose;
};


#endif