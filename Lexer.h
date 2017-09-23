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
		// printTokens();
		// prints the tokens that have been made
		void printTokens();
		// printInput();
		// prints the input provided to the Lexer
		void printInput();
};