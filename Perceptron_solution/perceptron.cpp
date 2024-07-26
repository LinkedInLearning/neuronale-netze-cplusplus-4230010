#include "perceptron.h"

#include <cmath>

namespace Perc {

Perceptron::Perceptron(const Vector &weights) : mWeights(weights)
{}

real Perceptron::run(const Vector &input)
{
    const auto y = input.dot(mWeights);
    const auto y_hat = sigmoid(y);
    return y_hat;
}

real Perceptron::sigmoid(const double y)
{
    return 1.0/(1.0 + exp(-y));
}

}
