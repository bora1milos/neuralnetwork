#include "Matrix.h"
#include <random>
#include <memory>

Matrix::~Matrix()
{
    if (m_transpose != nullptr)
        delete m_transpose;
}

Matrix::Matrix(size_t numRows, size_t numCols,  bool isRandom):m_numRows{numRows}, m_numCols{numCols}, m_isRandom{isRandom}, m_transpose{nullptr}
{
   init();
}

void Matrix::init()
{
    for (size_t  i = 0; i < m_numRows; ++i)
    {
       std::vector<double> colValues;
       for (size_t j = 0; j < m_numCols; ++j)
       {
           auto r = 0.0;
           if (m_isRandom)
           {
               r = generateRandomNumber();
           }
           colValues.push_back(r);
       }
       m_values.push_back(colValues); 
    }
}

Matrix* Matrix::transpose()
{
    m_transpose = new Matrix(m_numCols, m_numRows, false);

    for (size_t i = 0; i < m_numRows; ++i)
    {
        for (size_t j = 0; j < m_numCols; ++j)
        {
           m_transpose->setvalue(j, i , this->getValue(i, j)); 
        }
    }

    return m_transpose;
}

void Matrix::printToConsole()
{
    for (size_t  i = 0; i < m_numRows; ++i)
    {
        for (size_t j = 0; j < m_numCols; ++j)
       {
        std::cout << m_values.at(i).at(j) << "\t\t" ;
       }
       std::cout << std::endl;
    }
}

void Matrix::setvalue(size_t r, size_t c, double v)
{
   m_values.at(r).at(c) = v;
}

double Matrix::getValue(size_t r, size_t c)
{
    return m_values.at(r).at(c);
}

double Matrix::generateRandomNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0,1);

    return dis(gen);
}