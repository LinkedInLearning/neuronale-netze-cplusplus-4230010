/*
 *  A binary classifier that recognizes the MNIST given digits
 *
 */
#include <iostream>

#include "mathvector.h"

#include "perceptron.h"
#include "multilayerperceptron.h"
#include "mnistdataset.h"


typedef Perc::Vector Vec;
typedef Perc::Matrix Mat;
typedef Perc::MnistDataset MnistDataset;
typedef Perc::MultilayerPerceptron MP;
typedef Perc::Perceptron Perceptron;

using namespace std;

int main()
{
    Mat::runTests();

    MnistDataset dataset;

    if(!dataset.load_datasets())
    {
        cerr << "Error loading datasets. Exiting." << endl;
        return 1;
    }

    Mat X_train = dataset.mX_train;
    Mat Y_train = dataset.mY_train;
    Mat X_test = dataset.mX_test;
    Mat Y_test = dataset.mY_test;

    // Nur für die Zahl 5 trainieren und testen
    const uint digit_to_test = 5;
    for(auto &val : Y_train)
    {
        val = (val == digit_to_test) ? 1.0 : 0.0;
    }
    for(auto &val : Y_test)
    {
        val = (val == digit_to_test) ? 1.0 : 0.0;
    }

    Perceptron p;

    Mat w = p.train(X_train, Y_train, 100, 1e-5);
    p.test(X_test, Y_test, w, digit_to_test);

    return 0;
}
