#ifndef DIAG2F_H
#define DIAG2F_H

#include "genmatrix2x2f.h"
#include "point2f.h" // Make sure this is included if Point2f is in a separate file

class Diag2f : public GenMatrix2x2f {
private:
    float m_val1;
    float m_val2;

public:
    Diag2f();
    Diag2f(float val1, float val2);
    Diag2f(const Diag2f &diag2f);
    virtual ~Diag2f();

    virtual Point2f multiply(const Point2f& point) const override; // Corrected: Removed = 0 to indicate we'll provide an implementation
    virtual float val(int row, int col) const override; // Corrected: Removed = 0 to indicate we'll provide an implementation
};

#endif // DIAG2F_H
