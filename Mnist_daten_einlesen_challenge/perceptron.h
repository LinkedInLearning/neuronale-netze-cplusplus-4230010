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
     * @brief run
     * @param input
     * @return
     */
    real run(const Vector &input);



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
     * @brief gradient
     * @param X
     * @param Y
     * @param w
     */
    auto gradient(const Matrix &X, Matrix &Y, Matrix &w) -> auto;

    /**
     * @brief train
     * @param X
     * @param Y
     * @param iterations
     * @param lr
     */
    auto train(const Matrix &X,
               Matrix &Y,
               const uint iterations,
               const double lr) -> Matrix;

    /**
     * @brief classify
     * @param X
     * @param w
     */
    auto classify(const Matrix &X, const Matrix &w) const -> auto;

    /**
     * @brief loss
     * @param X
     * @param Y
     * @param w
     */
    real loss(const Matrix &X,
              const Matrix &Y,
              const Matrix &w);

    /**
     * @brief test
     * @param X
     * @param Y
     * @param w
     * @param digit
     */
    auto test(const Matrix &X,
              Matrix &Y,
              Matrix &w,
              const uint digit) -> void;


};

}

#endif // PERCEPTRON_H
