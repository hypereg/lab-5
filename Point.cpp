#pragma once

#include <iostream> 
#include "point.h"
#include "PPMImage.h"
using namespace std;

Point::Point(int j, int i, unsigned char red, unsigned char green, unsigned char blue): J(j), I(i), mycolor({ red, green, blue }) {
	licznik++;
}

Point::~Point() {
	cout << "Kasuje point" << endl;
	licznik--;
}

bool Point::operator == (const Point& p) {
	return((this->I == p.I)
		&& (this->J == p.J)
		&& (this->mycolor.r == p.mycolor.r)
		&& (this->mycolor.g == p.mycolor.g)
		&& (this->mycolor.b == p.mycolor.b)
		);
}


ostream& operator <<(ostream& s, Point& p) {
	s << endl << p.I << " " << p.J << endl;
	return s;
 }

int Point::licznik = 0;