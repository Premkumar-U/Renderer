#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include "vector.h"

class Camera {
public:
    explicit Camera(const Point& location, const Vector& view_direction, const Vector up_direction, double focal_length)
        : location_ { location }
        , view_direction_ { unit_vector(view_direction) }
        , up_direction_ { unit_vector(up_direction) }
        , focal_length_ { focal_length }
    {
    }

    [[nodiscard]]
    const Point& location() const
    {
        return location_;
    }

    [[nodiscard]]
    const Vector& view_direction() const
    {
        return view_direction_;
    }

    [[nodiscard]]
    const Vector& up_direction() const
    {
        return up_direction_;
    }

    [[nodiscard]]
    double focal_length() const
    {
        return focal_length_;
    }

private:
    Point location_;
    Vector view_direction_;
    Vector up_direction_;
    double focal_length_;
};

#endif // CAMERA_H