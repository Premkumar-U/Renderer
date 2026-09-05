#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"
#include "ray_traceable.h"
#include "renderable.h"

class Sphere : public renderable, public ray_traceable {
public:
    explicit Sphere(const Point& location, double radius)
        : location_ { location }
        , radius_(radius)
    {
    }

    bool hit(const Ray& ray) override;

private:
    Point location_ { Point::origin };
    double radius_ { 0.0 };
};

#endif // SPHERE_H