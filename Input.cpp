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
	inputFile.clear();
	moveToLoc(inputFile.beg);
	int tmpFileLength = getFileLength();
}

char Input::extract() {
	char ret = inputFile.get();
	return ret;
}

char Input::extract(char delim) {
	char ret;
	do {
		ret += inputFile.get();
	} while(ret != delim);
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

int Input::getCurrentLineNumber(){
	for(int i = 0; i < newLineCharPositions.size(); i++) {
		if (i = 0) {
			if (getCurrentCharLoc() < newLineCharPositions.at(i)) {
				return i;
			}
		} else if(i = newLineCharPositions.size()) {
			if (getCurrentCharLoc() > newLineCharPositions.at(i)) {
				return i;
			}
		} else {
			if (getCurrentCharLoc() > newLineCharPositions.at(i) && getCurrentCharLoc() < newLineCharPositions.at(i + 1)) {
				return i + 1;
			}
		}
	}
}

int Input::getCurrentCharLoc(){
	return inputFile.tellg();
}

void Input::moveToLoc(int loc) {
	inputFile.seekg(0, loc);
}