#pragma once
#include <iostream>
#include <string>
#include "LQueue.h"
using namespace std;
//ostream & operator<<(ostream &out, const Token &t);
class Token {
public:
	Token() {
		word = "";
		line = 0;
	}
	Token(string w, int l) {
		word = w;
		line = l;
		//lineQ.enqueue(l);
	}

	string getWord(){ return word; }

	void setWord(string w) { word = w; }
	void setLine(int l) { line = l; }
	void display(ostream &out)const {
		out << word;
		out << lineQ;
	}
	void queueLine(int l) {lineQ.enqueue(l);}
	int getLine() { return line; }
private:
	string word;
	int line;	//line in text document in which the word appears
	Queue<int> lineQ;
};

ostream & operator<<(ostream & out, const Token &t) {
	t.display(out);
	return out;
}