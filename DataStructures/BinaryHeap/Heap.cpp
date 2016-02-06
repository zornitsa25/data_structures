#include "Heap.h"

void BinaryHeap::insert(int data)
{
	if (data >= 0)
	{
		heap.push_back(data);
		heapUp(heap.size() - 1);
	}
}

void BinaryHeap::removeMin()
{
	if (heap.size() == 0)
	{
		printf("Heap is empty!\n");
		return;
	}
	heap[0] = heap.at(heap.size() - 1);
	heap.pop_back();
	heapDown(0);
}

int BinaryHeap::getMin()
{
	if (heap.size() == 0)
	{
		return -1;
	}
	return heap.front();
}

void BinaryHeap::printHeap()
{
	vector<int>::iterator iter;
	for (iter = heap.begin(); iter != heap.end(); ++iter)
	{
		cout << *iter << " ";
	}
	printf("\n");
}

int BinaryHeap::getSize() const
{
	return heap.size();
}

int BinaryHeap::left(int parent)
{
	int left = 2 * parent + 1;
	if (left >= 0 && left < heap.size())
	{
		return left;
	}
	return -1;
}

int BinaryHeap::right(int parent)
{
	int right = 2 * parent + 2;
	if (right >= 0 && right < heap.size())
	{
		return right;
	}
	return -1;
}

int BinaryHeap::parent(int child)
{
	if (child > 0 && child < heap.size())
	{
		return (child - 1) / 2;
	}
	return -1;
}

void BinaryHeap::heapUp(int index)
{
	if (index >= 0 && parent(index) >= 0 && heap[parent(index)] > heap[index])
	{
		// swap
		int temp = heap[parent(index)];
		heap[parent(index)] = heap[index];
		heap[index] = temp;
		// up
		heapUp(parent(index));
	}
}

void BinaryHeap::heapDown(int index)
{
	int left_child = left(index);
	int right_child = right(index);

	if (left_child >= 0 && right_child >= 0 && heap[left_child] > heap[right_child])
	{
		left_child = right_child;
	}
	if (heap[index] > heap[left_child])
	{
		int temp = heap[index];
		heap[index] = heap[left_child];
		heap[left_child] = temp;
		heapDown(left_child);
	}
}