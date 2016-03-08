#pragma once
#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include <stdint.h>
#include <iostream>

class Allocator
{
public:
	Allocator();
	~Allocator();

	void* Malloc(int64_t size);
	void Free(void* ptrBlock);
	
private:
	Allocator(const Allocator&);
	Allocator& operator=(const Allocator&);
	void allocate();
	void print() const;

private:
	void mergeLeft(int64_t* left, const int64_t middle);
	bool mergeRight(int64_t* right, const int64_t middle, const int64_t round_middle);
	void mergeBlocks(int64_t* free);

	void* bestReMalloc(const int64_t size);
	void* firstReMalloc(const int64_t size);
	int64_t roundSize(int64_t size) const;

	void setFreeBoundaries(int64_t* start, const int64_t size);
	void setAllocBoundaries(int64_t* free);
	void setAllocMiddleBoundaries(int64_t* free, const int64_t round_middle);
	void setEqualBoundaries(int64_t* start, const int64_t size);

	bool isDivisibleByEight(int64_t size) const;
	bool isAllocated(const int64_t size) const;
	bool isFull(const int64_t remaining, const int64_t size);
	bool isEqualSize(int64_t* ptr, const int64_t rounded);
	bool isGreaterSize(int64_t* ptr, const int64_t rounded);
	bool isValidPointer(int64_t* ptr);

private:
	int64_t* block;
	int64_t* currPtr;
	int64_t* startPtr;
	int64_t remainSpace;

	const int64_t SIZE = (1 << 20) * 20; /// 10 mb = 10485760 bytes
	const int64_t maxSize = sizeof(int64_t) * SIZE;
	bool found;
};

#endif