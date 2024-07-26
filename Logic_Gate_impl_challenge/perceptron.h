#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "mathvector.h"

namespace Perc
{

class Perceptron
{
public:

    Perceptron(const Vector &weights);

    real run(const Vector &input);

    real sigmoid(const double y);

private:
    Vector mWeights;

};

}

#endif // PERCEPTRON_H
