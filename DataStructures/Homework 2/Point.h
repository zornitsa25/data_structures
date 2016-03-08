#pragma once

#include <iostream>
using namespace std;

class Point
{
public:
	Point();
	Point(int x, int y);
	Point(const Point& other);
	Point& operator=(const Point& other);
	~Point();

	friend ostream& operator<<(std::ostream& os, const Point& obj)
	{
		os << "(" << obj.x << ", " << obj.y << ")" << "";
		return os;
	}

	int getX() const;
	int getY() const;

private:
	int x, y;
};