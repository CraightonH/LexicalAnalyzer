#pragma once
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

class Input {
	private:
		ifstream inputFile;
		unsigned int fileLength;
		vector<int> newLineCharPositions;

		void getLineNumbers();
		int getFileLength();
		string extract(char delim, string str);
	public:
		//---------------------------------------------------------------------------------------
		// Constructor/Destructor
		// Handles creation and deletion of the Input class.
		Input(char* fileName);
		virtual ~Input();
		// extract()
		// Get next char
		char extract();
		// extract(char delim)
		// Get next char, stopping at the next delim char
		string extract(char delim);
		// isNextChar(char c)
		// check to see if next char in stream matches param
		bool isNextChar(char c);
		// endOfFile()
		// checks to see if at end of file
		bool endOfFile();
		// opened()
		// checks to see if stream opened
		bool opened();
		// getCurrentLineNumber()
		// returns current line number
		int getCurrentLineNumber();
		// getCurrentCharLoc()
		// returns current character location
		int getCurrentCharLoc();
		// moveToLoc()
		// moves to the specified location in the buffer
		void moveToLoc(int loc);
		// getMaxReadableLines()
		// returns the max number of readable lines (does not include EOF line)
		int getMaxReadableLines();
		// reset()
		// resets stream to beginning
		void reset();
		// returnChar()
		// returns char to stream
		void returnChar(char c);
};