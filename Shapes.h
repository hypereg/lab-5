#pragma once

#include <iostream>
#include "lib.h"

using namespace std;

class Shape {
protected:
	int I, J; // kordynatory
	int h, w; // wysokosc i szerokosc
	color fg; // kolor konturu
public:
	virtual void Rysuj(color** tab) = 0;
	Shape(int x, int y) : h(x), w(y) {};
	Shape() { cout << "Shape"; };
	void set_JI(int j, int i) { J = j; I = i; }
	void set_fg(struct color tmp) { fg = tmp; }

};

class Line : public Shape {
private:
	string rodzaj;
public:
	Line() {};
	Line(int x, int y, int i, int j, struct color c) : Shape(x, y) {
		I = i; J = j; fg = c;
		cout << h << " " << w;
		if (h == 1 && w > 1)
			rodzaj = "pozioma";
		else if (h > 1 && w == 1)
			rodzaj = "pionowa";
		else if (h == 1 && w == 1)
			rodzaj = "punkt";
		else if (h == w)
			rodzaj = "ukosna";
		else
			rodzaj = "nie umiem tego namalowac";
		cout << rodzaj;
	}
	int lewy_skos = 0;

	void Rysuj(color** tab) override {
		if (rodzaj == "punkt")
			tab[I][J] = fg;
		if (rodzaj == "pozioma")
			for (int i = I; i < I + w; i++)
				tab[J][i] = fg;
		if (rodzaj == "pionowa")
			for (int j = J; j < J + h; j++)
				tab[j][I] = fg;
		if (rodzaj == "ukosna")
			for (int k = 0; k < w; k++)
				if (lewy_skos)
					tab[J + h - k - 1][I + k] = fg; // w prawo i do gory
				else
					tab[J + k][I + k] = fg;  // w prawo i w dol
	};

};

class Filling {
protected:
	struct color bg;
	struct color curr;
	vector<pair<int, int>> points;
public:

	Filling() { cout << "@@@@"; };
	PPMImage::Zagniezdzona* ziomek;

	void PaintPixel(int y, int x) {
		if (x >= 0 && y >= 0 && x < ziomek->sizex && y < ziomek->sizey)
			if (ziomek->array[y][x] == curr) {
				ziomek->array[y][x] = bg;
				PaintPixel(y - 1, x);
				PaintPixel(y, x - 1);
				PaintPixel(y + 1, x);
				PaintPixel(y, x + 1);
			}
	}
	void Fill(int x, int y, PPMImage* obraz) {
		ziomek = new PPMImage::Zagniezdzona(*obraz);
		curr = ziomek->array[y][x];
		points.push_back(pair<int, int>(y, x));
		do {
			pair<int, int> pixel = points.back();
			points.pop_back();
			int _y = pixel.first;
			int _x = pixel.second;

			if (_x >= 0 == _y >= 0 && _x < ziomek->sizex && _y < ziomek->sizey) {
				if (ziomek->array[_y][_x] == curr) {
					ziomek->array[_y][_x] = bg;
					points.push_back(pair<int, int>(_y, _x + 1));
					points.push_back(pair<int, int>(_y, _x - 1));
					points.push_back(pair<int, int>(_y + 1, _x));
					points.push_back(pair<int, int>(_y - 1, _x));
				}
			}
		} while (!points.empty());

		//PaintPixel(y, x);
		delete ziomek;

	};

	void setBG(struct color _bg) {
		bg = _bg;
	}
};

class Figure : public Shape, public Filling {
protected:
	int fillx;
	int filly;
	vector<Line> boki;
public:
	int cos_tam;
	Figure(int size1, int size2) : cos_tam(0), Shape(size1, size2), Filling() {};
	Figure() { cout << "figura"; };
	virtual void Rysuj(color** tab) {
		Draw_Circuit(tab);

	}

	void set_bg(color _bg) {
		cout << "\nBg";
		bg = _bg;
		set_center();
	}
	void Fill(struct color c, PPMImage* obrazek) {
		set_bg(c);
		Filling::Fill(filly, fillx, obrazek);
	}

private:
	virtual void Draw_Circuit(color** tab) = 0;
	virtual void set_center() = 0;
};



class Rectangle : public Figure {
public:
	Rectangle(int size1, int size2) : Figure(size1, size2) {};
	Rectangle() {};
	void Rysuj(color** tab) override {
		Figure::Rysuj(tab);
		cout << "\nRysuje prostokat\n";
		for (int i = I; i < I + h; i++) {
			for (int j = J; j < J + w; j++) {
				if (i == I || i == I + h - 1 || j == J || j == J + w - 1) {
					tab[i][j] = fg;
				}
				else {
					tab[i][j] = bg;
				}
			}
		}
	}
private:
	void set_center() override {
		fillx = I + w / 2;
		filly = J + h / 2;
	}
	void Draw_Circuit(color** tab) override {

		cout << "\nObwod prostokata\n";
		// Implementacja rysowania konturu prostok¹ta
		Line l1(1, w, I, J, fg);
		Line l2(h, 1, I, J, fg);
		Line l3(1, w, I, J + h - 1, fg);
		Line l4(h, 1, I + w - 1, J, fg);
		boki.push_back(l1);
		boki.push_back(l2);
		boki.push_back(l3);
		boki.push_back(l4);
	
		for (int i = 0; i < boki.size(); i++)
			boki[i].Rysuj(tab);

	}
};

class Square : public Rectangle {
public:
	Square(int size) : Rectangle(size, size) { cout << " SQUARE\n "; };


};

class Triangle : public Figure {
public:
	Line boki[4];

	Triangle(int size1, int size2) : Figure(size1, size2) {};
	Triangle();
	void Rysuj(color** tab) override {
		Figure::Rysuj(tab);
		cout << "\nRysuje prostokat\n";
		int x1 = I;
		int y1 = J;
		int x2 = I + h - 1;
		int y2 = J;
		int x3 = I + h / 2;
		int y3 = J + w - 1;

		Line l1(x2 - x1 + 1, y2 - y1 + 1, x1, y1, fg);
		Line l2(h, 1, x2, y2, fg);
		Line l3(x3 - x1 + 1, y3 - y1 + 1, x1, y1, fg);

		l1.Rysuj(tab);
		l2.Rysuj(tab);
		l3.Rysuj(tab);
	}
private:
	void Draw_Circuit(color** tab) override {

		cout << "\nObwod trojkata\n";
		Line l1(1, w, I, J + h - 1, fg);
		Line l2(h, 1, I, J, fg);
		Line l3(h, w, I, J, fg);
		boki[0] = l1;
		boki[1] = l2;
		boki[2] = l3;
		for (int i = 0; i < 3; i++)
		{
			boki[i].Rysuj(tab);
		}
	}

	void set_center() override {
		fillx = (I + I + I + w) / 3;
		filly = (J + J + h + J + h) / 3;
	}
};
class Circle : public Figure {
public:
	Circle(int r) : radius(r)
	{
		h = w = 2 * r;
	};
	void Rysuj(color** tab) override {
		Figure::Rysuj(tab);
		cout << "\nRysuje kolo\n";
	}
private:
	int radius;
	void setPixel(struct color** tab, int x, int y) {
		tab[x][y] = fg;
	}
	void set_center() override {
		fillx = I + w / 2;
		filly = J + w / 2;
		cout << "\n" << fillx << " !!!!!!!!!!!!!!\n";
		cout << "\n" << filly << " !!!!!!!!!!!!!!\n";
	}    void Draw_Circuit(color** tab) override {
		int xc = I + h / 2;
		int yc = J + w / 2;
		int x = 0;
		int y = radius;
		int d = 1 - radius;
		while (x <= y) {
			setPixel(tab, xc + x, yc + y);
			setPixel(tab, xc - x, yc + y);
			setPixel(tab, xc + x, yc - y);
			setPixel(tab, xc - x, yc - y);
			setPixel(tab, xc + y, yc + x);
			setPixel(tab, xc - y, yc + x);
			setPixel(tab, xc + y, yc - x);
			setPixel(tab, xc - y, yc - x);
			if (d < 0)
				d += 2 * x + 3;
			else {
				d += 2 * (x - y) + 5;
				y--;
			}
			x++;
		}
	}
};


class TriangleRight : public Triangle {
public:
	TriangleRight(int size1, int size2) : Triangle(size1, size2) {};
	TriangleRight() {};

private:
	void Draw_Circuit(color** tab) override {
		cout << "\nObwod trojkata prawostronnego\n";
		Line l1(h, 1, I, J, fg);
		Line l2(1, w, I, J + w - 1, fg);
		Line l3(h, 1, I + h - 1, J, fg);
		l1.Rysuj(tab);
		l2.Rysuj(tab);
		l3.Rysuj(tab);
	}
};

class TriangleLeft : public Triangle {
public:
	TriangleLeft(int size1, int size2) : Triangle(size1, size2) {};
	TriangleLeft() {};

private:
	void Draw_Circuit(color** tab) override {
		cout << "\nObwod trojkata lewostronnego\n";
		Line l1(h, 1, I, J, fg);
		Line l2(1, w, I, J, fg);
		Line l3(h, 1, I, J + w - 1, fg);
		l1.Rysuj(tab);
		l2.Rysuj(tab);
		l3.Rysuj(tab);
	}
};

class TriangleRownaramienny : public Triangle {
public:
	TriangleRownaramienny(int size1, int size2) : Triangle(size1, size2) {};
	TriangleRownaramienny() {};

private:
	void Draw_Circuit(color** tab) override {
		cout << "\nObwod trojkata rownoramiennego\n";
		Line l1(h, 1, I, J, fg);
		Line l2(h, 1, I, J + w - 1, fg);
		Line l3(1, w, I, J, fg);
		l1.Rysuj(tab);
		l2.Rysuj(tab);
		l3.Rysuj(tab);
	}
};