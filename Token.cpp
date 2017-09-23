#include "Token.h"
using namespace std;


Token::Token(TokenType pType, char pValue, unsigned int pLineNumber) {
	type = pType;
	value = pValue;
	lineNumber = pLineNumber;
}

Token::~Token(){}

string Token::print() {
	string strType = "";
	switch(type) {
	case COMMA: strType = "COMMA";
	case PERIOD: strType = "PERIOD";
	case Q_MARK: strType = "Q_MARK";
	case LEFT_PAREN: strType = "LEFT_PAREN";
	case RIGHT_PAREN: strType = "RIGHT_PAREN";
	case COLON: strType = "COLON";
	case COLON_DASH: strType = "COLON_DASH";
	case MULTIPLY: strType = "MULTIPLY";
	case ADD: strType = "ADD";
	case SCHEMES: strType = "SCHEMES";
	case FACTS: strType = "FACTS";
	case RULES: strType = "RULES";
	case QUERIES: strType = "QUERIES";
	case ID: strType = "ID";
	case STRING: strType = "STRING";
	case COMMENT: strType = "COMMENT";
	case WHITESPACE: strType = "WHITESPACE";
	case UNDEFINED: strType = "UNDEFINED";
	case MYEOF: strType = "EOF";
	}
	return "(" + strType + "," + value + "," + lineNumber + ")";
}