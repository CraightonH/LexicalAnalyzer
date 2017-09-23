#include <iostream>
#include "Input.h"
#include <string>

using namespace std;

void testInputClass(char* fileName) {
	Input* file = new Input(fileName);
	while(!file->endOfFile()) {
		cout << file->extract();
	}
	delete file;
}

int main() {
	char fileName[256];
	cout << "Input text file name:";
	cin.getline(fileName,256);
	//cout << "fileName:" << fileName << "\n";
	//testInputClass(fileName);
	Input* file = new Input(fileName);
	system("pause");
	delete file;
	return 0;
}