/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int pasc(int n , int k);

int main() {
    cout<<pasc(2,1)<<endl;
    return 0;
}

int pasc(int n, int k){
	if(k==0 || n==k){
		return 1;
	}
	return pasc(n-1,k-1) + pasc(n-1,k);
}
