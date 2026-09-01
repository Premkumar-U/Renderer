#ifndef GRADIENT_RENDERER_H
#define GRADIENT_RENDERER_H

#include "camera.h"
#include "image.h"
#include "point.h"
#include "ray.h"
#include "vector.h"
#include "viewport.h"

class Gradient_renderer {
public:
    explicit Gradient_renderer(const Camera& camera, const Viewport& viewport)
        : camera_ { camera }
        , viewport_ { viewport }
    {
    }

    void render(Image_8bit_colour* image) const;

private:
    Camera camera_;
    Viewport viewport_;

    double lerp(double a, double b, double t) const
    {
        return a + (b - a) * t;
    }

    Colour ray_colour(const Ray& ray) const;
};

#endif // GRADIENT_RENDERER_H