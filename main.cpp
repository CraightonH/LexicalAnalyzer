#include <iostream>
#include "Input.h"
#include <string>

using namespace std;

void testInputClass() {
	char fileName[9];
	cout << "Input text file name:";
	cin >> fileName;
	Input* file = new Input(fileName);
	while(!file->endOfFile()) {
		cout << file->extract();
	}
	
}

int main() {
	testInputClass();
	system("pause");
	return 0;
}