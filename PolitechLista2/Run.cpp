
#include <iostream>
#include "CNumber.h"
#include <utility>
using namespace std;

int main()
{
    CNumber c_num_0, c_num_1, c_num_2;
    c_num_1 = 5;
    //cout << (c_num_1.sToStr()) << endl;
    c_num_2 = 2;
    //cout << (c_num_2.sToStr()) << endl;

    // -
    c_num_0 = c_num_1 - c_num_2;
    cout << c_num_1.sToStr() << " - " << c_num_2.sToStr() << " = ";
    cout << (c_num_0.sToStr()) << endl;

    // +
    c_num_0 = c_num_1 + c_num_2;
    cout << c_num_1.sToStr() << " + " << c_num_2.sToStr() << " = ";
    cout << (c_num_0.sToStr()) << endl;

    // *
    c_num_0 = c_num_1 * c_num_2;
    cout << c_num_1.sToStr() << " * " << c_num_2.sToStr() << " = ";
    cout << (c_num_0.sToStr()) << endl;

    // /
    c_num_0 = c_num_1 / c_num_2;
    cout << c_num_1.sToStr() << " / " << c_num_2.sToStr() << " = ";
    cout << (c_num_0.sToStr()) << endl;

    return 0;
}

