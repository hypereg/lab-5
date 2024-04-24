#pragma once

#include "lib.h"

class Point
{
public:
	static int licznik;
	int J, I;
	struct color mycolor;
	Point(int j, int i, unsigned char red, unsigned char green, unsigned char blue);
	~Point();

	bool operator == (const Point& p);

	friend ostream& operator << (ostream& s, Point& p);
};
