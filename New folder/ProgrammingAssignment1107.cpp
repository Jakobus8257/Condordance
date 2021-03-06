#include "LQueue.h"
#include "BST.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Token.h"
using namespace std;

const int SIZE = 26;//number of characters in the alphabet

void readFile(ifstream & inputFile, BST tree[]);
void displayConcord(BST tree[]);
int main() {
	BST concord[SIZE];
	ifstream infile;
	infile.open("binaryTreeRead.txt");

	if (!infile) {//check file opens
		cerr << "File did not open correctly, exiting program" << endl;
		exit(1107);
	}

	readFile(infile, concord);

	displayConcord(concord);
	
	return 0;
}
void readFile(ifstream & inputFile, BST tree[]) {
	string inputString;
	Token inToken;
	int lineNum = 0;//increments the number of newline characters
	char stringChar;

	while (inputFile.get(stringChar)) {

		if (stringChar == '\n') 
			lineNum++;//increment line number each newline

		else if (stringChar == ' ') {//space indicates end of word

			inToken = Token(inputString, lineNum); //sets token to string and line value
			inToken.queueLine(lineNum);
			tree[toupper(inputString[0] - 'A')].insert(inToken);

			inputString = ""; //reset string	
		}
		else if (isalpha(stringChar))
			inputString += toupper(stringChar);
		

	}
}
void displayConcord(BST tree[]) {
	for (int i = 0; i < SIZE; i++) {
		cout << static_cast<char>('A'+i) << ": ";//displays character value of tree
		tree[i].graph(cout);
		cout << endl;
	}
}