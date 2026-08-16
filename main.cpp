#include <boost/multi_array.hpp>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>

#include "camera.h"
#include "colour.h"
#include "gradient_renderer.h"
#include "image.h"
#include "viewport.h"

void render_gradient(Image_8bit_colour* image)
{
    size_t width = image->width();
    size_t height = image->height();

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Colour& pixel = image->at(i, j);
            pixel.red(static_cast<double>(j) / static_cast<double>(width));
            pixel.green(static_cast<double>(i) / static_cast<double>(height));
        }
    }
}

inline int convert_to_range(double value, int max)
{
    return static_cast<int>(std::round(value * static_cast<double>(max)));
}

void write_ppm_file(const Image_8bit_colour& image,
    const std::string& file_name)
{
    size_t width = image.width();
    size_t height = image.height();

    std::ofstream file { file_name };

    file << "P3\n"
         << width << ' ' << height << "\n255\n";

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            const Colour& pixel = image.at(i, j);
            int red = convert_to_range(pixel.red(), 255);
            int green = convert_to_range(pixel.green(), 255);
            int blue = convert_to_range(pixel.blue(), 255);

            file << red << ' ' << green << ' ' << blue << '\n';
        }
    }
}

constexpr std::size_t image_width = 1920;
constexpr std::size_t image_height = 1080;

int main(int argc, char const* argv[])
{
    Image_8bit_colour image { image_width, image_height };
    render_gradient(&image);
    write_ppm_file(image, "gradient.ppm");

    Camera camera { Point { 0, 0, 0 }, Vector { 0, 0, -1 }, Vector { 0, 1, 0 }, 1 };
    Viewport viewport { 2, image };
    Gradient_renderer renderer { camera, viewport };

    renderer.render(&image);
    write_ppm_file(image, "linear_gradient.ppm");
    return 0;
}