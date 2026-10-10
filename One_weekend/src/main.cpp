#include <cmath>
#include <fstream>

#include "camera.h"
#include "colour.h"
#include "gradient_renderer.h"
#include "image.h"
#include "red_sphere_renderer.h"
#include "sphere.h"
#include "viewport.h"
#include "world.h"

void render_gradient(Image_8bit_colour *image) {
    const size_t width = image->width();
    const size_t height = image->height();

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Colour &pixel = image->at(i, j);
            pixel.red(static_cast<double>(j) / static_cast<double>(width));
            pixel.green(static_cast<double>(i) / static_cast<double>(height));
        }
    }
}

inline int convert_to_range(double value, int max) {
    return static_cast<int>(std::round(value * static_cast<double>(max)));
}

void write_ppm_file(const Image_8bit_colour &image,
                    const std::string &file_name) {
    const size_t width = image.width();
    const size_t height = image.height();

    std::ofstream file{file_name};

    file << "P3\n"
            << width << ' ' << height << "\n255\n";

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            const Colour &pixel = image.at(i, j);
            const int red = convert_to_range(pixel.red(), 255);
            const int green = convert_to_range(pixel.green(), 255);
            const int blue = convert_to_range(pixel.blue(), 255);

            file << red << ' ' << green << ' ' << blue << '\n';
        }
    }
}

constexpr std::size_t image_width = 1920;
constexpr std::size_t image_height = 1080;

using namespace std::literals;

int main(int argc, char const *argv[]) {
    Image_8bit_colour image{image_width, image_height};
    render_gradient(&image);
    write_ppm_file(image, "gradient.ppm"s);

    const Camera camera{Point{0, 0, 0}, Vector{0, 0, -1}, Vector{0, 1, 0}, 1};
    const Viewport viewport{2, image};

    const Gradient_renderer renderer{camera, viewport};

    renderer.render(&image);
    write_ppm_file(image, "linear_gradient.ppm");

    World world;
    world.emplace_back(std::make_unique<Sphere>(Point{0, 0, -1}, 0.5));

    const Red_sphere_renderer red_sphere_renderer{camera, viewport};

    red_sphere_renderer.render(&image, world);
    write_ppm_file(image, "red_sphere_gradient.ppm");

    return 0;
}
