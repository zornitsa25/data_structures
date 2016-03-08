#pragma once

#include <string>
using namespace std;

class Expression
{
public:
	Expression();
	Expression(int);
	~Expression();

	void setNumber(int);
	void setLetter(char);
	void setLetter(string);

	int getNumber() const;
	string getLetter() const;

public:
	static bool isNumber(char ch);
	static bool isLetter(char ch);
	static bool isLeftBracket(char ch);
	static bool isRightBracket(char ch);
	static bool isValidBracket(string s);
	static bool onlyLetters(string s);

private:
	int number;
	string letters;
};