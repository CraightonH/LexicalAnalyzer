#pragma once
#include <string>

using namespace std;

enum TokenType {
	COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	WHITESPACE,
	UNDEFINED,
	MYEOF
};

class Token {
	private:
		TokenType type;
		string value;
		int lineNumber;
	public:
		//---------------------------------------------------------------------------------------
		// Constructor/Destructor
		// Handles creation and deletion of the Token class.
		Token(TokenType pType, char* pValue, unsigned int pLineNumber);
		virtual ~Token();
};