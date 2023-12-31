#pragma once
#include <utility>
#include <string>
using namespace std;

class CNumber {
private:
	int* pi_table;
	int i_length;
	bool sign_minus;

public:
	CNumber();
	CNumber(CNumber&& other); //Move construktor
	CNumber(const CNumber& other);
	CNumber operator+(int intValue) const;
	~CNumber();
	void vSet(int iNewVal);
	void vSet(CNumber &pcNewVal);
	int vGetValue();
	CNumber vDiv(CNumber& pcDivident, CNumber pcDivisor);
	int* vLessArray(int* bigArray, int old_length, int i_length);
	string sToStr();
	void operator=(const int iValue);
	void operator=(const CNumber &pcOther);
	CNumber& operator=(CNumber&& other);
	CNumber operator+(CNumber& pcOther);
	CNumber operator-(CNumber& pcOther);
	CNumber operator*(CNumber& pcOther);
	CNumber operator/(CNumber& pcOther);
	CNumber vAdd(const CNumber pcFirst, const CNumber pcSecond);
	CNumber vSub(const CNumber pcBigger, const CNumber pcLesser);
	CNumber vMultiply(const CNumber pcFirst, const CNumber pcSecond);
	CNumber& vBigger(CNumber& pcFirst, CNumber& pcSecond);

};


const int DEFAULT_ARRAY_LENGTH = 64;
const int NUMBER_SYSTEM = 10;
const string destr_text = "destruktor";
