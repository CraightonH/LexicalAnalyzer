#include "Token.h"
using namespace std;


Token::Token(TokenType pType, char* pValue, unsigned int pLineNumber) {
	type = pType;
	value = pValue;
	lineNumber = pLineNumber;
}

Token::~Token(){}
