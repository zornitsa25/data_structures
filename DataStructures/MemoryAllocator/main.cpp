// Zornitsa Chopova 45043

#include <iostream>
#include "Allocator.h"
#include <vector>
using namespace std;

int main()
{
	Allocator a;
	vector<void*> mem;

	for (int c = 0; c < 10000; ++c) {
		mem.push_back(a.Malloc(c));
	}

	for (int c = 0; c < 10000; ++c) {
		if ((intptr_t)mem[c] % 8 != 0) {
			cout << "Not aligned block " << mem[c] << endl;
		}
		cout << mem[c] << endl;
		a.Free(mem[c]);
	}

/*
	int* ptr = (int*)a.Malloc(100 * sizeof(int));
	int* ptr2 = (int*)a.Malloc(200 * sizeof(int));
	ptr[0] = ptr2[0] = 100;

	std::cout << "ptr[0] = " << ptr[0] << "\n";
	std::cout << "ptr2[0] = " << ptr2[0] << "\n";
	a.Free(ptr);
	a.Free(ptr2);
*/
	return 0;
}