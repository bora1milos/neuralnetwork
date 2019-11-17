#ifndef _LAYER_H
#define _LAYER_H

#include "Neuron.h"
#include "Matrix.h"
#include <iostream>
#include <vector>

typedef std::vector<Neuron* > NEURONS;

class Layer
{
    public:
        Layer();
        explicit Layer(size_t size);

        ~Layer();

        void setValue(int i, double v);

        Matrix *matrixifyVals();
        Matrix *matrixifyActivatedVals();
        Matrix *matrixifyDerivedVals();

        const NEURONS getNeurons() const {return m_neurons;}
        void setNeurons(NEURONS neurons) {m_neurons = neurons;}

    private:
        size_t m_size;
        NEURONS m_neurons;
};


#endif