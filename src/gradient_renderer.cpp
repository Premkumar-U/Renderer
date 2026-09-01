#include "gradient_renderer.h"

void Gradient_renderer::render(Image_8bit_colour* image) const
{
    Point viewport_centre { camera_.location() + camera_.view_direction() * camera_.focal_length() };
    Vector viewport_left_direction { unit_vector(cross_product(camera_.up_direction(), camera_.view_direction())) };

    Point viewport_top_left { viewport_centre + viewport_left_direction * (viewport_.width() / 2) + camera_.up_direction() * (viewport_.height() / 2) };

    Vector viewport_right_direction { -viewport_left_direction };
    Vector viewport_down_direction { -camera_.up_direction() };

    Vector delta_u { viewport_right_direction * viewport_.width() / image->width() };
    Vector delta_v { viewport_down_direction * viewport_.height() / image->height() };

    Point point_0_0_location = viewport_top_left + delta_u * 0.5 + delta_v * 0.5;

    for (size_t i = 0; i < image->height(); i++) {
        for (size_t j = 0; j < image->width(); j++) {
            Point pixel_location = point_0_0_location + delta_u * static_cast<double>(i) + delta_v * static_cast<double>(j);
            Ray ray(camera_.location(), pixel_location - camera_.location());

            image->at(i, j) = ray_colour(ray);
        }
    }
}

Colour Gradient_renderer::ray_colour(const Ray& ray) const
{
    Vector ray_direction = ray.direction();
    double y_in_range_0_1 = 0.5 * (ray_direction.y + 1.0);
    return Colour {
        1.0 * (1.0 - y_in_range_0_1) + 0.5 * y_in_range_0_1,
        1.0 * (1.0 - y_in_range_0_1) + 0.7 * y_in_range_0_1,
        1.0 * (1.0 - y_in_range_0_1) + 1.0 * y_in_range_0_1
    };
}