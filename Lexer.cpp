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
	int curLine = 1;
	do {
		s = "";
		c = inputFile->extract();
		switch(c) {
			case ',':				
				tokens.push_back(new Token(COMMA, c, curLine));
				break;
			case '.':
				tokens.push_back(new Token(PERIOD, c, curLine));
				break;
			case '?':
				tokens.push_back(new Token(Q_MARK, c, curLine));
				break;
			case '(':
				tokens.push_back(new Token(LEFT_PAREN, c, curLine));
				break;
			case ')':
				tokens.push_back(new Token(RIGHT_PAREN, c, curLine));
				break;
			case ':':
				if (inputFile->isNextChar('-')) {
					s = c;
					s += inputFile->extract('-');
					tokens.push_back(new Token(COLON_DASH, s, curLine));
				} else {
					tokens.push_back(new Token(COLON, c, curLine));
				}
				break;
			case ':-':
				tokens.push_back(new Token(COLON_DASH, c, curLine));
				break;
			case '*':
				tokens.push_back(new Token(MULTIPLY, c, curLine));
				break;
			case '+':
				tokens.push_back(new Token(ADD, c, curLine));
				break;
			case '#':
				commentMachine(c, curLine);
				break;
			case '\'':
				stringMachine(c, curLine);
				break;
			default:
				//TODO: IMPLEMENT ID AND KEYWORDS LOGIC HERE
				// ASSUME ID
				if (isAlphabet(c)) {
					s = getKeywordOrID(c);
					tokens.push_back(getKeywordOrIDToken(s, curLine));
				} else if (c == '\n') {
					curLine++;
				} else if (isspace(c)) {
					// AS PER INSTRUCTIONS, DO NOT SAVE WHITESPACE
				} else if (c == EOF || inputFile->endOfFile()) {
					tokens.push_back(new Token(MYEOF, "", inputFile->getMaxReadableLines() + 1));
				} else {
					// ALL ELSE IS UNDEFINED
					tokens.push_back(new Token(UNDEFINED, c, curLine));
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

void Lexer::stringMachine(char c, int& curLine) {
	string s = "";
	int incrementCurLine = 0;
	bool endFileFound = false;
	s = recurseString(c, s, incrementCurLine, endFileFound);
	//inputFile->returnChar(c);
	if (endFileFound) {
		tokens.push_back(new Token(UNDEFINED, s, curLine));
		curLine += incrementCurLine;
		tokens.push_back(new Token(MYEOF, "", curLine));
	} else {
		tokens.push_back(new Token(STRING, s, curLine));
		curLine += incrementCurLine;
	}
}

string Lexer::recurseString(char c, string s, int& incrementCurLine, bool& endFileFound) {
	//if (inputFile->isNextChar('\'')) {
		do {
			if (c == EOF) {
				endFileFound = true;
				return s;
			}
			if (c == '\n') {
				incrementCurLine++;
			}
			s += c;
			c = inputFile->extract();
		} while(c != '\'');
		s += c;
		if (c == '\'' && inputFile->isNextChar('\'')) {
			c = inputFile->extract();
			s = recurseString(c,s,incrementCurLine,endFileFound);
		}
	//}
	return s;
}

void Lexer::commentMachine(char c, int& curLine) {
	string s = "";
	int incrementCurLine = 0;
	if (inputFile->isNextChar('|')) {
		s += c;
		c = inputFile->extract();
		while(c != '#') {
			if (c == '\n') {
				incrementCurLine = true;
			}
			s += c;
			c = inputFile->extract();
		}
		if (c == '#') {
			s += c;
			c = inputFile->extract();
		}
	} else {
		while(c != '\n') {
			if (c != '\r') {
				s += c;
			}
			c = inputFile->extract();
		}
		inputFile->returnChar(c);
	}
	tokens.push_back(new Token(COMMENT, s, curLine));
	curLine += incrementCurLine;
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

Token* Lexer::getKeywordOrIDToken(string val, int& curLine) {
	if (val == "Schemes") {
		return new Token(SCHEMES, val, curLine);
	} else if (val == "Facts") {
		return new Token(FACTS, val, curLine);
	} else if (val == "Rules") {
		return new Token(RULES, val, curLine);
	} else if (val == "Queries") {
		return new Token(QUERIES, val, curLine);
	} else {
		// ASSUME ID
		return new Token(ID, val, curLine);
	}
	return new Token();
}
