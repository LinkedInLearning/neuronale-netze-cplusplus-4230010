#include "perceptron.h"
#include "csvreader.h"

#include <cmath>
#include <iomanip>

#define xstr(a) str(a)
#define str(a) #a
#define DBG(x) std::cout << str(x) << ": " << x << std::endl

namespace Perc {

Perceptron::Perceptron()
{}

real Perceptron::run(const Vector &input)
{
    return 0.0;
}

auto Perceptron::sigmoid(const Matrix &y) const -> auto
{
    Matrix z(y);
    z.for_each([](const real val){ return 1.0/(1.0+exp(-val)); });
    return z;
}

auto Perceptron::sigmoid_gradient(const Matrix &y) const -> auto
{
    Matrix z(y);
    z.for_each([](const real &val){ return val*(1-val); });
    return z;
}

auto Perceptron::softmax(const Matrix &y) const -> auto
{
    Matrix exponentials(y);

    for(auto &val : exponentials)
    {
        val = exp(val);
    }

    const auto numRows = exponentials.getDim(0);
    const auto numCols = exponentials.getDim(1);

    for(uint r=0 ; r<numRows ; r++)
    {
        real sum = 0.0;
        for(uint c=0 ; c<numCols ; c++)
        {
            sum += exponentials.get(r,c);
        }

        for(uint c=0 ; c<numCols ; c++)
        {
            const auto val = exponentials.get(r,c);
            exponentials.set(r,c,val/sum);
        }
    }
    return exponentials;
}



real Perceptron::loss(const Matrix &Y, const Matrix &y_hat)
{
    return -Matrix::sum(Y*(Matrix::log(y_hat))) / Y.getDim(0);
}


auto Perceptron::forward(const Matrix &X,
                         const Matrix &w1,
                         const Matrix &w2) const -> auto
{
    // TODO:
    // 1. Hängen Sie dem X den Bias an
    // 2. Multiplizieren dieses X mit w1 und
    // 3. Schieben Sie das Ergebnis durch die Sigmoid Funktion
    Matrix h;

    // -> Das Ergebnis ist der Input für die Hidden Nodes
    // 4. Hängen Sie dem Input für hidden Nodes ebenfalls den Bias Vektor an (h)
    // 5. Die übertragenen Daten (h) an den verstecken Lager mit w2 multiplizieren
    // 6. Ergebnis durch Softmax schieben.
    // 7. Ergebnis von softmax und versteckte Knoten zurückgeben
    Matrix y_hat;

    return std::pair{y_hat, h};
}

auto Perceptron::back(const Matrix &X, const Matrix &Y,
                      const Matrix &y_hat,
                      const Matrix &w2,
                      const Matrix &h) -> auto
{
    auto prep_h = h;
    prep_h.prepend_bias();
    auto w2_grad = prep_h.transposed();
    const auto y_sub = y_hat - Y;
    w2_grad = (w2_grad.matmul(y_sub)) / X.getDim(0);


    Matrix w2_slice = w2.slice_col(1);
    const auto a_gradient = ((y_hat - Y).matmul(w2_slice.transposed())) * sigmoid_gradient(h);

    auto prep_X = X;
    prep_X.prepend_bias();
    auto w1_grad = (prep_X.transposed()).matmul(a_gradient) / X.getDim(0);

    return std::pair{w1_grad, w2_grad};
}

auto Perceptron::classify(const Matrix &X, const Matrix &w1, const Matrix &w2) const -> auto
{
    auto [y_hat, _] = forward(X, w1, w2);

    // Indizes sind die zu erkennenden Zahlen pro Zeile
    //auto labels = Matrix::round(y_hat);
    auto labels = Matrix::argmax(y_hat);
    return labels;
}



auto Perceptron::initWeights(const uint nInputVariables,
                             const uint hiddenNodes,
                             const uint nClasses)
{
    auto w1_rows = nInputVariables + 1;
    //Matrix w1 = Matrix::zeros(w1_rows, hiddenNodes);
    Matrix w1 = readMatrix("mnist/w1_init.csv");
    assert(w1.getDim(0) == w1_rows);


    auto w2_rows = hiddenNodes + 1;
    //Matrix w2 = Matrix::zeros(w2_rows, nClasses);
    Matrix w2 = readMatrix("mnist/w2_init.csv");
    assert(w2.getDim(0) == w2_rows);

    return std::pair{w1, w2};
}


auto Perceptron::report(const uint iteration,
                        const Matrix &X_train, const Matrix &Y_train,
                        const Matrix &X_test, const Matrix &Y_test,
                        const Matrix &w1, const Matrix &w2)
{

    auto [y_hat, _] = forward(X_train, w1, w2);
    auto training_loss = loss(Y_train, y_hat);
    auto classifications = classify(X_test, w1, w2);

    auto accuracy = Matrix::average(classifications == Y_test) * 100.0;
    std::cout << "Iteration: " << iteration << ", "
              << "Loss: " << std::setprecision(8) << training_loss << ", "
              << "Accuracy: " << accuracy << "\%" <<  std::endl;
}



auto Perceptron::train(const Matrix &X_train,
                       const Matrix &Y_train,
                       const Matrix &X_test,
                       const Matrix &Y_test,
                       const uint hiddenNodes,
                       const uint iterations,
                       const double lr) -> std::pair<Matrix, Matrix>
{
    auto nInputVariables = X_train.getDim(1);
    auto nClasses = Y_train.getDim(1);

    auto [w1, w2] = initWeights(nInputVariables, hiddenNodes, nClasses);

    for(uint i=0 ; i<iterations ; i++)
    {
        auto [y_hat, h] = forward(X_train, w1, w2);
        auto [w1_grad, w2_grad] = back(X_train, Y_train, y_hat, w2, h);

        w1 = w1 - (w1_grad * lr);
        w2 = w2 - (w2_grad * lr);

        report(i, X_train, Y_train, X_test, Y_test, w1, w2);
    }

    return std::pair{w1, w2};
}


}
