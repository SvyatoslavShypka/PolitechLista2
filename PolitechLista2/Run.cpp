
#include <iostream>
#include "CNumber.h"
#include <utility>
using namespace std;

int main()
{
    CNumber c_num_0, c_num_1, c_num_2;

    srand((unsigned)time(NULL));
    for (int i = 0; i < 20; i++) {
        c_num_1 = rand() % (10000) - 10000;
        //c_num_1 = 6;
        //c_num_2 = -3;
        c_num_2 = rand() % (10000) - 10000;

        // -
        c_num_0 = c_num_1 - c_num_2;
        cout << c_num_1.sToStr() << " - " << c_num_2.sToStr() << " = ";
        cout << (c_num_0.sToStr());
        if (c_num_0.vGetValue() == c_num_1.vGetValue() - c_num_2.vGetValue()) {
            cout << "  -Ok" << endl;
        }
        else {
            cout << "  *************INCORRECT" << endl;
        }

        // +
        c_num_0 = c_num_1 + c_num_2;
        cout << c_num_1.sToStr() << " + " << c_num_2.sToStr() << " = ";
        cout << (c_num_0.sToStr());
        if (c_num_0.vGetValue() == c_num_1.vGetValue() + c_num_2.vGetValue()) {
            cout << "  -Ok" << endl;
        }
        else {
            cout << "  *************INCORRECT" << endl;
        }

        // *
        c_num_0 = c_num_1 * c_num_2;
        cout << c_num_1.sToStr() << " * " << c_num_2.sToStr() << " = ";
        cout << (c_num_0.sToStr());
        if (c_num_0.vGetValue() == c_num_1.vGetValue() * c_num_2.vGetValue()) {
            cout << "  -Ok" << endl;
        }
        else {
            cout << "  *************INCORRECT" << endl;
        }

        // /
        c_num_0 = c_num_1 / c_num_2;
        cout << c_num_1.sToStr() << " / " << c_num_2.sToStr() << " = ";
        cout << (c_num_0.sToStr());
        if (c_num_0.vGetValue() == c_num_1.vGetValue() / c_num_2.vGetValue()) {
            cout << "  -Ok" << endl;
        }
        else {
            cout << "  *************INCORRECT" << endl;
        }
    }

    return 0;
}

