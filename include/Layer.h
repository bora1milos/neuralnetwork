#ifndef _LAYER_H
#define _LAYER_H

#include "Neuron.h"
#include <iostream>
#include <vector>

typedef std::vector<Neuron* > NEURONS;

class Layer
{
    public:
        Layer();
        explicit Layer(size_t size);

        ~Layer();

    private:
        size_t m_size;
        NEURONS m_neurons;
};


#endif