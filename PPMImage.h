#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "lib.h"
#include "point.h"
using namespace std;

class PPMImage {
private:
	int dX, dY;
	struct color** tab;
	struct color* tab1D;

	void allocate();
	void clear();
	string convert(unsigned char c);
public:
	const int pointSize = 20;

	Point* k = NULL;
	PPMImage(int x, int y);
	PPMImage();
	~PPMImage();

	void saveFile(string filename, int fraktal = 1);
	void saveFileP3(string filename);
	void loadFile(string filename);

	void white_board();

	void addPoint(const Point *p);
};
