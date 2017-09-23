#include "Input.h"
using namespace std;


Input::Input(char* fileName) {
	currentLineNumber = 0;
	currentCharLoc = 0;
	if(!fileLines.empty()) {
		fileLines.clear();
	}
	inputFile.open(fileName);
	getAllFileLines();
}

Input::~Input(){}

void Input::getAllFileLines() {
	string line = "";
	while(!inputFile.eof()) {
		getline(inputFile, line);
		fileLines.push_back(line);
	}
}

char Input::next() {
	string line = fileLines.at(currentLineNumber);
	char ret;
	if(line.length() <= currentCharLoc) {
		char ret = line.at(currentCharLoc);
		currentCharLoc++;
	} else {
		currentLineNumber++;
		currentCharLoc = 0;
		return next();
	}
	return ret;
/*
	currentCharLoc++;
	char c = inputFile.get();
	if(c == ) {
		
	}
	return c;
*/
}

bool Input::isNextChar(char c){
	string line = fileLines.at(currentLineNumber);
	if(line.length() <= currentCharLoc + 1) {
		char g = line.at(currentCharLoc + 1);
		if(c == g) {
			return true;
		}
	}
	return false;
}

bool Input::endOfFile(){
	if(currentLineNumber == fileLines.size() && currentCharLoc == ) {
		
	}
}
