#pragma once

#include <iostream> 
#include "point.h"

	using namespace std;

Point::Point(int j, int i, unsigned char red, unsigned char green, unsigned char blue) {
	J = i;
	I = i;

	mycolor.r = red;
	mycolor.g = green;
	mycolor.b = blue;
}

Point::~Point() {
	cout << "Kasuje point" << endl;
}