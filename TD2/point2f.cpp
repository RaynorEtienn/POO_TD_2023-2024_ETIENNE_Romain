#include "point2f.h"

// Constructors
Point2f::Point2f() : x(0.f), y(0.f) {}
Point2f::Point2f(float f1, float f2) : x(f1), y(f2) {}
Point2f::Point2f(const Point2f &point2f) : x(point2f.x), y(point2f.y) {}

// Destructor
Point2f::~Point2f() {}

// Operator Overloads
Point2f& Point2f::operator=(const Point2f& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Point2f Point2f::operator+(const Point2f& other) const {
    return Point2f(this->x + other.x, this->y + other.y);
}

Point2f Point2f::operator-(const Point2f& other) const {
    return Point2f(this->x - other.x, this->y - other.y);
}

// Scalar and Vector Products
float Point2f::produitScalaire(const Point2f &other) const {
    return this->x * other.x + this->y * other.y;
}

float Point2f::produitVectoriel(const Point2f &other) const {
    return this->x * other.y - this->y * other.x;
}

// Equality
bool Point2f::egalite(const Point2f &other) const {
    return this->x == other.x && this->y == other.y;
}

// Accessors
float Point2f::getX() const { return x; }
float Point2f::getY() const { return y; }

// Mutators
void Point2f::setX(float p_x) { x = p_x; }
void Point2f::setY(float p_y) { y = p_y; }

// Stream Insertion Operator
std::ostream& operator<<(std::ostream& os, const Point2f& point) {
    os << "x: " << point.x << ", y: " << point.y;
    return os;
}
