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
    /*
    for(uint c=0 ; c<9 ; c++)
    {
        Y_train.appendRS(Y_base_train);
    }

    for(uint c=0 ; c<9 ; c++)
    {
        Y_test.appendRS(Y_base_test);
    }*/

    // Wandle alle # (num->gewünschte Zahl) zu 1, ansonsten alle andere zu 0
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

    encode_number(Y_train, 5);
    encode_number(Y_test, 5);

    Perceptron p;

    Mat w = p.train(X_train, Y_train, 100, 1e-5);
    p.test(X_test, Y_test, w);

    // Achtung: Auch wenn der Test eine sehr hohe Erkennungsrate zeigt,
    // heißt das nicht dass es ein gutes Neuronetz ist. Es funktioniert ja nur so gut für
    // diese eine bestimmte Zahl. Nur 10% aller Zahlen werden betrachtet
    // und 90% liefern stets 0 ("Das ist nicht die gesuchte Zahl")
    // Sobald wir für alle 10 Zahlen trainieren sinkt die Prozentzahl, können
    // aber dafür mehrere Symbole erkennen.

    return 0;
}
