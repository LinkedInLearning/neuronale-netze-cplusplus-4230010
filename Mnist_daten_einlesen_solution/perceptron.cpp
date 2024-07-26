#include "perceptron.h"

#include <cmath>
#include <iostream>

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

auto Perceptron::gradient(const Matrix &X, Matrix &Y, Matrix &w) -> auto
{
    const auto xt = X.transposed();
    const auto forw = forward(X, w);
    const auto m2 = forw - Y;
    const auto m1 = xt.matmul(m2);
    const auto res = m1 / X.getDim(0);
    return res;
}

auto Perceptron::train(const Matrix &X,
                       Matrix &Y,
                       const uint iterations,
                       const double lr) -> Matrix
{
    /*
     * TODO: Für spätere Challenge
     */
}

auto Perceptron::classify(const Matrix &X, const Matrix &w) const -> auto
{
    Matrix res = forward(X, w);
    res = Matrix::round(res);
    return res;
}

real Perceptron::loss(const Matrix &X, const Matrix &Y, const Matrix &w)
{
    const Matrix y_hatmat = forward(X, w);
    const Matrix y_hatlog = Matrix::log(y_hatmat);
    Matrix first_term = Y * y_hatlog;
    Matrix Ones = Y;
    Ones.assign(1.0);
    Matrix second_term = (Ones - Y) * Matrix::log(Ones - y_hatmat);
    return -Matrix::average(first_term + second_term);
}


auto Perceptron::test(const Matrix &X, Matrix &Y, Matrix &w, const uint digit) -> void
{
    const auto total_examples = X.getDim(0);
    const auto correct_results = Matrix::sum(classify(X, w) == Y);
    const auto success_percent = correct_results * 100 / total_examples;

    cout << "Correct classifications for digit " << digit << ": "
         << correct_results << "/" << total_examples << " "
         << "(" << success_percent << "\%)" << endl;
}




}
