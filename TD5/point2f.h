#ifndef POINT2F_H
#define POINT2F_H

#include <iostream>

class Point2f {
public:
    Point2f();
    Point2f(float f1, float f2);
    Point2f(const Point2f &point2f);
    ~Point2f();

    // Accessors
    float getX() const;
    float getY() const;

    // Mutators
    void setX(float p_x);
    void setY(float p_y);

    // Operators
    Point2f operator+(const Point2f& other) const;
    Point2f operator-(const Point2f& other) const;
    Point2f& operator=(const Point2f& other);

    // Products
    float produitScalaire(const Point2f& other) const;
    float produitVectoriel(const Point2f& other) const;

    // Equality
    bool egalite(const Point2f& other) const;

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Point2f& point);

private:
    float x;
    float y;
};

#endif // POINT2F_H
