/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int pauseTime = 120;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

struct point {
	int x;
	int y;
	point(int xVal = 0, int yVal = 0) {
		x = xVal;
		y = yVal;
	}
};

/* Function prototypes */

void welcome();
void giveInstructions();
void fillBoard(Grid<char> &grid,int n);
void getWordsForBoard(Vector<string> &wordsForBoard, int n);
void shuffleVector(Vector<string> &wordForBoard);
void getPreferences(int &boardSize,bool &automaticFill);
void customFill(Grid<char> &grid,int boardSize);
void actualGame(Grid<char> grid);
bool checkInputedWord(Grid<char> &grid,Vector<point> &result,string userWord, Lexicon &lex);
bool existsOnBoard(Grid<char> grid, Vector<point> &result,string userWord);
bool checkIfPossible(Grid<char> grid, Vector<point> &result,string userWord, int row, int col);
void userTurn(Set<string> &userWordsSet,Grid<char> grid,  Lexicon &lex);
void compTurn(Set<string> userWordsSet, Grid<char> grid, Lexicon &lex);
void findCompWords(Set<string> &compWordSet,Grid<char> grid, Lexicon &lex);
void wrapper(Set<string> &compWordSet,Grid<char> grid, Lexicon &lex,int row,int col,string currentWord);
/* Main program */



int main() {
    int	 boardSize;
	bool automaticFill;
	Grid<char> grid;

	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();

	while(true){
	getPreferences(boardSize,automaticFill);
	drawBoard(boardSize,boardSize);
	grid.resize(boardSize,boardSize);

	if(automaticFill){
		fillBoard(grid,boardSize);
	}else{
		customFill(grid,boardSize);
	}
	actualGame(grid);

	cout<<endl;
	cout<<"would you like to play again? ";
	if(toLowerCase(getLine("")) == "no" ){
		break;
	}
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]

void fillBoard(Grid<char> &grid, int n){
	Vector<string> wordsForBoard;
	getWordsForBoard(wordsForBoard, n);
	shuffleVector(wordsForBoard);

	int index=0;
	for(int row=0; row<n; row++){
		for(int col=0; col<n; col++){
			char characterForBoard = wordsForBoard.get(index)[randomInteger(0,wordsForBoard.get(index).size()-1)];
			labelCube(row,col,characterForBoard);
			grid[row][col] = characterForBoard;
			index++;
		}
	}
}

void getWordsForBoard(Vector<string> &wordsForBoard, int n){
	if(n == 4){
		foreach(string letter in STANDARD_CUBES){
			wordsForBoard.add(letter);
		}
	}
	if(n == 5){
		foreach(string letter in BIG_BOGGLE_CUBES){
			wordsForBoard.add(letter);
		}
	}
}

void shuffleVector(Vector<string> &wordForBoard){
	for(int i=0; i < wordForBoard.size(); i++){
		int r = randomInteger(i, wordForBoard.size()-1);
		string temp = wordForBoard.get(i);
		wordForBoard.set(i,wordForBoard.get(r));
		wordForBoard.set(r,temp);
	}
}

void getPreferences(int &boardSize,bool &automaticFill){
	cout<<"do you want big(5x5) board or small(4x4) (input 4 or 5): ";
	boardSize = getInteger("");
	while(boardSize != 4 && boardSize != 5){
		cout<<"please input correct size: ";
		boardSize = getInteger("");
	}

	cout<<"Do you want custom fill of board (yes or no): ";
	string fillAnsw = getLine("");
	while(fillAnsw != "yes" && fillAnsw != "no"){
		cout<<"please input correct answer: ";
		fillAnsw = getLine("");
	}

	if(fillAnsw == "yes"){ 
		automaticFill = false;
	}else{
		automaticFill = true;
	}
}

void customFill(Grid<char> &grid,int boardSize){
	cout<<"input "<< boardSize*boardSize << " characters to fill board: ";
	string boardChars;
	boardChars = toUpperCase(getLine(""));
	while(boardChars.length() != boardSize*boardSize){
		cout<<"incorrect length of the characters!"<<endl;
		cout<<"input again: ";
		boardChars = toUpperCase(getLine(""));
	}
	int index = 0;
	for(int row=0; row<boardSize; row++){
		for(int col=0; col<boardSize; col++){
			labelCube(row,col,boardChars[index]);
			grid[row][col] = boardChars[index];
			index++;
		}
	}
}
void actualGame(Grid<char> grid){
	cout<<"input words you find (nothing if you finish):"<<endl;
	Lexicon lex("EnglishWords.dat");
	Set<string> userWordsSet;
	userTurn(userWordsSet, grid, lex);
	compTurn(userWordsSet,grid,lex);
}

bool checkInputedWord(Grid<char> &grid, Vector<point> &result,string userWord, Lexicon &lex, Set<string> userWordsSet){
	if(userWord.length() < 4){
		cout<<"insufficient length"<<endl;
		return false;
	}
	if(!lex.contains(userWord)){
		cout<<"this word doesn't exists"<<endl;
		return false;
	}
	if(userWordsSet.contains(userWord)){
		cout<<"you have already used this word"<<endl;
		return false;
	}
	if(!existsOnBoard(grid, result,userWord)){
		cout<<"this word isn't on board"<<endl;
		return false;
	}

	return true;
}

bool existsOnBoard(Grid<char> grid, Vector<point> &result,string userWord){
	for(int row=0; row < grid.numRows(); row++){
		for(int col=0; col < grid.numCols(); col++){
			if(grid[row][col] == userWord[0]){
				result.add(point(row,col));
				char temp = grid[row][col];
				grid[row][col]='0';
				if(checkIfPossible(grid, result,userWord.substr(1),row,col)){
					return true;
				}
				result.clear();
				grid[row][col]=temp;
			}
		}
	}
	return false;
}

bool checkIfPossible(Grid<char> grid, Vector<point> &result,string userWord, int row, int col){
	if(userWord.length()==0){
		return true;
	}

	int startRow = (row == 0) ? row : row-1;
	int startCol = (col == 0) ? col : col-1;
	int endRow   = (row == grid.numRows() - 1) ? row : row+1;
	int endCol   = (col == grid.numCols() - 1) ? col : col+1;

	for(int x = startRow; x<=endRow; x++){
		for(int y = startCol; y<=endCol; y++){
			if(userWord[0] == grid[x][y]){
				result.add(point(x,y));
				char temp = grid[x][y];
				grid[x][y]='0';
				if(checkIfPossible(grid, result,userWord.substr(1),x,y)){
					return true;
				}
				result.remove(result.size()-1);
				grid[x][y]=temp;
			}
		}
	}
	return false;
}

void userTurn(Set<string> &userWordsSet,Grid<char> grid, Lexicon &lex){
	string userWord = toUpperCase(getLine(""));
	while(userWord != ""){
		Vector<point> result;
//cheching if word is correct and if user already used this word
		while(!checkInputedWord(grid,result,userWord,lex,userWordsSet)){
			userWord = toUpperCase(getLine(""));
			if(userWord == ""){
			break;
			}
		}
/////////
		if(userWord != ""){

		recordWordForPlayer(userWord, HUMAN);
		userWordsSet.add(userWord);

		for(int i=0; i<result.size(); i++){
			highlightCube(result.get(i).x,result.get(i).y,true);
		}
		pause(pauseTime);
		for(int i=0; i<result.size(); i++){
			highlightCube(result.get(i).x,result.get(i).y,false);
		}

		userWord = toUpperCase(getLine(""));
		}
	}
}

void compTurn(Set<string> userWordsSet, Grid<char> grid, Lexicon &lex){
	Set<string> compWordSet;
	findCompWords(compWordSet,grid,lex);
	compWordSet -=userWordsSet;

	foreach(string compWord in compWordSet){
		recordWordForPlayer(compWord, COMPUTER);
	}
}

void findCompWords(Set<string> &compWordSet,Grid<char> grid, Lexicon &lex){
	for(int row=0; row < grid.numRows(); row++){
		for(int col=0; col < grid.numCols(); col++){
			char temp = grid[row][col];
			grid[row][col]='0';
			string currentWord = "" + temp;  
			wrapper(compWordSet, grid, lex, row, col, currentWord);
			grid[row][col]=temp;
		}
	}
}
void wrapper(Set<string> &compWordSet,Grid<char> grid, Lexicon &lex,int row,int col,string currentWord){
	if(currentWord.length()>=4 && lex.contains(currentWord)){
		compWordSet.add(currentWord);
	}
	int startRow = (row == 0) ? row : row-1;
	int startCol = (col == 0) ? col : col-1;
	int endRow   = (row == grid.numRows() - 1) ? row : row+1;
	int endCol   = (col == grid.numCols() - 1) ? col : col+1;

	for(int x = startRow; x<=endRow; x++){
		for(int y = startCol; y<=endCol; y++){
			char temp = grid[x][y];
			if(temp!='0' && lex.containsPrefix(currentWord+temp)){
				grid[x][y]='0';
				wrapper(compWordSet, grid, lex, x, y, currentWord+temp);
				grid[x][y]=temp;
			}
		}
	}
}
