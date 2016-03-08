#include "Allocator.h"

Allocator::Allocator()
{
	block = NULL;
	currPtr = NULL;
	startPtr = NULL;
	remainSpace = 0;
	found = false;
	allocate();
}

Allocator::~Allocator()
{
	if (block)
	{
		delete[] block;
	}
	block = NULL;
}

///
/// allocates the array that is going to be used as a memory block
///

void Allocator::allocate()
{
	try
	{
		block = new int64_t[SIZE];
		if (!block)
		{
			throw 1;
		}
		for (int i = 0; i < SIZE; i++)
		{
			*(block + i) = 0;
		}
		startPtr = block;
		currPtr = block;
		remainSpace = maxSize;
	}
	catch (int)
	{
		printf("Cannot allocate memory!\n");
		throw;
	}
}

int64_t Allocator::roundSize(int64_t size) const
{
	int64_t round = size >> 3;
	return !isDivisibleByEight(size) ? (round + 1) : round;
}

///
/// if the size is an odd number it returns true
/// and false otherwise
///

bool Allocator::isAllocated(const int64_t size) const
{
	return (size & 1);
}

bool Allocator::isDivisibleByEight(int64_t size) const
{
	if (size > 0)
	{
		if ((size & 1) || ((size >> 1) & 1) || ((size >> 2) & 1))
			return false;
	}
	return true;
}

bool Allocator::isEqualSize(int64_t* ptr, const int64_t rounded)
{
	return (!isAllocated(*ptr) && (*ptr == rounded));
}

bool Allocator::isGreaterSize(int64_t* ptr, const int64_t rounded)
{
	return (!isAllocated(*ptr) && (*ptr > rounded));
}

bool Allocator::isFull(const int64_t remaining, const int64_t size)
{
	return !(remaining >= (size + 16)); /// 16 = 2 * sizeof(int64_t) for the two boundaries
}

bool Allocator::isValidPointer(int64_t* ptr)
{
	int64_t start = *ptr;
	ptr = ptr + (start >> 3) + 1;
	return (*ptr == start);
}

void Allocator::print() const
{
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", *(block + i));
	}
	printf("\n");
}

///
/// changes both boundaries to 'allocated'
///

void Allocator::setFreeBoundaries(int64_t* start, const int64_t size)
{
	*start = size + 1;
	start = start + (size >> 3) + 1;
	*start = size + 1;
}

///
/// changes both boundaries to 'free'
///

void Allocator::setAllocBoundaries(int64_t* free)
{
	*free = *free - 1;
	free = free + ((*free) >> 3) + 1;
	*free = (*free) - 1;
}

///
/// changes middle boundaries to 'free'
///

void Allocator::setAllocMiddleBoundaries(int64_t* free, const int64_t round_middle)
{
	free = free + round_middle + 1;
	*free = 0;
	free = free + 1;
	*free = 0;
	free = free - round_middle - 2;
}

///
/// values remain the same - 'free'
///

void Allocator::setEqualBoundaries(int64_t* start, const int64_t size)
{
	*start = size;
	start = start + (size >> 3) + 1;
	*start = size;
}

///
/// searches for a free block with the same size
/// and allocates it
/// if there isn't such block calls firstReMalloc function
///

void* Allocator::bestReMalloc(const int64_t rounded)
{
	int64_t* start = startPtr; /// start pointer
	int64_t* end = startPtr; /// end pointer
	end = end + (SIZE - 1);

	found = false;

	while (start != end)
	{
		int64_t* return_ptr = start;
		if (isEqualSize(start, rounded))
		{
			found = true;
			setFreeBoundaries(start, rounded);
			return (return_ptr + 1);
		}
		else
		{
			start = start + ((*start) >> 3) + 2;
			if (start - 1 == end)
				break;
		}
	}
	if (!found)
	{
		return firstReMalloc(rounded);
	}
	return NULL;
}

///
/// tries to find and fit the first free block
/// which has bigger size than the wanted one
///

void* Allocator::firstReMalloc(const int64_t rounded)
{
	int64_t* start = startPtr; /// start pointer
	int64_t* end = startPtr; /// end pointer
	end = end + (SIZE - 1);

	do
	{
		int64_t* return_ptr = start;
		if (isGreaterSize(start, rounded))
		{			
			found = true;
			int64_t old_size = *start;
			if (old_size < rounded + 16)
			{
				setFreeBoundaries(start, old_size);
				return NULL;
			}
			int64_t rest_size = old_size - rounded - 16;
			
			setFreeBoundaries(start, rounded);
			start = start + (rounded >> 3) + 2;
			setEqualBoundaries(start, rest_size);

			return (return_ptr + 1);
		}
		else
		{
			start = start + ((*start) >> 3) + 2;
			if (start - 1 == end)
				break;
		}
	} while (start != end);

	if (!found) /// there isn't a free block
	{
		return NULL;
	}	
}

///
/// it continues to allocate memory until the array is full
/// then tries to find a free block (starting from the beginning)
/// if there is a free block -> returns it
/// if there isn't -> returns null pointer
///

void* Allocator::Malloc(int64_t size)
{
	int64_t* return_ptr = currPtr;
	int64_t rounded_bytes = roundSize(size);

	if (isFull(remainSpace, size))
	{
		int64_t bound = rounded_bytes << 3;
		return (int64_t*)bestReMalloc(bound);
	}
	*currPtr = (rounded_bytes << 3) + 1; /// start
	currPtr = currPtr + (rounded_bytes) + 1; /// end
	*currPtr = (rounded_bytes << 3) + 1;

	currPtr = currPtr + 1;
	remainSpace = remainSpace - ((rounded_bytes << 3) + (sizeof(int64_t) << 1)); /// remaining space

	return (return_ptr + 1);
}

///
/// checks if the left block is allocated
/// or the pointer is at the beginning of the memory block
/// then it merges both (middle and right) blocks
///

bool Allocator::mergeRight(int64_t* right, const int64_t middle, const int64_t round_middle)
{
	int64_t right_bound = (*right);
	int64_t right_size = right_bound + 16; /// 16 = 2*sizeof(int64_t)

	right = right - round_middle - 2;
	if (right != startPtr) /// not start
	{
		right = right - 1;
		if (isAllocated(*right)) /// if left side is allocated
		{
			right = right + 1;
			setAllocMiddleBoundaries(right, round_middle);
			int64_t all_bound = middle + right_size;
			setEqualBoundaries(right, all_bound);
		}
		return false;
	}
	else /// start (left side)
	{
		setAllocMiddleBoundaries(right, round_middle);

		int64_t all_bound = middle + right_size;
		setEqualBoundaries(right, all_bound);
		return true;
	}	
}

///
/// checks if the left block is allocated
/// if is not, then it merges both (left and middle) blocks
///

void Allocator::mergeLeft(int64_t* left, const int64_t middle)
{
	left = left - 1;
	if (isAllocated(*left))
	{
		return;
	}
	else
	{
		int64_t left_bound = (*left);
		int64_t left_size = left_bound + 16;
		int64_t all_bound = middle + left_size;

		left = left - (left_bound >> 3) - 1;
		setAllocMiddleBoundaries(left, (left_bound >> 3));
		setEqualBoundaries(left, all_bound);
	}
}

///
/// first, it tries to merge the right side
/// then it merges the left side
///

void Allocator::mergeBlocks(int64_t* free)
{
	if (isAllocated(*free))
		return;

	int64_t* left = free;
	int64_t round_middle = roundSize((*free));
	int64_t middle = (*free);

	/// right side
	free = free + round_middle + 2;
	if (!isAllocated(*free) && (*free != 0)) 
	{				
		if (mergeRight(free, middle, round_middle))
		{
			return;
		}
	}
	/// left side
	if (left == startPtr)
	{
		return;
	}
	mergeLeft(left, middle);
}

///
/// set both boundaries to 'free'
/// if they are free already or the pointer isn't the real one
/// then it throws an exception
///

void Allocator::Free(void* ptrBlock)
{
	int64_t* ptrFree = (int64_t*)ptrBlock;
	ptrFree = (ptrFree - 1);
	try
	{
		if (!isValidPointer(ptrFree))
		{
			throw 1;
		}
		if (isAllocated(*ptrFree))
		{
			setAllocBoundaries(ptrFree);
			mergeBlocks(ptrFree);
			return;
		}
		throw 2;
	}
	catch (...)
	{
		printf("Invalid pointer/Cannot free memory!\n");
		throw;
	}
}