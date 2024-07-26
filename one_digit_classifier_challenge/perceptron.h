#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "mathvector.h"
#include "matrix.h"

namespace Perc
{

class Perceptron
{
public:

    Perceptron();

    /**
     * @brief sigmoid Kunktion
     * @param y Eingabematrix
     * @return Ausgabewert als Matrix
     */
    auto sigmoid(const Matrix &y) const -> auto;

    /**
     * @brief forward Daten Funktionen
     *        des Perzeptron anwenden
     * @param X  Input Matrix
     * @param w  Weights Matrix
     */
    auto forward(const Matrix &X, const Matrix &w) const -> auto;

    /**
     * @brief gradient dL/dw. Durch Substraktion des Gradienten wird
     *        der Fehler in der nächsten Iteration reduziert.
     * @param X Eingabe
     * @param Y Soll-Ausgabe
     * @param w Aktuelle Gewichtung
     */
    auto gradient(const Matrix &X, const Matrix &Y, const Matrix &w) -> auto;

    /**
     * @brief train Die Trainingsmethode
     * @param X Inputmatrix
     * @param Y Soll-Output-Matrix
     * @param iterations Iterationen, wie lange es rechnen darf 
     * @param lr Lernrate
     */
    auto train(const Matrix &X,
               Matrix &Y,
               const uint iterations,
               const double lr) -> Matrix;

    /**
     * @brief classify Der Klassifizierer
     * @param X Inputmatrix
     * @param w Gewichtungen
     */
    auto classify(const Matrix &X, const Matrix &w) const -> auto;

    /**
     * @brief loss Fasst rechnerisch in einem Wert zusammen, wie hoch die Abweichung 
     *             zwischen den Soll- und Ist-Werten (Trainingslabel zu X.matmul.w)
     * @param X Inputmatrix
     * @param Y Sollausgabenmatrix
     * @param w Gewichtungen
     */
    real loss(const Matrix &X,
              const Matrix &Y,
              const Matrix &w);
              
    /**
     * @brief test Funktion
     * @param X Inputmatrix der Test-Datensätze
     * @param Y Outputmatrix der Test-Datensätze
     * @param w Gewichtungen
     */
    auto test(const Matrix &X,
              Matrix &Y,
              Matrix &w) -> void;

};

}

#endif // PERCEPTRON_H
