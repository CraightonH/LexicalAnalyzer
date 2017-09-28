#include "Lexer.h"
using namespace std;

Lexer::Lexer(char* fileName) {
	inputFile = new Input(fileName);
	tokens.clear();
}

Lexer::~Lexer(){
	delete inputFile;
	for(int i = 0; i < tokens.size(); i++) {
		delete tokens.at(i);
	}
}

void Lexer::tokenizeFile() {
	if(!inputFile->opened()) {
		return;
	}
	char c;
	//Token* tok = new Token();
	int curLine = 1;
	do {
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
				colonOrColonDashMachine(c, curLine);
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
				determineDefault(c, curLine);
				break;
		}
	} while(!inputFile->endOfFile());
}

void Lexer::printTokens() {
	tokenizeFile();
	for(int i = 0; i < tokens.size(); i++) {
		cout << tokens.at(i)->print() << "\n";
	}
	cout << "Total Tokens = " << tokens.size();
}

void Lexer::printInput() {
	while(!inputFile->endOfFile()) {
		cout << inputFile->extract();
	}
	inputFile->reset();
}

void Lexer::colonOrColonDashMachine(char c, int& curLine) {
	if (inputFile->isNextChar('-')) {
		string s = "";
		s = c;
		s += inputFile->extract();
		tokens.push_back(new Token(COLON_DASH, s, curLine));
	} else {
		tokens.push_back(new Token(COLON, c, curLine));
	}
}

void Lexer::determineDefault(char c, int& curLine) {
	//TODO: IMPLEMENT ID AND KEYWORDS LOGIC HERE
	// ASSUME ID
	if (isAlphabet(c)) {
		string s = "";
		s = getKeywordOrID(c);
		tokens.push_back(getKeywordOrIDToken(s, curLine));
	} else if (c == '\n') {
		curLine++;
	} else if (isspace(c)) {
		// AS PER INSTRUCTIONS, DO NOT SAVE WHITESPACE
	} else {
		// ALL ELSE IS UNDEFINED
		if (c != EOF) {
			tokens.push_back(new Token(UNDEFINED, c, curLine));
		}
	}
	if (c == EOF || inputFile->endOfFile()) {
		tokens.push_back(new Token(MYEOF, "", inputFile->getMaxReadableLines() + 1));
	}
}

bool Lexer::isAlphabet(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
		return true;
	}
	return false;
}

bool Lexer::isNumber(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}

void Lexer::stringMachine(char c, int& curLine) {
	string s = "";
	s += c;
	int incrementCurLine = 0;
	bool endFileFound = false;
	do {
		c = inputFile->extract();
		if (c == EOF) {
			endFileFound = true;
			break;
		}
		if (c == '\n') {
			incrementCurLine++;
		}
		s += c;
		if (c == '\'' && inputFile->isNextChar('\'')) {
			// DOUBLE QUOTE CASE = ACT AS THOUGH BOTH QUOTES WERE NOT SEEN
			c = inputFile->extract();
			s += c;
		} else if (c == '\'' && !inputFile->isNextChar('\'')) {
			// TERMINATION CASE = QUOTE NOT FOLLOWED BY QUOTE
			break;
			/*
			if (inputFile->isNextChar('\'')) {
				c = inputFile->extract();
				s += c;
				c = inputFile->extract();
				if (c == EOF) {
					endFileFound = true;
					break;
				} else {
					s += c;
				}
			}
			*/
		}
	} while(true);
	if (endFileFound) {
		tokens.push_back(new Token(UNDEFINED, s, curLine));
		curLine += incrementCurLine;
		tokens.push_back(new Token(MYEOF, "", inputFile->getMaxReadableLines() + 1));
	} else {
		tokens.push_back(new Token(STRING, s, curLine));
		curLine += incrementCurLine;
		if (inputFile->endOfFile()) {
			tokens.push_back(new Token(MYEOF, "", inputFile->getMaxReadableLines() + 1));
		}
	}
}

void Lexer::commentMachine(char c, int& curLine) {
	//cout << "commentMachine()";
	string s = "";
	int incrementCurLine = 0;
	if (inputFile->isNextChar('|')) {
		//cout << "multiline comment found";
		bool undef = false;
		s += c;
		c = inputFile->extract();
		while(true) {
			if (c == '\n') {
				incrementCurLine++;
			}
			/*
			if (c == EOF) {
				break;
			}
			*/
			if (c == '|' && inputFile->isNextChar('#')) {
				// IF CURRENT CHAR IS | AND NEXT CHAR IS #, SAVE BOTH AND BREAK
				s += c;
				c = inputFile->extract();
				s += c;
				break;
			} else if (c == EOF) {
				// DID NOT TERMINATE WITH STRING "|#" THEREFORE UNDEFINED
				undef = true;
				break;
			}
			s += c;
			c = inputFile->extract();
		}
		if (undef) {
			tokens.push_back(new Token(UNDEFINED, s, curLine));
		} else {
			tokens.push_back(new Token(COMMENT, s, curLine));
		}
		curLine += incrementCurLine;
		/*
		if (c == '#') {
			s += c;
			c = inputFile->extract();
			tokens.push_back(new Token(COMMENT, s, curLine));
			curLine += incrementCurLine;
		} else if (c == EOF) {
			tokens.push_back(new Token(UNDEFINED, s, curLine));
		}
*/
		//cout << "done with multiline";
	} else {
		//cout << "single line comment found";
		while(c != '\n') {
			//cout << "char " << c;
			if (c != '\r') {
				s += c;
			}
			c = inputFile->extract();
			if (c == EOF) {
				//cout << "single line EOF found";
				break;
			}
		}
		//cout << "done with single comment, creating token";
		tokens.push_back(new Token(COMMENT, s, curLine));
		// PUT BACK \n CHAR
		if (c != EOF) {
			inputFile->returnChar(c);
		}
	}
	if (inputFile->endOfFile()) {
		//cout << "end of file found, creating token";
		tokens.push_back(new Token(MYEOF, "", inputFile->getMaxReadableLines() + 1));
	}
}

string Lexer::getKeywordOrID(char c) {
	string str = "";
	while(isAlphabet(c) || isNumber(c)) {
		if (c != '\n') {
			str += c;
		}
		c = inputFile->extract();
		if (c == EOF) {
			break;
		}
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
	if (inputFile->endOfFile()) {
		tokens.push_back(new Token(MYEOF, "", inputFile->getMaxReadableLines() + 1));
	}
	return new Token();
}
