
#include <iostream>
#include "CNumber.h"
using namespace std;

int main()
{

    CNumber *obj1 = new CNumber();
    obj1->vSet(642);

    cout << (obj1->sToStr()) << endl;

    delete obj1;

    CNumber c_num_0, c_num_1, c_num_2;
    c_num_1 = 123;
    cout << (c_num_1.sToStr()) << endl;
    c_num_2 = 45;

    //c_num_0 = c_num_1;
    //cout << (c_num_0.sToStr()) << endl;
    
    c_num_0 = c_num_1 + c_num_2;
    cout << (c_num_0.sToStr()) << endl;

    return 0;
}

