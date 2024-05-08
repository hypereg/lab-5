#pragma once

#include <iostream>
#include <ostream>
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

	struct color** getTab() {
		return tab;
	}

	int getDx() {
		return  dX;
	}

	int getDy() {
		return dY;
	}

	class Zagniezdzona {
	public:
		int sizex; int sizey;
		struct color** array;
		Zagniezdzona(PPMImage& o){
			sizex = o.dX;
			sizey = o.dY;
			array = o.tab;
		}
	};


	void saveFile(string filename, int fraktal = 1);

	friend ostream& operator << (ostream& s, PPMImage& ppm);
	friend istream& operator >> (ostream& s, PPMImage& ppm);

	PPMImage & operator =(const PPMImage &);
	PPMImage & operator +=(const Point &);

	void saveFile(ostream& plik, int fractal = 0);
	void loadFile(istream& plik);


	void saveFileP3(string filename);
	void loadFile(string filename);
	void white_board();
	void addPoint(const Point *p);
};
