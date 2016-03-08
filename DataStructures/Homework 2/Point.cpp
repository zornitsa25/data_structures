#include "Point.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point& other)
{
	this->x = other.x;
	this->y = other.y;
}

Point& Point::operator=(const Point& other)
{
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return *this;
}

Point::~Point()
{
}

int Point::getX() const
{
	return this->x;
}

int Point::getY() const
{
	return this->y;
}