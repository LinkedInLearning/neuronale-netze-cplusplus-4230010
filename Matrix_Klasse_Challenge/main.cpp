/*
 *  Ein kleines Testprogramm welches überprüft, ob die Matrix-Operationen funktionieren
 */
#include <iostream>

#include "matrix.h"

typedef Perc::Matrix Mat;

using namespace std;

int main()
{
    Mat::runTests();

    return 0;
}
