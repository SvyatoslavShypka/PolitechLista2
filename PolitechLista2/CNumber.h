#pragma once

#include <string>
using namespace std;

class CNumber {
private:
	int* pi_table;
	int i_length;
	bool sign_minus;


public:
	CNumber(int number);
	CNumber();
	CNumber(const CNumber& pcOther);
	void printTable();
	string sToStr();
	~CNumber();
	//void operator=(const CNumber &pcOther);
	//void operator=(const int iValue);

};


const int DEFAULT_ARRAY_LENGTH = 10;
const int NUMBER_SYSTEM = 10;
const string destr_text = "destruktor";
