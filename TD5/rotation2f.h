#ifndef ROTATION2F_H
#define ROTATION2F_H

#include "genmatrix2x2f.h"
#include "point2f.h"
#include <cmath> // Pour std::cos et std::sin

class Rotation2f : public GenMatrix2x2f {
private:
    float angle; // Angle de rotation en radians

public:
    // Constructeur prenant l'angle de rotation en radians
    Rotation2f();
    Rotation2f(float angleRadians);
    Rotation2f(const Rotation2f &rotation2f);

    // Implémentation des méthodes virtuelles pures de GenMatrix2x2f
    virtual Point2f multiply(const Point2f& point) const override;
    virtual float val(int row, int col) const override;

    virtual ~Rotation2f();
};

#endif // ROTATION2F_H
