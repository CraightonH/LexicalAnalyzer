#pragma once
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Input {
	private:
		ifstream inputFile;
		vector<string> fileLines;
		int currentLineNumber;
		int currentCharLoc;
		void getAllFileLines();
	public:
		//---------------------------------------------------------------------------------------
		// Constructor/Destructor
		// Handles creation and deletion of the Input class.
		Input(char* fileName);
		virtual ~Input();
		// next()
		// Get next char in stream
		char next();
		// isNextChar(char c)
		// check to see if next char in stream matches param
		bool isNextChar(char c);
		// endOfFile()
		// checks to see if at end of file
		bool endOfFile();
		// currentLineNumber()
		// returns current line number
		int getCurrentLineNumber();
};