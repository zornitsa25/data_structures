#pragma once

#include <iostream>
using namespace std;

template<typename T>
class Stack
{
public:
	Stack();
	Stack(const Stack&);
	Stack& operator= (const Stack&);
	~Stack();

public:
	void Init();
	void Push(const T&);
	void Pop();
	T& Top();
	size_t Lenght();
	void Print();
	bool isEmpty() const;

private:
	class Node
	{
	public:
		T data;
		Node* next;

		Node();
		Node(T data);
	};

	void Copy(const Stack& other);
	void Delete();
	Node* top;
};

template<typename T>
Stack<T>::Node::Node() :data(0), next(nullptr){}

template<typename T>
Stack<T>::Node::Node(T data)
{
	this->data = data;
}

template<typename T>
Stack<T>::Stack()
{
	Init();
}

template<typename T>
Stack<T>::Stack(const Stack& other)
{
	top = other.top;
	Copy(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
	if (this != &other)
	{
		Delete();
		Copy(other);
	}
	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	Delete();
}

template<typename T>
void Stack<T>::Delete()
{
	Node* temp;
	while (top)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
	Init();
}

template<typename T>
void Stack<T>::Init()
{
	top = NULL;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	if (top == NULL)
		return true;
	else
		return false;
}

template<typename T>
void Stack<T>::Copy(const Stack& other)
{
	if (other.isEmpty())
	{
		return;
	}
	Node* first, *second;

	try
	{
		top = new Node(other.top->data);
		first = top;
		second = other.top->next;

		while (second)
		{
			first->next = new Node(second->data);
			first = first->next;
			second = second->next;
		}
	}
	catch (bad_alloc&)
	{
		Delete();
		throw;
	}
}

template<typename T>
void Stack<T>::Push(const T& data)
{
	Node* temp;
	try
	{
		temp = new Node();
	}
	catch (...)
	{
		return;
	}
	temp->data = data;
	temp->next = top;
	top = temp;
}

template<typename T>
void Stack<T>::Pop()
{
	Node* temp = top;
	if (!isEmpty())
	{
		T value = top->data;
		top = top->next;
		delete temp;
	}
	else
	{
		printf("Stack is empty! \n");
		return;
	}
}

template<typename T>
T& Stack<T>::Top()
{
	try
	{
		if (!isEmpty())
		{
			return top->data;
		}
		else
		{
			throw 1;
		}
	}
	catch (int ex)
	{
		printf("An exception occurred. There is no data in the stack! \n");
		throw;
	}
}

template<typename T>
void Stack<T>::Print()
{
	Node* temp = top;
	while (temp!=NULL)
	{
		cout << temp->data;
		temp = temp->next;
	};
}

template<typename T>
size_t Stack<T>::Lenght()
{
	size_t count = 0;
	Node* temp = top;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}