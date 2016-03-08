#pragma once

#include "Point.h"
#include "Queue.h"
#include "LinkedList.h"

class Matrix
{
public:
	Matrix();
	Matrix(int rows, int cols);
	~Matrix();

	void InitMatrix(int rows, int cols);
	void printMatrix();
	bool canPass(int row, int col, const Point pos);
	void BFS(Point s, int rows, int cols, LinkedList<Point>& path);
	void FindPaths(int row, int col, Point& end, Point& start, LinkedList<Point>& one, char** lab, LinkedList<LinkedList<Point>>& paths);
	static char** copy(const Matrix&);

public:
	static void PrintAllPaths(LinkedList<Point> path, LinkedList<LinkedList<Point>> paths, LinkedList<LinkedList<LinkedList<Point>>> allPaths);
	static void PrintPath(LinkedList<Point> path);

	void setRows(int);
	void setCols(int);

	int getRows() const;
	int getCols() const;

private:
	int rows, cols;
	char** matrix;
};