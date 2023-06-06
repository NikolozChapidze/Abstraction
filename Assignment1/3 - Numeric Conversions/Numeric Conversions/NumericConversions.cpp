/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    // [TODO: fill in the code]

	//cout<<intToString(-10)<<endl;

	cout<< stringToInt("0")<<endl;

    return 0;
}

string intToString(int n){
	char last_Digit = char(n%10 + '0');

	if(n<0){
		return "-" + intToString(n*(-1));
	}

	if(n<10){
		return string() + last_Digit;
	}
	
	return intToString(n/10) + string() + last_Digit;
}

int stringToInt(string str){

	if(str[0] == '-'){
		return stringToInt(str.substr(1,str.length()-1))*(-1);
	}

	int last_digit=str[str.length()-1]-'0';

	if(str.length()==1){
		return last_digit;
	}

	return stringToInt(str.substr(0,str.length()-1))*10 +  last_digit;
}