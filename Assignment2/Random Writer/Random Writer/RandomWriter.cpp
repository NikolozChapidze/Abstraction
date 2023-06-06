/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "map.h"
#include "simpio.h"
#include "vector.h"
#include "random.h"
#include <string>
#include <fstream>

using namespace std;

//generating final random text
void random_Writer(string & result, int k, Map<string, Vector<char>> map){
	while(result.length()!=2000){
		string key = result.substr(result.length()-k,result.length());
		if(map[key].size()==0){
			break;
		}
		int index_of_nextChar = randomInteger(0,map[key].size()-1);
		
		char nextChar = map[key].get(index_of_nextChar);
		result = string(result) + nextChar;
	}
}

//reading file and filling the map, which will be used for generating random text
void readfileAndFillMap(string & startingstring, int & k, Map<string, Vector<char>> & map){

	cout<<"Enter the source text: ";               
	string file(getLine(""));
	ifstream myfile;
//if file input is incorect we request the new file path
	myfile.open(file.c_str());
	while (myfile.fail()){
	cout<<"Unable to open file.   Try again."<<endl; 
	cout<<"Enter the source text: ";
	file=getLine("");
	myfile.clear();
	myfile.open(file.c_str());
	}
////////////////////////

	cout<<"Enter the Markov order [1-10] ";
	k = getInteger();

	while(!(k>=1 && k<=10)){
		cout<<"That value is out of range."<<endl;
		cout<<"Enter the Markov order [1-10] ";
		k = getInteger();
	}

	cout<<"Processing file..."<<endl;
	char c;
	string keys="";
	int occuarance=0;

	//filling map
	while(myfile.get(c)){
		if(keys.length() == k){
			map[keys].add(c);
			if(map[keys].size() > occuarance){
				occuarance = map[keys].size();
				startingstring = keys;
			}
			keys = keys.substr(1,keys.length()) + c;
		}else{
			keys = string(keys) + c;
		}
	}
	myfile.close();
}

int main() {

	Map<string, Vector<char>>   map;
	int							k;
	string                      result;
	string						startingstring;

	readfileAndFillMap(startingstring, k, map);
	result = startingstring;
	random_Writer(result, k , map);

	cout<<result<<endl;
    return 0;
}
