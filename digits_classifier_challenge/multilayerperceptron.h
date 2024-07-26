#ifndef MULTILAYERPERCEPTRON_H
#define MULTILAYERPERCEPTRON_H

#include "perceptron.h"

namespace Perc
{

class MultilayerPerceptron
{
public:

    MultilayerPerceptron();

    /**
     * @brief run   startet das Multilayer Perceptron
     * @param input Eingabevektor
     * @return  Ausgabewert
     */
    real run(const Vector &input) const;

    /**
     * @brief numLayers Die Anzahl der Schichten, ergibt daraus wie die Perceptrons hinzugefügt werden.
     * @return Anzahl der Schichten
     */
    unsigned int numLayers();

private:

    std::vector< std::vector<Perceptron> > mPerceptrons;

};

}

#endif // MULTILAYERPERCEPTRON_H
