#include "perceptron.h"

#include <cmath>

namespace Perc {

Perceptron::Perceptron(const Vector &weights) : mWeights(weights)
{}

real Perceptron::run(const Vector &input)
{
    // TODO: Hier Code eintragen, der das Perzeptron ausführt
    // "Summe der Multiplikation der Gewichtungen gegen Inputs"
}

real Perceptron::sigmoid(const double y)
{
    // TODO: Sigmoid Funktion implementieren
}

}
