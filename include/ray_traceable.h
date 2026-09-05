#ifndef RAY_TRACEABLE_H
#define RAY_TRACEABLE_H
#include "ray.h"

struct ray_traceable {
    virtual bool hit(const Ray& ray) = 0;
    virtual ~ray_traceable() = default;
};

#endif // RAY_TRACEABLE_H