#include "PPMImage.h"

PPMImage::PPMImage(int x, int y) {
    dX = x;
    dY = y;

    allocate();
}

PPMImage::PPMImage() {
    dX = 0;
    dY = 0;

    tab = NULL;
    tab1D = NULL;
}

PPMImage::~PPMImage() {
    clear();
    if (k) {
        delete k;
    }
}

void PPMImage::allocate() {
    clear();
    tab1D = new struct color[dX * dY];
    tab = new struct color* [dY];
    for (int i = 0; i < dY; i++)
        tab[i] = tab1D + i + dX;

}
void PPMImage::clear() {
    if (tab == NULL || tab1D == NULL) {
        delete tab;
        delete tab1D;
        
    }
}

void PPMImage::saveFile(string filename, int fraktal) {

    ofstream plik;
    plik.open(filename, ios::binary);

    cout << dX << endl;
    plik << "P6" << endl;
    plik << dX << "" << dY << endl;
    plik << "255" << endl;
    if(fraktal)
        for (int j = 0; j < dY; ++j)
            for (int i = 0; i < dX; ++i) {
                tab[j][i].r = i % 256;
                tab[j][i].g = (i - j) % 256;
                tab[j][i].b = (i + j) % 256;
            }

    plik.write((char*) tab1D, 3 * dX * dY);

    plik.close();

}

void PPMImage::loadFile(string filename) {
    ifstream plik;
    string tmp;
    plik.open(filename, ios::binary);
    getline(plik, tmp);
    cout << tmp << endl;
    plik >> dX;
    plik >> dY;
    getline(plik, tmp);
    cout << dX << " " << dY << tmp << endl;
    getline(plik, tmp);
    cout << tmp << endl;
    
    allocate();


    plik.close();
}

string PPMImage::convert(unsigned char c)
{
    int d = c;
    return to_string(d);
};

void PPMImage::saveFileP3(string filename) {
        
    ofstream plik;
    plik.open(filename);

    plik << "P3" << endl;
    plik << dX << "" << dY << endl;
    plik << "255" << endl;
    for (int j = 0; j < dY; ++j) {
        for (int i = 0; i < dX; ++i) {
            plik << convert(i % 256) << " ";
            plik << convert((i - j) % 256) << " ";
            plik << convert((i + j) % 256) << " ";
        }
    }

    plik.close();

}

void PPMImage::white_board() {
    for (int j = 0; j < dY; ++j) {
        for (int i = 0; i < dX; ++i) {
            tab[i][j].r = tab[i][j].g = tab[i][j].b = 255;
        }
    }
}

void PPMImage::addPoint(const Point *p) {
    for (int j = p->J * pointSize; j < (p->J + 1) * pointSize - 1; ++j) {
        for (int i = p->I * pointSize; i < (p->I + 1) * pointSize - 1; ++i) {
            tab[j][i] = p->mycolor;
        }
    }
}