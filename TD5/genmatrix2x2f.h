#ifndef GENMATRIX2X2F_H
#define GENMATRIX2X2F_H
#include "point2f.h"

class GenMatrix2x2f
{
public:
    GenMatrix2x2f();
    virtual ~GenMatrix2x2f() {}
    virtual Point2f multiply(const Point2f& point) const = 0;
    virtual float val(int row, int col) const = 0;

};

#endif // GENMATRIX2X2F_H
