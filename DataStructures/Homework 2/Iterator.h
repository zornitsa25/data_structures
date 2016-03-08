#pragma once

#include "Node.h"

template<typename T>
class Iterator
{
private:
	Node<T>* start;
	Node<T>* cur;

public:
	Iterator(Node<T>* start)
	{
		this->start = this->cur = start;
	}
	Iterator(const Iterator& obj)
	{
		this->start = obj.start;
	}
	Iterator& operator=(const Iterator& obj)
	{
		this->cur = obj.cur;
		return *this;
	}
	T& operator*() const
	{
		return cur->data;
	}
	bool operator==(const Iterator& it)
	{
		return cur == it.cur;
	}
	bool operator!=(const Iterator& it)
	{
		return cur != it.cur;
	}
	operator bool()
	{
		return this->cur != NULL;
	}
	Iterator& operator++()
	{
		if (cur)
		{
			cur = cur->next;
		}
		return *this;
	}
	T* operator->()
	{
		return &(cur->data);
	}
};