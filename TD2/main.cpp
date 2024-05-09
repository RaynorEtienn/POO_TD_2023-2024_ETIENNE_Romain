#include <iostream>
#include "point2f.h"

using namespace std;

int main()
{
    Point2f p1;
    Point2f p2(1.f, 2.f);
    Point2f p3(p2);

    p1.PrintPoints();
    p2.PrintPoints();
    p3.PrintPoints();

    p3 = p1;
    cout << "Tentative p3 = p1" << endl;
    p3.PrintPoints();

    cout << "p3 = (1, 6)" << endl;
    p3.setX(1);
    p3.setY(6);
    p3.PrintPoints();
    cout << "p3.getX() : " << p3.getX() << endl;
    cout << "p3.getY() : " << p3.getY() << endl;

    cout << "Tentative p3 + p2" << endl;
    p3 = p3 + p1;
    p3.PrintPoints();




    return 0;
}
