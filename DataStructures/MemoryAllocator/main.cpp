// Zornitsa Chopova

#include <iostream>
#include "Allocator.h"
#include <vector>
using namespace std;

int main()
{
	Allocator a;

	int* ptr = (int*)a.Malloc(100 * sizeof(int));
	int* ptr2 = (int*)a.Malloc(200 * sizeof(int));
	ptr[0] = ptr2[0] = 100;

	std::cout << "ptr[0] = " << ptr[0] << "\n";
	std::cout << "ptr2[0] = " << ptr2[0] << "\n";
	a.Free(ptr);
	a.Free(ptr2);

	return 0;
}