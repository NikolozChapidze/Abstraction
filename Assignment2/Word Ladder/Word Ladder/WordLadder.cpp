/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: Nikoloz Chapidze
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include "lexicon.h"
#include "queue.h"
#include "set.h"
using namespace std;

//checking potential word if it could be added to the test ladder 
void check_potentialword(Set<string> & used_words, Vector<string> & test,
						 string & potentialword, int & counter, Queue<Vector<string>> & ladder, 
						 Vector<string> & result, string second){
	
					for(int j=0; j < test.size(); j++){
						if(potentialword == test.get(j)){ 
							break; 
						}
						if(j == test.size()-1){
							test.add(potentialword);
							used_words.add(potentialword);
							//cout<<potentialword<<endl;
							if(potentialword == second){
								if(result.isEmpty() || counter > test.size()){
									result = test;
									counter = result.size();
								}
							}else{
								ladder.enqueue(test);
							}						
							test.remove(test.size()-1);
							
						}
					}

}

//search for the leader (reading EnglishWords.dat as the lexicon and finding the shortest ladder)
Vector<string> wordLadder(string first, string second){
	Queue<Vector<string>> ladder;
	Vector<string> result;
	Vector<string> test;
	Set<string> used_words;
	int counter;

	Lexicon lex("EnglishWords.dat");

	test.add(first);
	ladder.enqueue(test);
	used_words.add(first);

	while(!ladder.isEmpty()){
		test.clear();
		test = ladder.dequeue();

		string lastWord = test.get(test.size()-1);

		if(!result.isEmpty() && counter < test.size()){
			continue;
		}

		for(int i=0; i < lastWord.length(); i++){
			for(char c = 'a'; c<='z'; c++){

				string potentialword = lastWord;
				potentialword[i] = c;

				//if lexicon conatins the potential word and the qurrent vector dosn't contains it,
				//the word will be added to the vector
				if(lex.contains(potentialword) && !used_words.contains(potentialword)){
					check_potentialword(used_words, test, potentialword, counter, ladder, result , second);
				}
			}
		}
	}

	return result;
}

//result ladder to string 
string resultToString(Vector<string> result){
	string final = "";

	if(!result.isEmpty()){
	
	for(int i=0; i<result.size()-1; i++){
		final += result.get(i);
		final += " -> ";
	}
	final += result.get(result.size()-1);

	}

	return final;
}

int main() {
	while(true){
		
		cout<<"Enter the starting word (or nothing to quit): ";
		string first = getLine("");

		if(first.length()==0){
		break;
		}

		cout<<"Enter the ending word: ";
		string second = getLine("");


		cout<<"Searching ..."<<endl;
		Vector<string> result;
		result = wordLadder(first , second);


		string final_result = resultToString(result);

		if(final_result.size() == 0){
			cout<<"Result not found ! "<< endl;
		}else{
		cout<<"Ladder found: "<<final_result<<endl;
		}
	}
	cout<<"Goodbye!"<<endl;
    return 0;
}
