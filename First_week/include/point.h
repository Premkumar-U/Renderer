#ifndef POINT_H
#define POINT_H

#include "vector.h"

struct Point {
    double x = 0;
    double y = 0;
    double z = 0;

    Point() = default;
    Point(double x, double y, double z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    static const Point origin;

    friend Point operator+(const Vector& vector, const Point& point)
    {
        return Point { vector.x + point.x, vector.y + point.y, vector.z + point.z };
    }

    friend Point operator+(const Point& point, const Vector& vector)
    {
        return Point { vector.x + point.x, vector.y + point.y, vector.z + point.z };
    }

    friend std::ostream& operator<<(std::ostream& stream, const Point& object)
    {
        return stream << object.x << ", " << object.y << ", " << object.z;
    }

    friend Vector operator-(const Point& lhs, const Point& rhs)
    {
        return Vector { rhs.x - lhs.x, rhs.y - lhs.y, rhs.z - lhs.z };
    }
};

#endif // POINT_H