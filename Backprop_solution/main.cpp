/*
 *  A binary classifier that recognizes the MNIST given digits
 *
 */
#include <iostream>

#include "mathvector.h"

#include "perceptron.h"
#include "mnistdataset.h"


typedef Perc::Vector Vec;
typedef Perc::Matrix Mat;
typedef Perc::MnistDataset MnistDataset;
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
    Mat X_test = dataset.mX_test;

    Mat Y_base_train = dataset.mY_train;
    Mat Y_base_test = dataset.mY_test;

    auto Y_train = Y_base_train;
    auto Y_test = Y_base_test;

    // Matrix für Training-Labels und Test-Labels vorbereiten

    for(uint c=0 ; c<9 ; c++)
    {
        Y_train.appendRS(Y_base_train);
    }

/*    for(uint c=0 ; c<9 ; c++)
    {
        Y_test.appendRS(Y_base_test);
    }
*/

    // Und entsprechend normalisieren
    auto normalize_digit_matrix = [](Mat &m)
    {
        const auto rows = m.getDim(0);
        for(uint digit = 0 ; digit<m.getDim(1) ; digit++)
        {
            for(uint j=0 ; j<rows ; j++)
            {
                auto val = m.get(j, digit);
                val = (val == digit) ? 1.0 : 0.0;
                m.set(j, digit, val);
            }
        }
    };

    normalize_digit_matrix(Y_train);
    //normalize_digit_matrix(Y_test);

    Perceptron p;

    auto [w1, w2] = p.train(X_train, Y_train,
                            X_test, Y_test,
                            200, 10000, 0.01);

    return 0;
}
