#ifndef RED_SPHERE_RENDERER_H
#define RED_SPHERE_RENDERER_H

#include "camera.h"
#include "image.h"
#include "ray.h"
#include "viewport.h"
#include "world.h"

class Red_sphere_renderer {
public:
    explicit Red_sphere_renderer(const Camera& camera, const Viewport& viewport)
        : camera_ { camera }
        , viewport_ { viewport }
    {
    }

    void render(Image_8bit_colour* image, const World& world) const;

private:
    Camera camera_;
    Viewport viewport_;

    double lerp(double a, double b, double t) const
    {
        return a + (b - a) * t;
    }

    Colour ray_colour(const Ray& ray, const World& world) const;
};

#endif // RED_SPHERE_RENDERER_H