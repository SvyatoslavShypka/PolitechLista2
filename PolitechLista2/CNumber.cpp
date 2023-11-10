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

CNumber::CNumber(CNumber&& other) 
{
    i_length = other.i_length;
    sign_minus = other.sign_minus;
    pi_table = other.pi_table;
    other.pi_table = NULL; // Zabezpieczenie przed ponownym zwolnieniem
}

CNumber::~CNumber()
{
    if (pi_table != NULL) {
        delete[] pi_table;
        pi_table = NULL; // Zabezpieczenie przed ponownym zwolnieniem
    }
    //cout << destr_text << endl;
}

void CNumber::vSet(int iNewVal)
{
    delete[] pi_table;
    pi_table = new int[DEFAULT_ARRAY_LENGTH];
    i_length = DEFAULT_ARRAY_LENGTH;
    if (iNewVal < 0) {
        sign_minus = true;
        iNewVal = - iNewVal;
    }
    int counter = 0;
    int total_part = iNewVal;

    if (iNewVal == 0) {
        pi_table[i_length - 1] = 0;
        counter = 1;
    } else {
        while (total_part != 0)
        {
            int rest_part = total_part % NUMBER_SYSTEM;
            pi_table[i_length - 1 - counter] = rest_part;
            total_part /= NUMBER_SYSTEM;
            counter++;
        }
    }
    
    pi_table = vLessArray(pi_table, i_length, counter);
    i_length = counter;
}

void CNumber::vSet(CNumber& pcOther)
{
    if (pi_table != NULL) {
        delete[] pi_table;
    }
    pi_table = new int[pcOther.i_length];
    i_length = pcOther.i_length;
    for (int i = 0; i < i_length; i++)
    {
        pi_table[i] = pcOther.pi_table[i];
    }
    pi_table = vLessArray(pi_table, i_length, pcOther.i_length);
}

int CNumber::vGetValue()
{
    int result = 0;
    for (int i = 0; i < i_length; i++) {
        result += pi_table[i] * pow(10, i_length - 1 - i);
    }
    if (this->sign_minus) {
        result = - result;
    }
    return result;
}

int* CNumber::vLessArray(int* bigArray, int old_length, const int new_length)
{
    int* resultArray = new int[new_length];
    for (int i = 0; i < new_length; i++)
    {
        resultArray[i] = bigArray[old_length - new_length + i];
    }
    return resultArray;
}

string CNumber::sToStr()
{
    string result;
    if (sign_minus) {
        result = "-";
    }
    else {
        result = "";
    }
    for (int i = 0; i < i_length; i++) {
        result += to_string(pi_table[i]);
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

CNumber& CNumber::operator=(CNumber&& other) {
    if (this != &other) {
        // Zwolnij zasoby w obecnym obiekcie
        if (pi_table != NULL) {
            delete[] pi_table;
        }

        // Przeniesienie zasobów z innego obiektu
        i_length = other.i_length;
        sign_minus = other.sign_minus;
        pi_table = other.pi_table;

        // Zabezpieczenie przed zwolnieniem pamięci przez inny obiekt
        other.pi_table = NULL;
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
        CNumber& bigger = vBigger(*this, pcOther);
        CNumber lesser;
        if (&bigger == this) {
            lesser = pcOther;
        }
        else {
            lesser = *this;
        }
        //cout << "Bigger: " << bigger.sToStr();
        //cout << "Lesser: " << lesser.sToStr();
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
        //TODO changes!?
        result = vAdd(*this, pcOther);
        if (pcOther.sign_minus) {
            result.sign_minus = false;
        }
        else {
            result.sign_minus = true;
        }
    }
    else {
        //Find bigger and lesser
        //+A - +B = (A - B); change sign for B; "sign of Bigger +/-" (Bigger - Lesser)
        //-A - -B = (-A + B); -//-
        pcOther.sign_minus = !pcOther.sign_minus;
        CNumber& bigger = vBigger(*this, pcOther);
        CNumber lesser;

        if (&bigger == this) {
            lesser = pcOther;
        }
        else {
            lesser = *this;
        }
        result = vSub(bigger, lesser);
        // "sign of Bigger +/-"
        result.sign_minus = bigger.sign_minus;
        // put back sign for B
        pcOther.sign_minus = !pcOther.sign_minus;
    }
    return result;
}

CNumber CNumber::operator*(CNumber& pcOther)
{
    CNumber resultMulti;
    resultMulti = vMultiply(*this, pcOther);
    if (sign_minus == pcOther.sign_minus) {
        //+A * +B = + (A*B)
        //-A * -B = - (A*B)
        resultMulti.sign_minus = false;
    }
    else {
        resultMulti.sign_minus = true;
    }

    return resultMulti;
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
    bool skip = false;
    int size = counter;
    for (int i = resultSub.i_length - size; i < resultSub.i_length - 1; i++) {
        if (resultSub.pi_table[i] != 0) {
            skip = true;
        }
        else if (!skip) {
            counter--;
        }
    }
    resultSub.pi_table = vLessArray(resultSub.pi_table, resultSub.i_length, counter);
    resultSub.i_length = counter;
    return resultSub;
}


CNumber CNumber::vMultiply(const CNumber pcFirst, const CNumber pcSecond)
{
    CNumber resultSum;
    resultSum.vSet(0);
    int max_length = pcFirst.i_length > pcSecond.i_length ? pcFirst.i_length : pcSecond.i_length;
    int counter = 0;
    int pcFirst_bit;
    int pcSecond_bit;
    int rest;
    for (int i = 0; i < pcFirst.i_length; i++) {
        CNumber resultMultiply;
        rest = 0;
        pcFirst_bit = pcFirst.pi_table[pcFirst.i_length - 1 - i];
        int k = 0;
        for (int j = 0; j < pcSecond.i_length; j++) {
            //int k = i * pcSecond.i_length + j;
            if (i > 0 && j == 0) {
                //zsuwanie wlewo ze wstawieniem zer
                for (int zsuw = 0; zsuw < i; zsuw++) {
                    resultMultiply.pi_table[resultMultiply.i_length - 1 - zsuw] = 0;
                    counter++;
                }
                k = counter;
            }
            pcSecond_bit = pcSecond.pi_table[pcSecond.i_length - 1 - j];
            int multi = pcFirst_bit * pcSecond_bit + rest;
            counter++;
            if (multi >= NUMBER_SYSTEM) {
                resultMultiply.pi_table[resultMultiply.i_length - 1 - j - k] = multi % NUMBER_SYSTEM;
                rest = multi / NUMBER_SYSTEM;
            }
            else {
                resultMultiply.pi_table[resultMultiply.i_length - 1 - j - k] = multi;
                rest = 0;
            }
            if (j == pcSecond.i_length - 1 && rest != 0) {
                counter++;
                resultMultiply.pi_table[resultMultiply.i_length - 1 - j - k - 1] = rest;
            }
        }
        //delete first zeros
        bool skip = false;
        int size = counter;
        for (int i = resultMultiply.i_length - size; i < resultMultiply.i_length - 1; i++) {
            if (resultMultiply.pi_table[i] != 0) {
                skip = true;
            }
            else if (!skip) {
                counter--;
            }
        }
        resultMultiply.pi_table = vLessArray(resultMultiply.pi_table, resultMultiply.i_length, counter);
        resultMultiply.i_length = counter;
        counter = 0;
        resultSum = resultSum + resultMultiply;

    }
    return resultSum;
}

//Find bigger CNumber
CNumber& CNumber::vBigger(CNumber& pcFirst, CNumber& pcSecond)
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
        return pcFirst; // Jeśli oba obiekty są takie same, zwracamy jeden z nich (dowolny)
    }
}

CNumber::CNumber(const CNumber& other) {
    // Kopiujemy pola z obiektu other do bieżącego obiektu
    i_length = other.i_length;
    sign_minus = other.sign_minus;
    pi_table = new int[i_length];
    for (int i = 0; i < i_length; i++) {
        pi_table[i] = other.pi_table[i];
    }
}

CNumber CNumber::operator+(int intValue) const
{
    CNumber result = *this;
    CNumber second;
    second.vSet(intValue);
    result.vSet(result);
    result = result + second;
    return result;
}

CNumber CNumber::operator/(CNumber& pcOther)
{
    CNumber result;
    result = vDiv(*this, pcOther);
    if (sign_minus == pcOther.sign_minus) {
        //+A / +B = + (A/B)
        //-A / -B = + (A/B)
        result.sign_minus = false;
    }
    else {
        result.sign_minus = true;
    }
    return result;
}

CNumber CNumber::vDiv(CNumber& pcDivident, CNumber pcDivisor)
{
    CNumber result;

    int divisor = abs(pcDivisor.vGetValue());
    // Result = zero
    if (pcDivident.i_length == 1 && pcDivident.pi_table[pcDivident.i_length - 1] == 0) {
        result.vSet(0);
        return result;
    }

    // Check for division by zero
    if (pcDivisor.i_length == 1 && pcDivisor.pi_table[pcDivisor.i_length - 1] == 0) {
        cout << "Error: Division by zero!" << endl;
        return result;
    }

    int rest = 0;
    int pcFirstDivident = 0;
    int counter = 0;
    bool first = true;
    for (int i = 0; i < pcDivident.i_length; i++) {
        pcFirstDivident += pcDivident.pi_table[i];
        if (pcFirstDivident / divisor > 0) {
            counter++;
            result.pi_table[counter - 1] = pcFirstDivident / divisor;
            rest = pcFirstDivident % divisor;
            pcFirstDivident = rest * 10;
            first = false;
        } else if (first) {
            pcFirstDivident *= 10;
        }
        else {
            counter++;
            result.pi_table[counter - 1] = pcFirstDivident / divisor;
            pcFirstDivident *= 10;
        }
    }
    if (counter == 0) {
        counter = 1;
        result.pi_table[0] = 0;
    }
    //result.pi_table is cut after counter-1
    int* correctedArray = new int[counter];
    for (int i = 0; i < counter; i++) {
        correctedArray[i] = result.pi_table[i];
    }
    delete[] result.pi_table;
    result.pi_table = correctedArray;
    result.i_length = counter;
    return result;
}

