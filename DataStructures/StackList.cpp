#include <iostream>
using namespace std;

class Stack
{
public:

	Stack()
	{
		data = 0;
		link = NULL;
		top = NULL;
	}

	void Push(int x)
	{
		Stack* temp = new Stack();
		temp->data = x;
		temp->link = top;
		top = temp;
	}

	void Pop()
	{
		if (top == NULL)
		{
			printf("Stack is empty! \n");
			return;
		}
		Stack* temp = top;
		top = top->link;
		delete temp;
	}

	bool isEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int Top()
	{
		return top->data;
	}

	void Print()
	{
		Stack* temp = top;
		while (temp != NULL)
		{
			printf("%d ", temp->data);
			temp = temp->link;
		}
		printf("\n");
	}

private:
	int data;
	Stack* link;
	Stack* top;
};


int main()
{
	Stack info;
	info.Push(13);
	info.Push(21);
	info.Push(14);
	info.Push(22);
	info.Push(15);

	info.Print();

	info.Pop();

	info.Print();

	return 0;
}
