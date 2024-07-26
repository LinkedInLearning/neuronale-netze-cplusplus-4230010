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

    // Wandle alle # (num->gewünschte Zahl) zu 1, ansonsten alle andere zu 0
    /*
    auto encode_number = [](Mat &m, const int num)
    {
        const auto rows = m.getDim(0);
        const auto cols = m.getDim(1);
        for(uint i = 0 ; i<cols ; i++)
        {
            for(uint j=0 ; j<rows ; j++)
            {
                auto val = m.get(j, i);
                val = (val == num) ? 1.0 : 0.0;
                m.set(j, i, val);
            }
        }
    };
*/

    // TODO: Implementiere ein Lambda,
    // welches die Zahlen im Y_Train so aufbereitet
    // die Spalte, die zur der passenden Zahl gehört
    // eine Eins wird und der Rest Null.
    // Referenz: encode_number()
    // -> Funktion aus der letzten Übung
    auto encode_all = [](Mat &m)
    {
        const auto rows = m.getDim(0);
        const auto cols = m.getDim(1);

        // ...
    };

    encode_all(Y_train);

    Perceptron p;

    Mat w = p.train(X_train, Y_train,
                    X_test, Y_test, 200, 1e-5);

    return 0;
}
