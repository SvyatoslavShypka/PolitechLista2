#pragma once

#include <string>
using namespace std;

class CNumber {
private:
	int* pi_table;
	int i_length;
	bool sign_minus;


public:
	CNumber();
	~CNumber();
	void vSet(int iNewVal);
	void vSet(CNumber &pcNewVal);
	string sToStr();
	void operator=(const int iValue);
	void operator=(const CNumber &pcOther);
	CNumber operator+(const CNumber pcOther);
	CNumber vAdd(const CNumber pcFirst, const CNumber pcSecond);

};


const int DEFAULT_ARRAY_LENGTH = 10;
const int NUMBER_SYSTEM = 10;
const int TEMPORARY_ARRAY_LENGTH_MULTIPLY = 64;
const string destr_text = "destruktor";
