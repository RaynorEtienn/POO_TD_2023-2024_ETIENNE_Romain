#include "rotation2f.h"
#include "point2f.h"

Rotation2f::Rotation2f() : angle(0.f) {}

Rotation2f::Rotation2f(float angleRadians) : angle(angleRadians) {}

Rotation2f::Rotation2f(const Rotation2f &rotation2f) : angle(rotation2f.angle) {}

Rotation2f::~Rotation2f() {};

Point2f Rotation2f::multiply(const Point2f& point) const
{
    // Calcul de la multiplication de la matrice de rotation par un point
    float x = std::cos(angle) * point.getX() - std::sin(angle) * point.getY();
    float y = std::sin(angle) * point.getX() + std::cos(angle) * point.getY();
    return Point2f(x, y);
}

float Rotation2f::val(int row, int col) const {
    if (row == 0 && col == 0)
    {
        return std::cos(angle);
    }
    if (row == 0 && col == 1)
    {
        return -std::sin(angle);
    }
    if (row == 1 && col == 0)
    {
        return std::sin(angle);
    }
    if (row == 1 && col == 1)
    {
        return std::cos(angle);
    }
    return 0.0f; // Pour tout autre indice, ce qui ne devrait pas arriver
}
