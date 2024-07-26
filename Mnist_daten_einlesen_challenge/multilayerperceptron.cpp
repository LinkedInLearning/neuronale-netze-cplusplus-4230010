#include "mathvector.h"
#include "multilayerperceptron.h"

namespace Perc {


MultilayerPerceptron::MultilayerPerceptron()
{

}

/**
     * @brief run   startet das Multilayer Perceptron
     * @param input Eingabevektor
     * @return  Ausgabewert
     */
real MultilayerPerceptron::run(const Vector &input) const
{

}

/**
     * @brief addPerceptron
     * @param perc  Das Perceptron welches hinzugefügt werden soll
     * @param layer Schicht (von Input zu Output) wo das Perceptron hinzugefügt wird.
     *         0 -> Ist das erste Layer, welches direkt das am Input hängt.
     * @return true, wenn das hinzufügen geklappt hat, andernfalls false
     */
bool MultilayerPerceptron::addPerceptron(const Perceptron &perc, const unsigned int layer)
{

}

/**
     * @brief numLayers Die Anzahl der Schichten, ergibt daraus wie die Perceptrons hinzugefügt werden.
     * @return Anzahl der Schichten
     */
unsigned int MultilayerPerceptron::numLayers()
{

}

}
