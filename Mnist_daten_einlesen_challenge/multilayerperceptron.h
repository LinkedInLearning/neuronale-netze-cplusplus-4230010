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
     * @brief addPerceptron
     * @param perc  Das Perceptron welches hinzugefügt werden soll
     * @param layer Schicht (von Input zu Output) wo das Perceptron hinzugefügt wird.
     *         0 -> Ist das erste Layer, welches direkt das am Input hängt.
     * @return true, wenn das hinzufügen geklappt hat, andernfalls false
     */
    bool addPerceptron(const Perceptron &perc, const unsigned int layer);

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
