#include <boost/multi_array.hpp>
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>

struct Vector {
    double x = 0;
    double y = 0;
    double z = 0;

    Vector() = default;
    Vector(double x, double y, double z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    friend Vector operator*(const Vector& vector, double scalar)
    {
        return Vector { vector.x * scalar, vector.y * scalar, vector.z * scalar };
    }

    friend Vector operator*(double scalar, const Vector& vector)
    {
        return Vector { vector.x * scalar, vector.y * scalar, vector.z * scalar };
    }

    friend Vector operator/(const Vector& vector, double scalar)
    {
        return Vector { vector.x / scalar, vector.y / scalar, vector.z / scalar };
    }

    friend Vector operator/(double scalar, const Vector& vector)
    {
        return Vector { vector.x / scalar, vector.y / scalar, vector.z / scalar };
    }

    friend std::ostream& operator<<(std::ostream& stream, const Vector& object)
    {
        return stream << object.x << ", " << object.y << ", " << object.z;
    }
};

Vector cross_product(const Vector& lhs, const Vector& rhs)
{
    return Vector(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
}

Vector operator-(const Vector& vector)
{
    return Vector { -vector.x, -vector.y, -vector.z };
}

[[nodiscard]]
inline double length_squared(const Vector& vector)
{
    return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

[[nodiscard]]
double length(const Vector& vector)
{
    return std::sqrt(length_squared(vector));
}

[[nodiscard]]
Vector unit_vector(const Vector& vector)
{
    return vector / length(vector);
}

struct Point {
    double x = 0;
    double y = 0;
    double z = 0;

    Point() = default;
    Point(double x, double y, double z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    friend Point operator+(const Vector& vector, const Point& point)
    {
        return Point { vector.x + point.x, vector.y + point.y, vector.z + point.z };
    }

    friend Point operator+(const Point& point, const Vector& vector)
    {
        return Point { vector.x + point.x, vector.y + point.y, vector.z + point.z };
    }

    friend std::ostream& operator<<(std::ostream& stream, const Point& object)
    {
        return stream << object.x << ", " << object.y << ", " << object.z;
    }

    friend Vector operator-(const Point& lhs, const Point& rhs)
    {
        return Vector { rhs.x - lhs.x, rhs.y - lhs.y, rhs.z - lhs.z };
    }
};

class Colour_exception : public std::exception { };

class Colour {
public:
    constexpr Colour() noexcept = default;

    Colour(double red, double green, double blue)
        : red_ { red }
        , green_ { green }
        , blue_ { blue }
    {
        validate(red_);
        validate(blue_);
        validate(green_);
    }

    [[nodiscard]]
    constexpr double red() const noexcept
    {
        return red_;
    }

    [[nodiscard]]
    constexpr double green() const noexcept
    {
        return green_;
    }

    [[nodiscard]]
    constexpr double blue() const noexcept
    {
        return blue_;
    }

    void red(double value)
    {
        validate(value);
        red_ = value;
    }

    void green(double value)
    {
        validate(value);
        green_ = value;
    }

    void blue(double value)
    {
        validate(value);
        blue_ = value;
    }

private:
    double red_ { 0 };
    double green_ { 0 };
    double blue_ { 0 };

    static constexpr void validate(double value)
    {
        if (value < 0 || value > 1)
            throw Colour_exception {};
    }
};

template <typename T>
class Image {
public:
    explicit Image(std::size_t width, std::size_t height)
        : pixels_ { boost::extents[height][width] }
    {
    }

    [[nodiscard]]
    T& at(std::size_t row, std::size_t column)
    {
        return pixels_[row][column];
    }

    [[nodiscard]]
    const T& at(std::size_t row, std::size_t column) const
    {
        return pixels_[row][column];
    }

    [[nodiscard]]
    std::size_t width() const noexcept
    {
        return pixels_.shape()[1];
    }

    [[nodiscard]]
    std::size_t height() const noexcept
    {
        return pixels_.shape()[0];
    }

private:
    boost::multi_array<T, 2> pixels_;
};

using Image_8bit_colour = Image<Colour>;

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

constexpr std::size_t image_width = 1920;
constexpr std::size_t image_height = 1080;

class Viewport {
public:
    explicit Viewport(double height, const Image_8bit_colour& image)
        : height_ { height }
    {
        double aspect_ratio = static_cast<double>(image.width()) / static_cast<double>(image.height());
        width_ = aspect_ratio * height_;
    }

    [[nodiscard]]
    double width() const
    {
        return width_;
    }

    [[nodiscard]]
    double height() const
    {
        return height_;
    }

private:
    double width_;
    double height_;
};

class Gradient_renderer {
public:
    explicit Gradient_renderer(const Camera& camera, const Viewport& viewport)
        : camera_ { camera }
        , viewport_ { viewport }
    {
    }

    void render(Image_8bit_colour* image) const
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

private:
    Camera camera_;
    Viewport viewport_;

    double lerp(double a, double b, double t) const
    {
        return a + (b - a) * t;
    }

    Colour ray_colour(const Ray& ray) const
    {
        Vector ray_direction = ray.direction();
        double y_in_range_0_1 = 0.5 * (ray_direction.y + 1.0);
        return Colour {
            1.0 * (1.0 - y_in_range_0_1) + 0.5 * y_in_range_0_1,
            1.0 * (1.0 - y_in_range_0_1) + 0.7 * y_in_range_0_1,
            1.0 * (1.0 - y_in_range_0_1) + 1.0 * y_in_range_0_1
        };
    }
};

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