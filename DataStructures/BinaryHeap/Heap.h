#pragma once
#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap
{
public:
	BinaryHeap(){};

	void insert(int data);
	void removeMin();
	int getMin();
	void printHeap();
	int getSize() const;

private:
	vector<int> heap;

	int left(int parent);
	int right(int parent);
	int parent(int child);

	void heapUp(int index);
	void heapDown(int index);
};

#endif