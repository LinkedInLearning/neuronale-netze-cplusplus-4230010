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

auto runOrGate(const bool a, const bool b) -> bool
{
    const float threshold = 0.95f;
    Perceptron orPerc(Vec{-5, 10, 10});

    Vec in{1.0, a ? 1.0 : 0.0, b ? 1.0 : 0.0};

    const auto y = orPerc.run(in);

    return (y>threshold);
}


auto runXorGate(const bool a, const bool b) -> bool
{
    const float threshold = 0.95f;
    Perceptron andPerc(Vec{-15, 10, 10});
    Perceptron negAndPerc(Vec{15, -10, -10});
    Perceptron orPerc(Vec{-5, 10, 10});

    Vec in{1.0, a ? 1.0 : 0.0, b ? 1.0 : 0.0};

    const auto y1 = negAndPerc.run(in);
    const auto y2 = orPerc.run(in);

    Vec res{1.0, y1, y2};

    const auto y_last = andPerc.run(res);

    return (y_last>threshold);
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


    // OR Fall
    {
        cout << endl;
        cout << "Wahrheitstabelle OR:";
        cout << endl;

        const auto test1 = runOrGate(false, false);
        const auto test2 = runOrGate(false, true);
        const auto test3 = runOrGate(true, false);
        const auto test4 = runOrGate(true, true);

        cout << bool2Str(test1) << endl;
        cout << bool2Str(test2) << endl;
        cout << bool2Str(test3) << endl;
        cout << bool2Str(test4) << endl;
    }

    // XOR Fall
    {
        cout << endl;
        cout << "Wahrheitstabelle XOR:";
        cout << endl;

        const auto test1 = runXorGate(false, false);
        const auto test2 = runXorGate(false, true);
        const auto test3 = runXorGate(true, false);
        const auto test4 = runXorGate(true, true);

        cout << bool2Str(test1) << endl;
        cout << bool2Str(test2) << endl;
        cout << bool2Str(test3) << endl;
        cout << bool2Str(test4) << endl;
    }


    return 0;
}
