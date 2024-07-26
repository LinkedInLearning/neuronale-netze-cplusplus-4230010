#include "perceptron.h"

#include <cmath>
#include <iostream>
#include <iomanip>

// Hilfreich um Zahlenwerte zu debuggen
// Die Bennenung der Variable wird als Text ausgegeben zusammen mit dem aktuellen Wert
// Z.B. DBG(grad) -> grad : 30
#define xstr(a) str(a)
#define str(a) #a
#define DBG(x) std::cout << str(x) << ": " << x << std::endl

using namespace std;

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

    for(auto &val : z)
    {
        val = 1.0/(1.0+exp(-val));        
    }

    return z;
}

auto Perceptron::forward(const Matrix &X, const Matrix &w) const -> auto
{
    const Matrix weighted_sum = X.matmul(w);
    return sigmoid(weighted_sum);
}

auto Perceptron::gradient(const Matrix &X, const Matrix &Y, const Matrix &w) -> auto
{
    const auto xt = X.transposed();
    const auto m1 = xt.matmul(forward(X, w) - Y);
    const auto res = m1 / X.getDim(0);
    return res;
}


auto Perceptron::report(const uint iteration,
                        const Matrix &X_train, const Matrix &Y_train,
                        const Matrix &X_test, const Matrix &Y_test,
                        const Matrix &w)
{
    auto classifications = (classify(X_test, w) == Y_test);
    auto matches = classifications.sum();
    const auto n_test_examples = Y_test.getDim(0);
    matches = (matches*100.0) / n_test_examples;
    const auto training_loss = loss(X_train, Y_train, w);

    std::cout << iteration << " - "
              << "Loss: " << std::setprecision(8) << training_loss << ", "
              << matches << "\%" <<  std::endl;
}



auto Perceptron::train(const Matrix &X_train, const Matrix &Y_train,
                       const Matrix &X_test, const Matrix &Y_test,
                       const uint iterations,
                       const double lr) -> Matrix
{
    Matrix w = Matrix::zeros(X_train.getDim(1), Y_train.getDim(1));

    for(unsigned i=0 ; i<iterations ; i++)
    {
        report(i, X_train, Y_train, X_test, Y_test, w);
        const auto grad = gradient(X_train, Y_train, w) * lr;
        w -= grad;
    }

    return w;
}

auto Perceptron::classify(const Matrix &X, const Matrix &w) const -> Matrix
{
    auto y_hat = forward(X, w);

    // Indizes sind die zu erkennenden Zahlen pro Zeile
    //auto labels = Matrix::round(y_hat);
    auto labels = Matrix::argmax(y_hat);
    return labels;
}

real Perceptron::loss(const Matrix &X, const Matrix &Y, const Matrix &w)
{
    const Matrix y_hat = forward(X, w);
    Matrix first_term = Y * Matrix::log(y_hat);
    Matrix Ones = Y;
    Ones.assign(1.0);
    Matrix second_term = (Ones - Y) * Matrix::log(Ones - y_hat);
    return -Matrix::sum(first_term + second_term) / X.getDim(0);
}


}
