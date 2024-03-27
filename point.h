#pragma once

#include "lib.h"

class Point
{
public:
	int J, I;
	struct color mycolor;
	Point(int j, int i, unsigned char red, unsigned char green, unsigned char blue);
	~Point();
};
