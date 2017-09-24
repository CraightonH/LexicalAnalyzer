#include "Token.h"
using namespace std;

Token::Token() {}

Token::Token(TokenType pType, char pValue, unsigned int pLineNumber) {
	type = pType;
	value = pValue;
	lineNumber = pLineNumber;
}

Token::Token(TokenType pType, string pValue, unsigned int pLineNumber) {
	type = pType;
	value = pValue;
	lineNumber = pLineNumber;
}

Token::~Token(){}

Token* Token::updateValues(TokenType pType, string pValue, unsigned int pLineNumber) {
	type = pType;
	value = pValue;
	lineNumber = pLineNumber;
	return this;
}

string Token::print() {
	string strType = "";
	switch(type) {
	case COMMA: 
		strType = "COMMA";
		break;
	case PERIOD: 
		strType = "PERIOD";
		break;
	case Q_MARK: 
		strType = "Q_MARK";
		break;
	case LEFT_PAREN: 
		strType = "LEFT_PAREN";
		break;
	case RIGHT_PAREN: 
		strType = "RIGHT_PAREN";
		break;
	case COLON: 
		strType = "COLON";
		break;
	case COLON_DASH: 
		strType = "COLON_DASH";
		break;
	case MULTIPLY: 
		strType = "MULTIPLY";
		break;
	case ADD: 
		strType = "ADD";
		break;
	case SCHEMES: 
		strType = "SCHEMES";
		break;
	case FACTS: 
		strType = "FACTS";
		break;
	case RULES: 
		strType = "RULES";
		break;
	case QUERIES: 
		strType = "QUERIES";
		break;
	case ID: 
		strType = "ID";
		break;
	case STRING: 
		strType = "STRING";
		break;
	case COMMENT: 
		strType = "COMMENT";
		break;
	case WHITESPACE: 
		strType = "WHITESPACE";
		break;
	case UNDEFINED: 
		strType = "UNDEFINED";
		break;
	case MYEOF: 
		strType = "EOF";
		break;
	default:
		break;
	}
	ostringstream os;
	os << "(" << strType << ",\"" << value << "\"," << lineNumber << ")";
	return os.str();
}