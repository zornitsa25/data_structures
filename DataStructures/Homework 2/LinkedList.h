#pragma once

#include "Node.h"
#include "Iterator.h"
#include <iostream>

template<typename T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);
	~LinkedList();

public:
	void Push_Front(const T&);
	void Pop_Front();
	void Push_Back(const T&);
	void Pop_Back();

	T& Front();
	T& Back();

	void InsertAfter(int, const T&);
	void InsertBefore(int, const T&);
	void RemoveAt(int);
	T& GetAt(int) const;

	bool isEmpty() const;
	int getSize() const;
	void Print() const;

	void InsertionSort();
	Iterator<T> IteratorBegin();
	void DeleteAll();

	bool operator>(const LinkedList&);

private:
	void Init();
	void Copy(const LinkedList&);

	Node<T>* first;
	Node<T>* last;
	int m_size;
};

// initializing the empty list  
template<typename T>
void LinkedList<T>::Init()
{
	this->first = NULL;
	this->last = NULL;
	this->m_size = 0;
}

// removes all elements from the list
template<typename T>
void LinkedList<T>::DeleteAll()
{
	Node<T>* cur = first;
	Node<T>* prev = first;

	while (cur)
	{
		prev = cur;
		cur = cur->next;
		delete prev;
	}
	Init();
}

template<typename T>
LinkedList<T>::LinkedList()
{
	Init();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	Init();
	Copy(other);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this != &other)
	{
		DeleteAll();
		Copy(other);
	}
	return *this;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	DeleteAll();
}

template<typename T>
void LinkedList<T>::Copy(const LinkedList<T>& other)
{
	Node<T>* otherfront = other.first;
	while (otherfront != NULL)
	{
		Push_Back(otherfront->data);
		otherfront = otherfront->next;
	}

	this->m_size = other.m_size;

	//Node<T>* cur = other.first;
	//Node<T>* end = NULL;

	//while (cur)
	//{
	//	Node<T>* new_node = new Node<T>();
	//	new_node->data = cur->data;

	//	if (!first)
	//	{
	//		first = new_node;
	//		end = first;
	//	}
	//	else 
	//	{
	//		end->next = new_node;
	//		end = new_node;
	//	}
	//	cur = cur->next;
	//}
}

template<typename T>
void LinkedList<T>::Push_Front(const T& data)
{
	Node<T>* new_node = new Node<T>();

	if (new_node)
	{
		new_node->data = data;
		new_node->next = first;
		if (this->isEmpty())
		{
			last = new_node;
		}

		first = new_node;
		++m_size;
	}
}

template<typename T>
void LinkedList<T>::Pop_Front()
{
	if (!this->isEmpty())
	{
		Node<T>* temp = first;
		first = first->next;

		// if this is the last element in the list
		if (first == NULL)
		{
			last = NULL;
		}

		delete temp;
		--m_size;
	}
}

template<typename T>
void LinkedList<T>::Push_Back(const T& data)
{
	Node<T>* new_node = new Node<T>();

	if (new_node)
	{
		new_node->data = data;
		if (this->isEmpty())
		{
			first = new_node;
			last = new_node;
		}
		else
		{
			last->next = new_node;
			last = new_node;
		}
		++m_size;
	}
}

template<typename T>
void LinkedList<T>::Pop_Back()
{
	if (this->isEmpty())
		std::cout << "List is empty!\n";
	else if (m_size == 1)
	{
		delete last;
		first = last = NULL;
	}
	else
	{
		Node<T>* temp = first;
		while (temp->next->next != NULL) 
		{
			temp = temp->next;
		}
		last = temp;
		delete last->next;
		last->next = NULL;
		--m_size;
	}
}

template<typename T>
T& LinkedList<T>::Front()
{
	if (isEmpty())
	{
		std::cout << "List is empty. Cannot access the first element!\n";
		throw;
	}
	return first->data;
}

template<typename T>
T& LinkedList<T>::Back()
{
	if (isEmpty())
	{
		std::cout << "List is empty. Cannot access the last element!\n";
		throw;
	}
	return last->data;
}

template<typename T>
void LinkedList<T>::InsertAfter(int index, const T& data)
{
	if (index < 0 || index >= m_size)
	{
		return;
	}
	else
	{
		Node<T>* p = first;
		for (int i = 0; i < index; i++)
		{
			p = p->next;
		}
		if (p)
		{
			Node<T>* temp = new Node<T>();
			temp->data = data;
			temp->next = p->next;
			if (!temp)
			{
				return;
			}
			p->next = temp;

			if (p == last)
			{
				last = temp;
			}
			++m_size;
		}
	}
}

template<typename T>
void LinkedList<T>::InsertBefore(int index, const T& data)
{
	if (index == 0)
	{
		return Push_Front(data);
	}
	else
	{
		InsertAfter(index - 1, data);
	}
}

template<typename T>
void LinkedList<T>::RemoveAt(int index)
{
	if (index == 0)
	{
		Pop_Front();
	}
	else
	{
		Node<T>* p = first;
		for (int i = 0; i < index - 1; i++)
		{
			p = p->next;
		}
		if (p)
		{
			Node<T>* temp = p->next;

			if (index == m_size - 1)
			{
				last = p;
			}
			p->next = temp->next;
			delete temp;
			--m_size;
		}
	}
}

template<typename T>
T& LinkedList<T>::GetAt(int index) const
{
	Node<T>* p = first;
	for (int i = 0; i < index; i++)
	{
		p = p->next;
	}

	if (p)
		return p->data;
}

template<typename T>
void LinkedList<T>::Print() const
{
	if (!isEmpty())
	{
		Node<T>* temp = first;
		while (temp)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
	}
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return m_size <= 0;
}

template<typename T>
int LinkedList<T>::getSize() const
{
	return this->m_size;
}

template<typename T>
Iterator<T> LinkedList<T>::IteratorBegin()
{
	return Iterator<T>(this->first);
}

template<typename T>
void LinkedList<T>::InsertionSort()
{
	Node<T>* current = first;
	Node<T>* tail = NULL;
	while (current != NULL && tail != first)
	{
		Node<T>* nextptr;
		for (nextptr = current; nextptr->next != tail; nextptr = nextptr->next)
		{
			if (nextptr->data > nextptr->next->data)
			{
				T temp = nextptr->data;
				nextptr->data = nextptr->next->data;
				nextptr->next->data = temp;
			}
		}
		tail = nextptr;
		current = first;
	}
}

template<typename T>
bool LinkedList<T>::operator>(const LinkedList& other)
{
	return m_size > other.m_size;
}
