#include "Lexer.h"
using namespace std;

Lexer::Lexer(char* fileName) {
	inputFile = new Input(fileName);
	tokens.clear();
}

Lexer::~Lexer(){
	delete inputFile;
}

void Lexer::tokenizeFile() {
	if(!inputFile->opened()) {
		return;
	}
	char c;
	do {
		c = inputFile->extract();
		switch(c) {
			case ',':
				tokens.push_back(new Token(COMMA, c, inputFile->getCurrentLineNumber()));
			case '.':
				tokens.push_back(new Token(PERIOD, c, inputFile->getCurrentLineNumber()));
			case '?':
				tokens.push_back(new Token(Q_MARK, c, inputFile->getCurrentLineNumber()));
			case '(':
				tokens.push_back(new Token(LEFT_PAREN, c, inputFile->getCurrentLineNumber()));
			case ')':
				tokens.push_back(new Token(RIGHT_PAREN, c, inputFile->getCurrentLineNumber()));
			case ':':
				tokens.push_back(new Token(COLON, c, inputFile->getCurrentLineNumber()));
			case ':-':
				tokens.push_back(new Token(COLON_DASH, c, inputFile->getCurrentLineNumber()));
			case '*':
				tokens.push_back(new Token(MULTIPLY, c, inputFile->getCurrentLineNumber()));
			case '+':
				tokens.push_back(new Token(ADD, c, inputFile->getCurrentLineNumber()));
			case '#':
				tokens.push_back(new Token(COMMENT, c, inputFile->getCurrentLineNumber()));
				//TODO: IMPLEMENT LOGIC TO CHECK FOR MULTILINE
			default:
				//TODO: IMPLEMENT MORE LOGIC HERE
		}
	} while(!inputFile->endOfFile());
}

void Lexer::printTokens() {
	for(int i = 0; i < tokens.size(); i++) {
		cout << tokens.at(i)->print();
	}
}

void Lexer::printInput() {
	while(!inputFile->endOfFile()) {
		cout << inputFile->extract();
	}
	inputFile->reset();
}