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
     * @brief gradient dL/dw. Durch Substraktion des Gradienten wird
     *        der Fehler in der nächsten Iteration reduziert.
     * @param X Eingabe
     * @param Y Soll-Ausgabe
     * @param w Aktuelle Gewichtung
     */
    auto gradient(const Matrix &X, const Matrix &Y, const Matrix &w) -> auto;

    /**
     * @brief report Berichterstattung der Genauigkeit
     * @param iteration
     * @param X_train
     * @param Y_train
     * @param X_test
     * @param Y_test
     * @param w
     */
    auto report(const uint iteration,
                const Matrix &X_train, const Matrix &Y_train,
                const Matrix &X_test, const Matrix &Y_test,
                const Matrix &w);

    /**
     * @brief train     Training methode, obwohl auch hier mitgetestet
     *                  wird um die Fehlerentwicklung zu beobachten
     * @param X_train
     * @param Y_train
     * @param X_test
     * @param Y_test
     * @param iterations
     * @param lr
     * @return
     */
    auto train(const Matrix &X_train,
               const Matrix &Y_train,
               const Matrix &X_test,
               const Matrix &Y_test,
               const uint iterations,
               const double lr) -> Matrix;

    /**
     * @brief classify
     * @param X
     * @param w
     */
    auto classify(const Matrix &X, const Matrix &w) const -> Matrix;

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
     * @brief report
     * @param iteration
     * @param X_train
     * @param Y_train
     * @param X_test
     * @param Y_test
     * @param w1
     * @param w2
     */
    auto report(const uint iteration,
                const Matrix &X_train, const Matrix &Y_train,
                const Matrix &X_test, const Matrix &Y_test,
                const Matrix &w1, const Matrix &w2);


};

}

#endif // PERCEPTRON_H
