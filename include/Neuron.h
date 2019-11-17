#ifndef _NEURON_H
#define _NEURON_H

enum FUNCTION_TYPE{ TANH = 1, RELU = 2, SIGM = 3};

#include <iostream>

class Neuron
{
    public:
        Neuron();
        explicit Neuron(double val);
        explicit Neuron(double val, FUNCTION_TYPE functionType);
        ~Neuron();

        // fast sigmond function
        // f(x) = x / (1 |x|)
        void activate();

        // Derivative for fast sigmod function
        // f' (x) = f (x) * (1 - f(x))
        void derive();

        void init();

        // Getters
        const double getVal() const {return m_val;}
        const double getActivatedVal() const {return m_activatedVal;}
        const double getDerivedVal() const {return m_derivedVal;}

        // Setters  
        void setVal(double val); 

    private:
        double m_val;
        double m_activatedVal;
        double m_derivedVal;

        int m_activationType;
};


#endif