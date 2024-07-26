/*
 *  Ein kleines Testprogramm, welches überprüft ob die Matrizen-Operationen klappen
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
