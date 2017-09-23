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
	//Token* tok = new Token();
	string s;
	char innerExtractionChar;
	do {
		s = "";
		c = inputFile->extract();
		switch(c) {
			case ',':
				tokens.push_back(new Token(COMMA, c, inputFile->getCurrentLineNumber()));
				break;
			case '.':
				tokens.push_back(new Token(PERIOD, c, inputFile->getCurrentLineNumber()));
				break;
			case '?':
				tokens.push_back(new Token(Q_MARK, c, inputFile->getCurrentLineNumber()));
				break;
			case '(':
				tokens.push_back(new Token(LEFT_PAREN, c, inputFile->getCurrentLineNumber()));
				break;
			case ')':
				tokens.push_back(new Token(RIGHT_PAREN, c, inputFile->getCurrentLineNumber()));
				break;
			case ':':
				if (inputFile->isNextChar('-')) {
					s = c;
					s += inputFile->extract('-');
					tokens.push_back(new Token(COLON_DASH, s, inputFile->getCurrentLineNumber()));
				} else {
					tokens.push_back(new Token(COLON, c, inputFile->getCurrentLineNumber()));
				}
				break;
			case ':-':
				tokens.push_back(new Token(COLON_DASH, c, inputFile->getCurrentLineNumber()));
				break;
			case '*':
				tokens.push_back(new Token(MULTIPLY, c, inputFile->getCurrentLineNumber()));
				break;
			case '+':
				tokens.push_back(new Token(ADD, c, inputFile->getCurrentLineNumber()));
				break;
			case '#':
				s = c;
				if (inputFile->isNextChar('|')) {
					s += inputFile->extract('#');
				} else {
					s += inputFile->extract('\n'); 
				}
				tokens.push_back(new Token(COMMENT, s, inputFile->getCurrentLineNumber()));
				break;
			case '\'':
				s = c;
				s += inputFile->extract('\'');
				tokens.push_back(new Token(STRING, s, inputFile->getCurrentLineNumber()));
			default:
				//TODO: IMPLEMENT MORE LOGIC HERE
				break;
		}
	} while(!inputFile->endOfFile());
}

void Lexer::printTokens() {
	tokenizeFile();
	for(int i = 0; i < tokens.size(); i++) {
		cout << tokens.at(i)->print() << "\n";
	}
	cout << "\nTotal tokens = " << tokens.size();
}

void Lexer::printInput() {
	while(!inputFile->endOfFile()) {
		cout << inputFile->extract();
	}
	inputFile->reset();
}