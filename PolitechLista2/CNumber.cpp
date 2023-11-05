#include <iostream>
#include "CNumber.h"
using namespace std;


CNumber::CNumber(int number) {
    if (number < 0) {
        sign_minus = true;
        number = -number;
    }
    int counter = 0;
    int total_part = number;
    int* tmp_tablica = new int[DEFAULT_ARRAY_LENGTH];

    while (total_part != 0)
    {
        int rest_part = total_part % NUMBER_SYSTEM;
        tmp_tablica[DEFAULT_ARRAY_LENGTH - counter - 1] = rest_part;
        total_part /= NUMBER_SYSTEM;
        counter++;
    }

    i_length = counter;
    pi_table = new int[i_length];

    for (int i = 0; i < counter; i++)
    {
        pi_table[i] = tmp_tablica[DEFAULT_ARRAY_LENGTH - counter + i];
    }
}



CNumber::CNumber()
{
    //CNumber(3);
}



CNumber::~CNumber()
{
    //cout << destr_text << endl;
    //cout << *pi_table << endl;
    //delete[] pi_table;
    //cout << *pi_table << endl;
    //cout << pi_table << endl;
    //cout << "object deleted" << endl;

    if (*pi_table > 0)
    {
        cout << *pi_table << endl;
        delete[] pi_table;
        cout << *pi_table << endl;
        cout << pi_table << endl;
        cout << "deleted" << endl;
    }

}

CNumber::CNumber(const CNumber& pcOther)
{
    //sign_minus = pcOther.sign_minus;
    //i_length = pcOther.i_length;
    //pi_table = new int[pcOther.i_length];

    //for (int index = 0; index < pcOther.i_length; index++)
    //{
    //    pi_table[index] = pcOther.pi_table[index];
    //}
}


void CNumber::printTable() {

    for (int i = 0; i < i_length; i++) {
        cout << pi_table[i] << endl;
    }

}

string CNumber::sToStr()
{
    string result;
    if (sign_minus) {
        result = "true";
    }
    else {
        result = "false";
    }
    result = "{sign_minus = " + result + ", i_length = " + to_string(i_length) + ", pi_table = [";
    for (int i = 0; i < i_length; i++) {
        result += to_string(pi_table[i]);
        if (i < i_length - 1) {
            result += ", ";
        }
        else {
            result = result + "]}\n";
        }
    }
    return result;
}

void CNumber::operator=(const CNumber& pcOther) {
    //i_length = pcOther.i_length;
    //pi_table = pcOther.pi_table;

    //*this = CNumber(pcOther);
}

void CNumber::operator=(const int iValue) {
    //*this = *new CNumber(iValue);
}












