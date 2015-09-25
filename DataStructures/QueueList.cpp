#include <iostream>
using namespace std;

template<typename T>
class Queue
{
private:
	T data;
	Queue* next;
	Queue* front;
	Queue* rear;

public:
	Queue();

	void Enqueue(T data);
	void Dequeue();
	T Front();
	bool isEmpty();
	void Print();
};

template<typename T>
Queue<T>::Queue()
{
	data = NULL;
	next = NULL;
	front = NULL;
	rear = NULL;
}

template<typename T>
void Queue<T>::Enqueue(T data)
{
	Queue* temp = new Queue();
	temp->data = data;
	temp->next = NULL;
	if (front == NULL && rear == NULL)
	{
		front = rear = temp;
	}
	rear->next = temp;
	rear = temp;
}

template<typename T>
void Queue<T>::Dequeue()
{
	Queue* temp = front;
	if (front == NULL)
	{
		printf("Front is empty! \n");
		return;
	}
	if (front == rear)
	{
		front = rear = NULL;
	}
	else
	{
		front = front->next;
	}
	delete[] temp;
}

template<typename T>
T Queue<T>::Front()
{
	return front->data;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	if (front == NULL)
	{
		return true;
	}
	else
	{ 
		return false;
	}
}

template<typename T>
void Queue<T>::Print()
{
	Queue* temp = front;
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
	Queue<char> info;

	for (char i = 'a'; i <= 'z'; i++)
	{
		info.Enqueue(i);
	}
	info.Print();
	cout << info.Front() << endl;;

	for (size_t i = 0; i < 13; i++)
	{
		info.Dequeue();
	}
	info.Print();

	return 0;
}