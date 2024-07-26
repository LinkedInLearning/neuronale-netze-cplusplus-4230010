#include "mnistdataset.h"

#include <fstream>
#include <iostream>
#include <array>

using namespace std;

namespace Perc
{

MnistDataset::MnistDataset()
{

}

auto MnistDataset::load_datasets() -> bool
{
    bool ok = true;

    // 60000 Bilder, jedes 784 Werte (28*28 Pixel) + Bias
    ok &= load_images("mnist/train-images-idx3-ubyte.bin", mX_train);
    prepend_bias(mX_train);


    // 10000 Bilder, jedes 784 Werte (28*28 Pixel) + Bias
    ok &= load_images("mnist/t10k-images-idx3-ubyte.bin", mX_test);
    prepend_bias(mX_test);

    // 60000 Labels laden
    ok &= load_labels("mnist/train-labels-idx1-ubyte.bin", mY_train);

    // 10000 Labels für die Tests
    ok &= load_labels("mnist/t10k-labels-idx1-ubyte.bin", mY_test);            

    return true;
}

static void swapBytes(void* data, size_t size)
{
    char* bytes = (char*)data;
    for (int i = 0; i < size / 2; ++i)
    {
        std::swap(bytes[i], bytes[size - 1 - i]);
    }
}


auto MnistDataset::load_images(const std::string &filename,
                               Mat &output) -> bool
{
    std::ifstream file(filename);

    if(!file)
    {
        cerr << "Error opening " << filename << endl;
        return false;
    }

    array<uint, 4> header;

    // Zuerst lesen wir den Header ein
    file.read(reinterpret_cast<char*>(header.data()), 16);

    // Von Big Endian nach Little Endian umwandeln
    for(auto &val : header) swapBytes(&val, sizeof(val));

    // header[0] wird nicht benötigt.
    const uint n_images = header[1];
    const uint cols = header[2]*header[3];
    const uint rows = n_images;


    const uint raw_data_size = cols*rows;
    file.seekg (0, file.end);
    const uint file_size = file.tellg();
    file.seekg (16, file.beg);

    // Prüfung ob die Dateigröße mit dem Dateninhalt konsistent ist
    // Dafür prüfen die berechnete Größe aus dem Header
    if(raw_data_size+16 != file_size)
    {
        cerr << "Error reading " << filename << ".";
        cerr << "The header and file size do not match." << endl;
        return false;
    }

    // Einlesen der Bilder
    std::vector<unsigned char> pic_data(raw_data_size, 0);
    file.read(reinterpret_cast<char*>(pic_data.data()),
              raw_data_size);

    // TODO: Kopieren des Daten-Vektors in eine Matrix

    return true;
}

auto MnistDataset::load_labels(const std::string &filename,
                               Mat &output) -> bool
{
    std::ifstream file(filename);

    if(!file)
    {
        cerr << "Error opening " << filename << endl;
        return false;
    }

    // Übersrpinge die ersten 8 Bytes
    file.seekg (8, file.beg);

    // Label in eine Liste einlesen
    std::vector<uint> labelList;

    uint val;

    // Alle Labels in eine List einlesen
    unsigned char num = 0;
    while(file.read(reinterpret_cast<char*>(&num), sizeof(unsigned char)))
    {
        assert(num >= 0 && num <= 9);
        labelList.push_back(num);
    }

    // Matrix als Vektor formatieren
    output.setDim(labelList.size(),1);

    // TODO: Listenelemente in die Matrix übertragen

    return true;
}

auto MnistDataset::prepend_bias(Mat &mat) -> void
{
    // Spalte mit Einsen an den Anfang der Matrix hängen
    Mat res;

    const auto rows = mat.getDim(0);
    const auto cols = mat.getDim(1);
    res.setDim(rows, cols+1);

    const auto numBias = mat.getDim(0);
    for(uint c=0 ; c<numBias ; c++)
    {
        res.set(c, 0, 1.0);
    }

    // Werte aus der alten Matrix kopieren
    for(uint j=0 ; j<rows ; j++)
    {
        for(uint i=0 ; i<cols ; i++)
        {
            res.set(j, i+1, mat.get(j,i));
        }
    }
    mat = res;
}


}
