#include "PPMImage.h"
#include "Shapes.h"
using namespace std;

int main()
{
    Point p2(3, 3, 255, 0, 0);
    cout << p2;

    PPMImage obrazek1(50, 50);
    ofstream plik("nowy3.ppm", ios::binary);
    plik << obrazek1;

    Square square(10); 
    TriangleRight triangleRight(10, 10); 
    TriangleLeft triangleLeft(10, 10); 
    TriangleRownaramienny triangleRownoramienny(10, 10);

    square.Rysuj(obrazek1.getTab());
    triangleRight.Rysuj(obrazek1.getTab());
    triangleLeft.Rysuj(obrazek1.getTab());
    triangleRownoramienny.Rysuj(obrazek1.getTab());


    plik.close();
    /*
    PPMImage* obraz = new PPMImage(500, 500);
    obraz->white_board();

    Point *p = new Point(3, 4, 0, 255, 0);
    obraz->addPoint(p);
    
    obraz->k = new Point(1, 1, 250, 0, 0);
    obraz->addPoint(obraz->k);

    Point p2(*p);
    obraz->saveFile("nowy2.ppm", 0);
    
    delete obraz;
    delete p;

    */
}
