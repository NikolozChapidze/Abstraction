/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "tokenscanner.h"
using namespace std;

double  grade_Calculate(int sentence,int word,int syllable);
void calculate(int& sentence,int& word,int& syllable);

int main() {
	int sentence = 0;
	int word     = 0;
	int syllable = 0;

	calculate(sentence, word, syllable);

	cout<<"Syllable: "<<syllable<<endl;
	cout<<"Words: "<<word<<endl;
	cout<<"Sentences: "<<sentence<<endl;
	cout<<endl;
	cout<<"Grade: "<< grade_Calculate(sentence, word, syllable )<<endl;

    return 0;
}
double  grade_Calculate(int sentence,int word,int syllable){
	double c0 = -15.59;
	double c1 = 0.39;
	double c2 = 11.8;
	double result = c0+c1*((double)word/sentence)+c2*((double)syllable/word);
	return result;
}
void count_Sentence(string line, int& sentence){

	string end_OfS=".?!";
	for(int i=0; i < line.length(); i++){
		for(int j=0; j < end_OfS.length(); j++){
			if(line[i] == end_OfS[j]){
				sentence++;
			}
		}
	}

}
void count_Word(string line, int& word){
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	scanner.ignoreComments();
	scanner.addWordCharacters("'");

	while (scanner.hasMoreTokens()) {
		string token = scanner.nextToken();
		if((token[0]>='a' && token[0]<='z') || (token[0]>='A' && token[0]<='Z')){
			word++;
		}
	}
}


//determining if the character is vowel
bool aris_Xmovani(char c){
	string xmov="aeiouy";
	c=tolower(c);
	for(int j=0; j < xmov.length(); j++){
		if(c == xmov[j]){
			return true;
		}
	}
	return false;
}

void count_syllable(string line, int& syllable){
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	scanner.ignoreComments();
	
	while (scanner.hasMoreTokens()) {
		bool already_has_xmovani_garda_E=false;
		string token = scanner.nextToken();
//counting syllable in each word
		for(int i=0;i<token.length();i++){
			if(aris_Xmovani(token[i])){
				syllable++;
				if(i!=token.length()-1){
					already_has_xmovani_garda_E=true;
				}
				while(aris_Xmovani(token[i]) && i < token.length()){
					i++;
				}
			}
		}
//substracting the syllables where e is last character of the word
		if( tolower(token[token.length()-1])=='e' && token.length()>1 && !aris_Xmovani(token[token.length()-2]) && already_has_xmovani_garda_E){
			syllable--;
		}	
	}
}

void calculate(int & sentence, int & word, int & syllable){
	
	string line;

	cout<<"please input file location: ";               
	
	string file(getLine(""));
	ifstream myfile (file.c_str());
//if file input is incorect we request the new file path
	while (myfile.fail()){
	cout<<"please input file location, previous attampt failed: "; 
	file=getLine("");
	myfile.clear();
	myfile.open(file.c_str());
	}
    while (getline(myfile,line) ){

     count_Sentence(line, sentence);
	 count_Word(line, word);
	 count_syllable(line, syllable);
   }
	myfile.close();
}
