/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
	cout<<"Input text: ";
	string text = getLine("");
	cout<<"Input subtext: ";
	string subt = getLine("");

	if(isSubsequence(text,subt)){
		cout<<"Aris"<<endl;
	}else{
		cout<<"Ar aris"<<endl;
	}
    return 0;
}

bool isSubsequence(string text, string subsequence){
	if(text.size() * subsequence.size() == 0){
		return text.size()>=0 && subsequence.size()==0; 
	}
	if(text[0]==subsequence[0]){
		return isSubsequence(text.substr(1),subsequence.substr(1));
	}else{
		return isSubsequence(text.substr(1),subsequence);	
	}
	return false;
}
