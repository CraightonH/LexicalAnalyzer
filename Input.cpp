#include "Input.h"
using namespace std;


Input::Input(char* fileName) {
	inputFile.open(fileName);
	newLineCharPositions.clear();
	fileLength = getFileLength();
	getLineNumbers();
}

Input::~Input(){}

int Input::getFileLength() {
	moveToLoc(inputFile.end);
	int ret = inputFile.tellg();
	moveToLoc(inputFile.beg);
	return ret;
}

void Input::getLineNumbers() {
	char c;
	int charPos = 0;
	while(inputFile.get(c)) {
		charPos++;
		if (c == '\n') {
			newLineCharPositions.push_back(charPos);
		}
	}
	reset();
}

char Input::extract() {
	char ret = inputFile.get();
	return ret;
}

string Input::extract(char delim) {
	string ret;
	char c;
	do {
		c = inputFile.get();
		ret += c;
	} while(c != delim);
	return ret;
}

bool Input::isNextChar(char c){
	char g = inputFile.peek();
	if (g == c) {
		return true;
	}
	return false;
}

bool Input::endOfFile(){
	return inputFile.eof();
}

bool Input::opened(){
	return inputFile.is_open();
}

int Input::getCurrentLineNumber(){
	int currentCharLoc = getCurrentCharLoc();
	for(int i = 0; i < newLineCharPositions.size(); i++) {
		if (currentCharLoc > newLineCharPositions.at(newLineCharPositions.size() - 1)) {
			return newLineCharPositions.size();
		} else if (currentCharLoc < newLineCharPositions.at(0)) {
			return i + 1;
		} else if (currentCharLoc == newLineCharPositions.at(i)) {
			return i + 1;
		} else if (currentCharLoc > newLineCharPositions.at(i) && currentCharLoc < newLineCharPositions.at(i + 1)) {
			return i + 1;
		}
	}
}

int Input::getCurrentCharLoc(){
	return inputFile.tellg();
}

void Input::moveToLoc(int loc) {
	inputFile.seekg(0, loc);
}

void Input::reset() {
	inputFile.clear();
	moveToLoc(inputFile.beg);
}