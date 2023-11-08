#include <iostream>
#include "CNumber.h"
#include <utility>
using namespace std;

CNumber::CNumber()
{
    i_length = DEFAULT_ARRAY_LENGTH;
    sign_minus = false;
    pi_table = new int[DEFAULT_ARRAY_LENGTH];
}

CNumber::CNumber(CNumber&& other) noexcept 
{
    i_length = other.i_length;
    sign_minus = other.sign_minus;
    pi_table = other.pi_table;
    other.pi_table = nullptr; // Zabezpieczenie przed zwolnieniem pamięci przez inny obiekt
}

CNumber::~CNumber()
{
    //cout << pi_table << endl;
    //cout << *pi_table << endl;
    if (pi_table != nullptr) {
        delete[] pi_table;
        pi_table = nullptr; // Zabezpieczenie przed ponownym zwolnieniem
    }
    //cout << *pi_table << endl;
    //cout << destr_text << endl;
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
        pi_table[i_length - 1 - counter] = rest_part;
        total_part /= NUMBER_SYSTEM;
        counter++;
    }

    if (iNewVal == 0) {
        pi_table[0] = 0;
        counter = 1;
    }
    pi_table = vLessArray(pi_table, i_length, counter);
    i_length = counter;
}

void CNumber::vSet(CNumber& pcOther)
{
    if (pi_table != nullptr) {
        delete[] pi_table;
    }
    pi_table = new int[pcOther.i_length];
    i_length = pcOther.i_length;
    for (int i = 0; i < i_length; i++)
    {
        pi_table[i] = pcOther.pi_table[i];
    }
}

int* CNumber::vLessArray(int* bigArray, int old_length, const int new_length)
{
    int* resultArray = new int[new_length]; 
    for (int i = 0; i < new_length; i++)
    {
        resultArray[i] = bigArray[old_length - new_length + i];
    }
    delete[] bigArray;
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

CNumber& CNumber::operator=(CNumber&& other) noexcept {
    if (this != &other) {
        // Zwolnij zasoby w obecnym obiekcie
        if (pi_table != nullptr) {
            delete[] pi_table;
        }

        // Przeniesienie zasobów z innego obiektu
        i_length = other.i_length;
        sign_minus = other.sign_minus;
        pi_table = other.pi_table;

        // Zabezpieczenie przed zwolnieniem pamięci przez inny obiekt
        other.pi_table = nullptr;
    }
    return *this;
}

CNumber CNumber::operator+(CNumber& pcOther)
{
    CNumber result;
    
    if (sign_minus == pcOther.sign_minus) {
        //+A + +B = + (A+B)
        //-A + -B = - (A+B)
        result = vAdd(*this, pcOther);
        result.sign_minus = sign_minus;
    }
    else {
        //+A + -B = "sign of Bigger +/-" (Bigger - Lesser)
        //-A + +B = -//-
        //Find bigger and lesser
        CNumber bigger = vBigger(*this, pcOther);
        CNumber lesser;
        if (&bigger == this) {
            lesser = pcOther;
        }
        else {
            lesser = *this;
        }
        cout << "Bigger: " << bigger.sToStr();
        cout << "Lesser: " << lesser.sToStr();
        result = vSub(bigger, lesser);
        // "sign of Bigger +/-"
        result.sign_minus = bigger.sign_minus;
    }
    return result;
}

CNumber CNumber::operator-(CNumber& pcOther)
{
    CNumber result;

    if (sign_minus != pcOther.sign_minus) {
        //+A - -B =   (A+B)
        //-A - +B = - (A+B)
        result = vAdd(std::move(*this), std::move(pcOther));
        if (pcOther.sign_minus) {
            result.sign_minus = false;
        }
        else {
            result.sign_minus = true;
        }
    }
    else {
        //Find bigger and lesser
        //+A - +B = "sign of Bigger +/-" (Bigger - Lesser)
        //-A - -B = -//-
        CNumber bigger = vBigger(*this, pcOther);
        CNumber lesser;
        if (&bigger == this) {
            lesser = pcOther;
        }
        else {
            lesser = *this;
        }
        cout << "Bigger: " << bigger.sToStr();
        cout << "Lesser: " << lesser.sToStr();
        result = vSub(bigger, lesser);
        // "sign of Bigger +/-"
        result.sign_minus = bigger.sign_minus;

    }
    //cout << "this: " << this->sToStr() << endl;
    //cout << "pcOther" << pcOther.sToStr() << endl;

    return result;
}

CNumber CNumber::vAdd(const CNumber pcFirst, const CNumber pcSecond)
{
    CNumber resultAdd;
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
                resultAdd.pi_table[resultAdd.i_length - 1 - i] = sum % NUMBER_SYSTEM;
                rest = sum / NUMBER_SYSTEM;
            }
            else {
                resultAdd.pi_table[resultAdd.i_length - 1 - i] = sum; 
                rest = 0;
            }
        }
        else if (sum != 0) {
            counter++;
            resultAdd.pi_table[resultAdd.i_length - i - 1] = sum;
        }
    }
    resultAdd.pi_table = vLessArray(resultAdd.pi_table, resultAdd.i_length, counter);
    resultAdd.i_length = counter;
    return resultAdd;
}

CNumber CNumber::vSub(const CNumber pcBigger, const CNumber pcLesser)
{
    CNumber resultSub;
    int max_length = pcBigger.i_length;
    int counter = 0;
    int pcBigger_bit = 0;
    int pcLesser_bit;
    int pozyczka = 0;
    for (int i = 0; i < max_length; i++) {
        if (i < pcBigger.i_length) {
            pcBigger_bit = pcBigger.pi_table[pcBigger.i_length - 1 - i];
        }
        if (i < pcLesser.i_length) {
            pcLesser_bit = pcLesser.pi_table[pcLesser.i_length - 1 - i];
        }
        else {
            pcLesser_bit = 0;
        }
        int sub = 0;
        if (pcBigger_bit - pozyczka < pcLesser_bit) {
        sub = pcBigger_bit + NUMBER_SYSTEM - pozyczka - pcLesser_bit;
        pozyczka = 1;
        } else {
        sub = pcBigger_bit - pozyczka - pcLesser_bit;
        pozyczka = 0;
        }
        counter++;
        resultSub.pi_table[resultSub.i_length - 1 - i] = sub;
    }
    //delete first zeros
    for (int i = resultSub.i_length - pcBigger.i_length; i < resultSub.i_length - 1; i++) {
        if (resultSub.pi_table[i] == 0) {
        counter--;
        }
    }
    resultSub.pi_table = vLessArray(resultSub.pi_table, resultSub.i_length, counter);
    resultSub.i_length = counter;
    return resultSub;
}
//Find bigger CNumber
CNumber CNumber::vBigger(const CNumber pcFirst, const CNumber pcSecond)
{
    if (pcFirst.i_length > pcSecond.i_length) {
        return pcFirst;
    }
    else if (pcFirst.i_length < pcSecond.i_length) {
        return pcSecond;
    }
    else {
        for (int i = 0; i < pcFirst.i_length; i++) {
            int difference = pcFirst.pi_table[i] - pcSecond.pi_table[i];
            if (difference > 0) {
                return pcFirst;
            }
            else if (difference < 0) {
                return pcSecond;
            }
        }
    }
    return pcFirst; //in case of pcFirst==pcSecond return pcFirst
}

CNumber::CNumber(const CNumber& other) {
    // Skopiuj pola z obiektu other do bieżącego obiektu
    i_length = other.i_length;
    sign_minus = other.sign_minus;
    pi_table = new int[i_length];
    for (int i = 0; i < i_length; i++) {
        pi_table[i] = other.pi_table[i];
    }
}

