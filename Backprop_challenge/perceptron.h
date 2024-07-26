#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "mathvector.h"
#include "matrix.h"

#include <tuple>

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
     * @brief sigmoid Funktion
     * @param y Eingabematrix
     * @return Ausgabewert als Matrix
     */
    auto sigmoid(const Matrix &y) const -> auto;

    /**
     * @brief sigmoid_gradient
     * @param y
     */
    auto sigmoid_gradient(const Matrix &y) const -> auto;

    /**
     * @brief softmax   Softmax Funktion
     * @param y Eingabematrix
     * @return Ausgabewert als Matrix
     */
    auto softmax(const Matrix &y) const -> auto;


    /**
     * @brief loss
     * @param Y
     * @param y_hat
     * @return
     */
    real loss(const Matrix &Y, const Matrix &y_hat);

    /**
     * @brief forward Daten Funktionen
     *        des Perzeptron anwenden
     * @param X  Input Matrix
     * @param w1  Weights Matrix
     */
    auto forward(const Matrix &X,
                 const Matrix &w1,
                 const Matrix &w2) const -> auto;

    /**
     * @brief back Backpropagation eines Neuronetzes
     *             mit verstecktem Layer
     * @param X
     * @param Y
     * @param y_hat
     * @param w2
     * @param h
     */
    auto back(const Matrix &X, const Matrix &Y,
              const Matrix &y_hat,
              const Matrix &w2,
              const Matrix &h) -> auto;

    /**
     * @brief gradient
     * @param X
     * @param Y
     * @param w
     */
    //auto gradient(const Matrix &X, Matrix &Y, Matrix &w) -> auto;

    /**
     * @brief train
     * @param X
     * @param Y
     * @param epochs
     * @param lr
     */

    auto train(const Matrix &X_train,
               const Matrix &Y_train,
               const Matrix &X_test,
               const Matrix &Y_test,
               const uint hiddenNodes,
               const uint iterations,
               const double lr) -> std::pair<Matrix, Matrix>;


    /**
     * @brief initWeights   Gewichte in Abhängigkeit des Inputs und der
     *                      versteckten Layer initialisieren
     * @param nInputVariables
     * @param hiddenNodes
     * @param nClasses
     */
    auto initWeights(const uint nInputVariables,
                                 const uint hiddenNodes,
                                 const uint nClasses);

    /**
     * @brief report Berichterstattung der Genauigkeit
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


    /**
     * @brief classify
     * @param X
     * @param w1
     * @param w2
     */
    auto classify(const Matrix &X, const Matrix &w1, const Matrix &w2) const -> auto;

    /**
     * @brief loss
     * @param X
     * @param Y
     * @param w
     */
    /*
    real loss(const Matrix &X,
              const Matrix &Y,
              const Matrix &w);
*/


private:
    //Vector mWeights;

};

}

#endif // PERCEPTRON_H
