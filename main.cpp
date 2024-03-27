#include "PPMImage.h"

using namespace std;

int main()
{
    PPMImage* obraz = new PPMImage(500, 500);
    obraz->white_board();

    Point *p = new Point(3, 4, 0, 255, 0);
    obraz->addPoint(p);
    
    obraz->k = new Point(1, 1, 250, 0, 0);
    obraz->addPoint(obraz->k);

    obraz->saveFile("nowy2.ppm", 0);
    
    delete obraz;
    delete p;

}
