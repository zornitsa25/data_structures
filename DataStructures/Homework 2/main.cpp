// Zornitsa Chopova [45043]

#include <iostream>
using namespace std;

#include "Queue.h"
#include "LinkedList.h"
#include "Iterator.h"
#include "Point.h"
#include "Matrix.h"

bool isValid(int rows, int cols);
bool validCoord(int x, int y);

int main()
{
	int rows, cols;
	cout << "rows: ";
	cin >> rows;
	cout << "cols: ";
	cin >> cols;

	if (!isValid(rows, cols))
	{
		printf("Invalid rows/cols!\n");
		return 1;
	}

	cout << "Enter the labyrinth: \n";
	Matrix lab(rows, cols);
	lab.InitMatrix(rows, cols);

	int x, y;
	cout << "Enter start position: \n";
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;

	if (!validCoord(x, y))
	{
		printf("Invalid coordinates!\n");
		return 1;
	}
	Point start(x, y);

	LinkedList<Point> path; // gets all reachable points
	LinkedList<LinkedList<Point>> paths;
	LinkedList<LinkedList<LinkedList<Point>>> allPaths;

	char** copy = Matrix::copy(lab); // original matrix will be changed to visited
	lab.BFS(start, rows, cols, path);

	Matrix::PrintPath(path);
	for (Iterator<Point> i = path.IteratorBegin(); i; ++i)
	{
		LinkedList<Point> currentPath;
		Point cur_end = *i;
		int row = start.getX();
		int col = start.getY();
		lab.FindPaths(row, col, cur_end, start, currentPath, copy, paths);
		paths.InsertionSort();
		allPaths.Push_Back(paths);
		paths.DeleteAll();
	}

	Matrix::PrintAllPaths(path,paths,allPaths);

	for (int i = 0; i < rows; i++)
	{
		delete[] copy[i];
	}
	delete[] copy;

	return 0;
}

bool isValid(int rows, int cols)
{
	if (rows <= 0 || cols <= 0)
		return false;
	return true;
}

bool validCoord(int x, int y)
{
	if (x < 0 || y < 0)
		return false;
	return true;
}