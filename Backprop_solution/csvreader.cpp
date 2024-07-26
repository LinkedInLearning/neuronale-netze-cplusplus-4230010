#include "csvreader.h"

using namespace std;

// Funktion zum Splitten von Kommata
std::vector<std::string> split(const std::string& line)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    // Check for trailing comma with no data after it
    if (!ss && token.empty()) {
        tokens.push_back("");
    }

    return tokens;
}

using namespace Perc;

Perc::Matrix readMatrix(const std::string &fname)
{
    Matrix mat;

    // Öffnen der CSV Datei
    std::ifstream file(fname);

    // Konnte Datei geöffnet werden?
    if (!file.is_open())
    {
        std::cerr << "Fehler: Konnte Datei " << fname << " nicht einlesen." << std::endl;
        return mat;
    }

    // Vector mit allen CSV Daten
    std::vector<std::vector<std::string>> data;

    // Lese Datei Zeile für Zeile ein
    std::string line;
    while (std::getline(file, line))
    {
        // Splitte jede Zeile
        std::vector<std::string> row = split(line);
        data.push_back(row);
    }

    // Close the file
    file.close();

    const uint rows = data.size();

    if(rows<1)
    {
        std::cerr << "Error: Datensätze scheinen leer zu sein. 0 Zeilen erkannt." << std::endl;
        return mat;
    }

    const uint cols = data[0].size();

    if(cols<1)
    {
        std::cerr << "Error: Datensätze scheinen leer zu sein. 0 Spalten erkannt." << std::endl;
        return mat;
    }

    mat.setDim(rows, cols);

    // Einsortieren in die Matrix
    for(uint i=0 ; i<rows ; i++)
    {
        const auto &theRow = data[i];

        for(uint j=0 ; j<cols ; j++)
        {
            const auto &theCol = theRow[j];
            const auto val = std::stod(theCol);
            mat.set(i,j, val);
        }
    }

    return mat;
}
