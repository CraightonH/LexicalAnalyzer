#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Token.h"
#include "Input.h"

using namespace std;

class Lexer {
	private:
		vector<Token*> tokens;
		Input* inputFile;

	public:
		//---------------------------------------------------------------------------------------
		// Constructor/Destructor
		// Handles creation and deletion of the Token class.
		Lexer(char* fileName);
		virtual ~Lexer();
		// tokenizeFile()
		// interacts with the Input class to read through and create tokens
		void tokenizeFile();
		// isAlphabet()
		// determines if the input is a letter of the alphabet
		bool isAlphabet(char c);
		// getKeyword()
		// finds keyword or ID in the next sequence of characters
		string getKeywordOrID(char c);
		// getKeywordOrIDToken()
		// determines if the input is a keyword and returns token of that keyword
		Token* getKeywordOrIDToken(string val);
		// printTokens();
		// prints the tokens that have been made
		void printTokens();
		// printInput();
		// prints the input provided to the Lexer
		void printInput();
};