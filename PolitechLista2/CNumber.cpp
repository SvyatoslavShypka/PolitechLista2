#include <iostream>
#include "CNumber.h"
using namespace std;

CNumber::CNumber()
{
    i_length = DEFAULT_ARRAY_LENGTH;
    sign_minus = false;
    pi_table = new int[DEFAULT_ARRAY_LENGTH];
}

CNumber::~CNumber()
{
    //cout << *pi_table << endl;
    delete[] pi_table;
    //cout << *pi_table << endl;
    //cout << pi_table << endl;
    cout << destr_text << endl;
}

void CNumber::vSet(int iNewVal)
{
    if (iNewVal < 0) {
        sign_minus = true;
        iNewVal = - iNewVal;
    }
    int counter = 0;
    int total_part = iNewVal;
    //int tmp_tablica[DEFAULT_ARRAY_LENGTH];

    while (total_part != 0)
    {
        int rest_part = total_part % NUMBER_SYSTEM;
        pi_table[i_length - counter - 1] = rest_part;
        total_part /= NUMBER_SYSTEM;
        counter++;
    }

    if (iNewVal == 0) {
        pi_table[0] == 0;
        counter = 1;
    }
    pi_table = vLessArray(pi_table, i_length, counter);
    i_length = counter;
}

void CNumber::vSet(CNumber& pcOther)
{
    pi_table = new int[pcOther.i_length];
    i_length = pcOther.i_length;
    for (int i = 0; i < i_length; i++)
    {
        pi_table[i] = pcOther.pi_table[i];
    }
}

int* CNumber::vLessArray(int* bigArray, int old_length, int new_length)
{
    int* resultArray = new int[new_length];

    for (int i = 0; i < new_length; i++)
    {
        resultArray[i] = bigArray[old_length - i_length + i];
    }
    return resultArray;
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

void CNumber::operator=(const int iValue) {
    this->vSet(iValue);
}

void CNumber::operator=(const CNumber& pcOther) {
    // It's just a shallow copy
    //i_length = pcOther.i_length;
    //pi_table = pcOther.pi_table;

    // But we need deep copy
    this->vSet((CNumber& )pcOther);
}

CNumber CNumber::operator+(const CNumber pcOther)
{
    CNumber result;
    
    if (sign_minus == pcOther.sign_minus) {
        result = vAdd(*this, pcOther);
        result.sign_minus = sign_minus;
    }
    else {
        //TODO (first-bigger, second-lesser)
        result = vSub(*this, pcOther);
        result.sign_minus = sign_minus;

    }

    return result;
}

CNumber CNumber::vAdd(const CNumber pcFirst, const CNumber pcSecond)
{
    CNumber result;
    int max_length = pcFirst.i_length > pcSecond.i_length ? pcFirst.i_length : pcSecond.i_length;
    int counter = 0;
    int pcFirst_bit;
    int pcSecond_bit;
    int rest = 0;
    for (int i = 0; i <= max_length; i++) {
        if (i < pcFirst.i_length) {
            pcFirst_bit = pcFirst.pi_table[pcFirst.i_length - 1 - i];
        }
        else {
            pcFirst_bit = 0;
        }
        if (i < pcSecond.i_length) {
            pcSecond_bit = pcSecond.pi_table[pcSecond.i_length - 1 - i];
        }
        else {
            pcSecond_bit = 0;
        }
        int sum = pcFirst_bit + pcSecond_bit + rest;
        if (i < max_length) {
            counter++;
            if (sum >= NUMBER_SYSTEM) {
                result.pi_table[result.i_length - i - 1] = sum - NUMBER_SYSTEM;
                rest = sum / NUMBER_SYSTEM;
            }
            else {
                result.pi_table[result.i_length - i - 1] = sum;
                rest = 0;
            }
        }
        else if (sum != 0) {
            counter++;
            result.pi_table[result.i_length - i - 1] = sum;
        }
    }
    result.pi_table = vLessArray(result.pi_table, result.i_length, counter);
    result.i_length = counter;
    return result;
}

CNumber CNumber::vSub(const CNumber pcFirst, const CNumber pcSecond)
{
    return CNumber();
}

