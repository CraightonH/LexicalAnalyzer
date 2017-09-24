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
	int curLine = 0;
	do {
		s = "";
		c = inputFile->extract();
		curLine = inputFile->getCurrentLineNumber();
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
				break;
			default:
				//TODO: IMPLEMENT ID AND KEYWORDS LOGIC HERE
				// ASSUME ID
				if (isAlphabet(c)) {
					s = getKeywordOrID(c);
					tokens.push_back(getKeywordOrIDToken(s));
				} else if (isspace(c)) {
					// AS PER INSTRUCTIONS, DO NOT SAVE WHITESPACE
				} else if (c == EOF || inputFile->endOfFile()) {
					tokens.push_back(new Token(MYEOF, "", inputFile->getMaxReadableLines() + 1));
				} else {
					// ALL ELSE IS UNDEFINED
					tokens.push_back(new Token(UNDEFINED, c, inputFile->getCurrentLineNumber()));
				}
				break;
		}
	} while(!inputFile->endOfFile());
}

void Lexer::printTokens() {
	tokenizeFile();
	for(int i = 0; i < tokens.size(); i++) {
		cout << tokens.at(i)->print() << "\n";
	}
	cout << "Total tokens = " << tokens.size();
}

void Lexer::printInput() {
	while(!inputFile->endOfFile()) {
		cout << inputFile->extract();
	}
	inputFile->reset();
}

bool Lexer::isAlphabet(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
		return true;
	}
	return false;
}

string Lexer::getKeywordOrID(char c) {
	string str = "";
	while(isAlphabet(c)) {
		if (c != '\n') {
			str += c;
		}
		c = inputFile->extract();
	}
	inputFile->returnChar(c);
	return str;
}

Token* Lexer::getKeywordOrIDToken(string val) {
	if (val == "Schemes") {
		return new Token(SCHEMES, val, inputFile->getCurrentLineNumber());
	} else if (val == "Facts") {
		return new Token(FACTS, val, inputFile->getCurrentLineNumber());
	} else if (val == "Rules") {
		return new Token(RULES, val, inputFile->getCurrentLineNumber());
	} else if (val == "Queries") {
		return new Token(QUERIES, val, inputFile->getCurrentLineNumber());
	} else {
		// ASSUME ID
		return new Token(ID, val, inputFile->getCurrentLineNumber());
	}
	return new Token();
}
