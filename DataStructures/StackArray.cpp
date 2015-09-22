#include <iostream>
using namespace std;

int const MAX_SIZE = 101;

class Stack
{
public:
	Stack()
	{
		top = -1;
	}

	void Push(int x)
	{
		if (top == MAX_SIZE - 1)
		{
			printf("Stack is full! \n");
			return;
		}
		Array[++top] = x;
	}

	void Pop()
	{
		if (top == -1)
		{
			printf("Cannot pop an element! \n");
			return;
		}
		top--;
	}

	int Top()
	{
		return Array[MAX_SIZE - 1];
	}

	bool isEmpty()
	{
		if (top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Print()
	{
		printf("Stack: ");
		for (size_t i = 0; i <= top; i++)
		{
			printf("%d ", Array[i]);
		}
		printf("\n");
	}

private:
	int Array[MAX_SIZE];
	int top;
};

int main()
{
	Stack numbers;
	cout << numbers.isEmpty() << endl;

	for (size_t i = 0; i < 10; i++)
	{
		numbers.Push(i);
	}
	numbers.Pop();
	numbers.Print();

	return 0;
}