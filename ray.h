#ifndef RAY_H
#define RAY_H

#include "point.h"
#include "vector.h"

class Ray {
public:
    Ray(const Point& location, const Vector& direction)
        : location_ { location }
        , directon_ { unit_vector(direction) }
    {
    }

    [[nodiscard]]
    const Point& location() const
    {
        return location_;
    }

    [[nodiscard]]
    const Vector& direction() const
    {
        return directon_;
    }

private:
    Point location_;
    Vector directon_;
};

#endif // RAY_H