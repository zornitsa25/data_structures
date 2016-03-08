#include "Matrix.h"

Matrix::Matrix()
{
	this->rows = 0;
	this->cols = 0;
	this->matrix = NULL;
}

Matrix::Matrix(int rows, int cols)
{
	setRows(rows);
	setCols(cols);

	matrix = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new char[cols];
	}
}

void Matrix::InitMatrix(int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin >> matrix[i][j];
		}
	}
}

char** Matrix::copy(const Matrix& other)
{
	char** lab = new char*[other.rows];
	for (int i = 0; i < other.rows; i++)
	{
		lab[i] = new char[other.cols];
	}

	for (int i = 0; i < other.rows; i++)
	{
		for (int j = 0; j < other.cols; j++)
		{
			lab[i][j] = other.matrix[i][j];
		}
	}
	return lab;
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void Matrix::printMatrix()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

bool Matrix::canPass(int rows, int cols, const Point pos)
{
	if (pos.getX() < 0 || pos.getY() < 0 || pos.getX() >= rows || pos.getY() >= cols)
	{
		return false;
	}
	return matrix[pos.getX()][pos.getY()] == '.';
}

void Matrix::BFS(Point start, int rows, int cols, LinkedList<Point>& path)
{
	if (matrix[start.getX()][start.getY()] == '#')
	{
		cout << "The position is invalid!\n";
		return;
	}

	int dr[] = { 0, -1, 0, 1 };
	int dc[] = { -1, 0, 1, 0 };
	Queue<Point> queue;

	queue.Enqueue(start);
	matrix[start.getX()][start.getY()] = '?';

	cout << "Starting from point: ";
	cout << "(" << start.getX() << ", " << start.getY() << ")" << " : " << endl;

	while (!queue.isEmpty())
	{
		start = queue.Front();
		queue.Dequeue();

		for (int d = 0; d < 4; d++)
		{
			Point nextPos(start.getX() + dr[d], start.getY() + dc[d]);
			
			if (canPass(rows, cols, nextPos))
			{
				path.Push_Back(nextPos);
				queue.Enqueue(nextPos);

				matrix[nextPos.getX()][nextPos.getY()] = '?';			
			}
		}
	}
}

void Matrix::FindPaths(int row, int col, Point& end, Point& start, LinkedList<Point>& one, char** lab, LinkedList<LinkedList<Point>>& paths)
{	
	int dr[] = { 0, -1, 0, 1 };
	int dc[] = { -1, 0, 1, 0 };

	if ((row == end.getX()) && (col == end.getY()))
	{
		one.Push_Back(end);
		paths.Push_Back(one);
		one.DeleteAll();
		one.Push_Back(start);
		return;
	}
	if (lab[row][col] != '.')
	{
		return;
	}
	Point cur(row, col);
	one.Push_Back(cur);

	lab[row][col] = 'p';

	for (int i = 0; i < 4; i++)
	{
		int x = row + dr[i];
		int y = col + dc[i];
		Point p(x, y);
		if (!((x < 0) || (y < 0) || (x >= rows) || (y >= cols)))
		{
			FindPaths(x, y, end, start, one, lab, paths);
		}
	}
	lab[row][col] = '.';
}

void Matrix::PrintAllPaths(LinkedList<Point> path, LinkedList<LinkedList<Point>> paths, LinkedList<LinkedList<LinkedList<Point>>> allPaths)
{
	for (Iterator<LinkedList<LinkedList<Point>>> k = allPaths.IteratorBegin(); k; ++k)
	{
		for (Iterator<LinkedList<Point>> i = (*k).IteratorBegin(); i; ++i)
		{
			for (Iterator<Point> j = (*i).IteratorBegin(); j; ++j)
			{
				cout << (*j) << " ";
			}
			cout << endl;
		}
	}
}

void Matrix::PrintPath(LinkedList<Point> path)
{
	for (Iterator<Point> i = path.IteratorBegin(); i; ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

void Matrix::setRows(int rows)
{
	this->rows = rows;
}

void Matrix::setCols(int cols)
{
	this->cols = cols;
}

int Matrix::getRows() const
{
	return this->rows;
}

int Matrix::getCols() const
{
	return this->cols;
}