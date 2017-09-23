#include "Input.h"
using namespace std;


Input::Input(char* fileName) {
	inputFile.open(fileName);
	inputFile.seekg(0,inputFile.end);
	fileLength = inputFile.tellg();
	inputFile.seekg(0,inputFile.beg);
	newLineCharPositions.clear();
}

Input::~Input(){}

void Input::getLineNumbers() {
	char c;
	int i = 0;
	while(inputFile.get(c)) {
		if (c == '\n') {
			++i;
			newLineCharPositions.push_back(i);
		}
	}
}

char Input::extract() {
	char ret = inputFile.get();
	return inputFile.get();
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
	inputFile.seekg(loc);
}