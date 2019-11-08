#include "Matrix.h"

Matrix::Matrix()
{}

Matrix::~Matrix()
{}

Matrix::Matrix(unsigned int numRows, unsigned int numCols,  bool isRandom):m_numRows{numRows}, m_numCols{numCols}, m_isRandom{isRandom}
{}

Matrix* Matrix::transpose(){return this;}

void Matrix::setvalue(unsigned int r, unsigned int c, double v){}

double Matrix::getValue(unsigned int r, unsigned int c){return 5.0;}

double Matrix::generateRandomNumber(){return 6.0;}