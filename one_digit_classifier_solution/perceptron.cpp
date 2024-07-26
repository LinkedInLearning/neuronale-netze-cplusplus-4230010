#include "perceptron.h"

#include <cmath>
#include <iostream>

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



auto Perceptron::train(const Matrix &X,
                       const Matrix &Y,
                       const uint iterations,
                       const double lr) -> Matrix
{
    Matrix w = Matrix::zeros(X.getDim(1), Y.getDim(1));

    for(unsigned i=0 ; i<iterations ; i++)
    {
        const auto lossVal = loss(X, Y, w);
        cout << "Iteration " << i << " => Loss: " << lossVal << endl;
        const auto grad = gradient(X, Y, w) * lr;
        w -= grad;
    }

    return w;
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

auto Perceptron::test(const Matrix &X, Matrix &Y, Matrix &w) -> void
{
    const auto total_examples = X.getDim(0);   
    const auto correct_results = Matrix::sum(classify(X, w) == Y);
    const auto success_percent = (correct_results*100) / total_examples;
    cout << "Correct classifications for all digits: "
         << correct_results << "/" << total_examples << " "
         << "(" << success_percent << "\%)" << endl;
}


}
