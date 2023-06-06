/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;


int main() {
	int result = 0;
	int counter = 3;

	while (true){
		result++;
		
		if(randomChance(.50)){	

			cout<<"Heads"<<endl;
			counter--;
			if(counter==0){
				break;
			}
			continue;
		}
		cout<<"Tails"<<endl;
		counter=3;
	}

	cout<<"It took "<<result<<" flips to get 3 consecutive heads."<<endl;
    return 0;
}
