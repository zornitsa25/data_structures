// Zornitsa Chopova 45043
#include "Stack.h"
#include "Expression.h"

#include <string>
using namespace std;

int main()
{
	Stack<Expression> expression;
	Expression first;
	expression.Push(first);

	string str;
	cin >> str;

	if (!Expression::isValidBracket(str) && !Expression::onlyLetters(str))
	{
		cout << "Invalid input! \n";
		return 1;
	}

	int cur_num = -1;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (Expression::isLetter(str[i]))
		{
			expression.Top().setLetter(str[i]);
		}
		else if (Expression::isNumber(str[i]))
		{
			if (cur_num < 0)
			{
				cur_num = str[i] - '0'; // first digit
			}
			else
			{
				cur_num = cur_num * 10 + str[i] - '0';
			}
		}
		else if (Expression::isLeftBracket(str[i]))
		{
			Expression new_obj(cur_num);
			expression.Push(new_obj);
			cur_num = -1;
		}
		else if (Expression::isRightBracket(str[i]))
		{
			string temp;
			for (int i = 0; i < expression.Top().getNumber(); i++)
			{
				temp += expression.Top().getLetter();
			}
			expression.Pop();
			expression.Top().setLetter(temp);
		}
	}
	cout << expression.Top().getLetter() << "\n";

	return 0;
}