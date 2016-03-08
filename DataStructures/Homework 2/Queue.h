#pragma once
#include <iostream>

template<typename T>
class Queue
{
public:
	Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();

public:
	void Enqueue(const T& data);
	void Dequeue();

	const T& Front();
	bool isEmpty() const;
	void Print() const;
	int getSize() const;

private:
	struct Node
	{
		T data;
		Node* next;
	};

private:
	void Copy(const Queue&);

	Node* front;
	Node* rear;
	int m_size;
};

template<typename T>
Queue<T>::Queue()
{
	this->front = NULL;
	this->rear = NULL;
	this->m_size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other)
{
	Copy(other);
}

template<typename T>
Queue<T>& Queue<T>::operator =(const Queue<T>& other)
{
	if (&other != this)
	{
		Copy(other);
	}
	return *this;
}

template<typename T>
Queue<T>::~Queue()
{
	while (!isEmpty())
	{
		Dequeue();
	}
}

template<typename T>
void Queue<T>::Copy(const Queue<T>& other)
{
	if (other.front == NULL)
		front = NULL;
	else
	{
		front = new Node();
		front->data = other.front->data;

		// copy rest of Queue
		Node *new_node = front;
		for (Node *cur = other.front->next; cur; cur = cur->next)
		{
			new_node->next = new Node();
			new_node = new_node->next;
			new_node->data = cur->data;
		}
		new_node->next = NULL;
	}
}

template<typename T>
void Queue<T>::Enqueue(const T& data)
{
	Node* temp;
	try
	{
		temp = new Node();
	}
	catch (...)
	{
		printf("Cannot allocate memory! \n");
		return;
	}
	temp->data = data;
	m_size++;

	if (isEmpty())
	{
		front = rear = temp;
		return;
	}

	rear->next = temp;
	rear = temp;
}

template<typename T>
void Queue<T>::Dequeue()
{
	Node* temp = front;
	if (front == NULL)
	{
		printf("Queue is empty! \n");
		return;
	}
	if (front == rear)
	{
		front = rear = NULL;
		return;
	}
	front = front->next;
	delete temp;
	--m_size;
}

template<typename T>
const T& Queue<T>::Front()
{
	return this->front->data;
}

template<typename T>
int Queue<T>::getSize() const
{
	return this->m_size;
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	return front == NULL;
}

template<typename T>
void Queue<T>::Print() const
{
	Node* temp = front;

	if (temp)
	{
		while (temp)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		printf("\n");
	}
}