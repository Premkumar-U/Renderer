#include "sphere.h"

bool Sphere::hit(const Ray& ray)
{
    Vector ray_origin_to_centre { location_ - ray.location() };

    double a { dot_product(ray.direction(), ray.direction()) };
    double b { -2 * dot_product(ray.direction(), ray_origin_to_centre) };
    double c { dot_product(ray_origin_to_centre, ray_origin_to_centre) - radius_ * radius_ };

    double discriminant { b * b - 4 * a * c };

    return discriminant >= 0;
}