#ifndef MNISTDATASET_H
#define MNISTDATASET_H

#include <string>

#include "matrix.h"

typedef Perc::Matrix Mat;

namespace Perc
{

class MnistDataset
{
public:
    MnistDataset();

    /**
     * @brief load_datasets Laden aller Bilder aus MNIST Datensätze
     * @return true falls das geklappt hat, false falls es irgendwo scheiterte
     */
    auto load_datasets() -> bool;

    Mat mX_train, mX_test;
    Mat mY_train, mY_test;


private:
    /**
     * @brief load_images   Laden der Bilder aus MNIST Dateien
     * @param filename Dateiname
     * @param output Die Matrix wo die Daten der Bilder abgespeichert werden
     * @return true falls das geklappt hat, false falls es irgendwo scheiterte
     */
    auto load_images(const std::string &filename, Mat &output) -> bool;

    /**
     * @brief load_labels   Laden der dazugehörigen Labels
     * @param filename  Labeldatei
     * @param output    Eine Matrix mit den Zahlen zw. 0 und 9
     * @return true falls das geklappt hat, false falls es irgendwo scheiterte
     */
    auto load_labels(const std::string &filename, Mat &output) -> bool;

    /**
     * @brief prepend_bias Die erste Spalte wird der Bias
     * @param mat Matrix die durch den Bias erweitert wird
     */
    auto prepend_bias(Mat &mat) -> void;
};

}

#endif // MNISTDATASET_H
