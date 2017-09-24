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
	int charPos = -1;
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
		if (c != '\n') {
			ret += c;
		}
	} while(c != delim);
	ret = extract(delim, ret);
	return ret;
}

// private function reserved for possible recursion cases
string Input::extract(char delim, string str) {
	if (delim == '\'') {
		if (isNextChar('\'')) {
			char c;
			do {
				c = inputFile.get();
				str += c;
			} while(c != delim);
			str = extract(delim, str);
		}
	}
	return str;
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

int Input::getCurrentLineNumber() {
	int currentCharLoc = getCurrentCharLoc();
	for(int i = 0; i < newLineCharPositions.size(); i++) {
		if (currentCharLoc == -1) {
			return getMaxReadableLines() + 1;
		} else if (currentCharLoc > newLineCharPositions.at(newLineCharPositions.size() - 1)) {
			return getMaxReadableLines();
		} else if (currentCharLoc < newLineCharPositions.at(0)) {
			return i + 1;
		} else if (currentCharLoc == newLineCharPositions.at(i)) {
			return i + 1;
		} else if (currentCharLoc > newLineCharPositions.at(i) && currentCharLoc < newLineCharPositions.at(i + 1)) {
			return i + 1;
		}
	}
}

int Input::getMaxReadableLines() {
	return newLineCharPositions.size();
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

void Input::returnChar(char c) {
	inputFile.putback(c);
}
