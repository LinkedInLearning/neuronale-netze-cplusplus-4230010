#ifndef CSVREADER_H
#define CSVREADER_H

#include <iostream>

#include <fstream>
#include <sstream>
#include <vector>

#include "matrix.h"

/**
 * @brief readMatrix    Lese Matrix aus einer CSV Datei ein
 * @param fname Dateiname
 * @return Matrix mit eingelesenen Daten
 */
Perc::Matrix readMatrix(const std::string &fname);

#endif // CSVREADER_H
