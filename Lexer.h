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

		// isAlphabet()
		// determines if the input is a letter of the alphabet
		bool isAlphabet(char c);
		// isNumber()
		// determines if the input is a letter of the alphabet
		bool isNumber(char c);
		// getKeywordOrID()
		// finds keyword or ID in the next sequence of characters
		string getKeywordOrID(char c);
		// commentMachine()
		// will handle getting comments
		void commentMachine(char c, int& curLine);
		// stringMachine()
		// will handle getting strings
		void stringMachine(char c, int& curLine);
		// colonOrColonDashMachine()
		// will handle getting strings
		void colonOrColonDashMachine(char c, int& curLine);
		// determineDefault()
		// will handle getting strings
		void determineDefault(char c, int& curLine);
		// getKeywordOrIDToken()
		// determines if the input is a keyword and returns token of that keyword
		Token* getKeywordOrIDToken(string val, int& curLine);
	public:
		//---------------------------------------------------------------------------------------
		// Constructor/Destructor
		// Handles creation and deletion of the Token class.
		Lexer(char* fileName);
		//---------------------------------------------------------------------------------------
		// Constructor/Destructor
		// Handles creation and deletion of the Token class.
		//Lexer(char* fileName[]);
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