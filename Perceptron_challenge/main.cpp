#include <iostream>

#include "mathvector.h"
#include "perceptron.h"


typedef Perc::Vector Vec;
typedef Perc::Perceptron Perceptron;

using namespace std;

std::string bool2Str(const bool val)
{
    return (val ? "true" : "false");
}

auto runAndGate(const bool a, const bool b) -> bool
{
    const float threshold = 0.95f;
    Perceptron andPerc(Vec{-15, 10, 10});

    Vec in{1.0, a ? 1.0 : 0.0, b ? 1.0 : 0.0};

    const auto y = andPerc.run(in);

    return (y>threshold);
}

int main()
{
    Vec x{1.0, 2.0, 5.0};
    Vec w{1.0, 3.0, 2.0};

    for(auto &val : x)
    {
        cout << val << ",";
    }

    cout << endl;
    cout << "Skalarprodukt: " << x.dot(w);
    cout << endl;

    cout << std::endl;

    // AND Fall
    {
        cout << endl;
        cout << "Wahrheitstabelle AND:";
        cout << endl;

        const auto test1 = runAndGate(false, false);
        const auto test2 = runAndGate(false, true);
        const auto test3 = runAndGate(true, false);
        const auto test4 = runAndGate(true, true);

        cout << bool2Str(test1) << endl;
        cout << bool2Str(test2) << endl;
        cout << bool2Str(test3) << endl;
        cout << bool2Str(test4) << endl;
    }

    return 0;
}
