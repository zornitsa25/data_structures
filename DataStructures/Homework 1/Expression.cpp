#include "Expression.h"
#include "Stack.h"

Expression::Expression() :number(0), letters(""){}

Expression::Expression(int number)
{
	setNumber(number);
}

Expression::~Expression() {}

void Expression::setNumber(int number)
{
	this->number = number;
}

void Expression::setLetter(char ch)
{
	this->letters += ch;
}

void Expression::setLetter(string str)
{
	this->letters += str;
}

int Expression::getNumber() const
{
	return number;
}

string Expression::getLetter() const
{
	return letters;
}

bool Expression::isNumber(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool Expression::isLetter(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

bool Expression::isLeftBracket(char ch)
{
	return ch == '(';
}

bool Expression::isRightBracket(char ch)
{
	return ch == ')';
}

bool Expression::isValidBracket(string s)
{
	Stack<char> brackets;

	bool isValid = false;

	for (size_t i = 0; i < s.length(); i++)
	{
		if (isLeftBracket(s[i]))
		{
			brackets.Push(s[i]);
		}
		else
		{
			if (isRightBracket(s[i]) && brackets.isEmpty())
			{
				return false;
			}
			if (isRightBracket(s[i]) && (brackets.Top() == '('))
			{
				isValid = true;
				brackets.Pop();
			}
			else if (isRightBracket(s[i]) && (brackets.Top() != '('))
			{
				return false;
			}
		}
	}
	if (brackets.isEmpty())
	{
		return isValid;
	}
	return false;
}

bool Expression::onlyLetters(string s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!isLetter(s[i]))
			return false;
	}
	return true;
}