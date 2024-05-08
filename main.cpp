#include "PPMImage.h"
#include "Shapes.h"
#include <vector>
using namespace std;

int main()
{
    Point p2(3, 3, 255, 0, 0);
    cout << p2;

    PPMImage obrazek1(50, 50);
    ofstream plik("nowy3.ppm", ios::binary);
    plik << obrazek1;
    PPMImage obrazek1(500, 500);    
    obrazek1.white_board();    
    Square s(100);    
    Rectangle r = s;    

    r.set_JI(5, 5);    
    r.set_fg({ 0,0,255 });    
    r.Rysuj(obrazek1.getTab());   
    r.Fill({ 0,255,0 }, &obrazek1);    
    Filling f;    
    f.setBG({ 100, 0, 0 });   
    f.Fill(1, 1, &obrazek1);   
    Triangle t(100, 100);    
    t.set_JI(300, 300);    
    t.Rysuj(obrazek1.getTab());
    t.Fill({ 255,255,0 }, &obrazek1);    
    Circle c(25);    c.set_JI(150, 150);    
    c.set_fg({ 255,255,255 });    
    c.Rysuj(obrazek1.getTab());
    c.Fill({ 255,255,255 }, &obrazek1);   
    ofstream plik("nowy4.ppm", ios::binary);  
    plik << obrazek1;    plik.close();


    Square square(10); 
    TriangleRight triangleRight(10, 10); 
    TriangleLeft triangleLeft(10, 10); 
    TriangleRownaramienny triangleRownoramienny(10, 10);

    square.Rysuj(obrazek1.getTab());
    triangleRight.Rysuj(obrazek1.getTab());
    triangleLeft.Rysuj(obrazek1.getTab());
    triangleRownoramienny.Rysuj(obrazek1.getTab());

    vector<int> liczby;
    liczby.push_back(1);
    liczby.push_back(2);

    vector<Shape*> shape;
    shape.push_back(&r);
    shape.push_back(&t);
    cout << "##################" << endl;
    cout << shape.size() << endl;

    for (int i = 0; i < shape.size(); i++) {
        shape[i]->Rysuj(obrazek1.getTab());
    }

    for (auto item : shape) {
        item->Rysuj(obrazek1.getTab());
    }

    vector<Shape*>::iterator ptr;
    for (ptr = shape.begin(); ptr < shape.end(); ptr++) {
        (*ptr)->Rysuj(obrazek1.getTab());
    }

    ptr = shape.end();

    while (ptr != shape.begin()) {
        --ptr;
        (*ptr)->Rysuj(obrazek1.getTab());
    }

    ptr = shape.begin();

    while (ptr != shape.end()) {
        ptr++;
        (*ptr)->Rysuj(obrazek1.getTab());
    }

    plik.close();
    exit(0);
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
