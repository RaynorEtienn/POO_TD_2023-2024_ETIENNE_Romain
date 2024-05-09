#include "diag2f.h"

Diag2f::Diag2f() : m_val1(0.f), m_val2(0.f) {}

Diag2f::Diag2f(float val1, float val2) : m_val1(val1), m_val2(val2) {}

Diag2f::Diag2f(const Diag2f &diag2f) : m_val1(diag2f.m_val1), m_val2(diag2f.m_val2) {}

Diag2f::~Diag2f() {}

Point2f Diag2f::multiply(const Point2f& point) const
{
    return Point2f(m_val1 * point.getX(), m_val2 * point.getY());
}

float Diag2f::val(int row, int col) const
{
    if (row == col)
    {
        return (row == 0) ? m_val1 : m_val2;
    }
    else
    {
        return 0.0f;
    }
}
