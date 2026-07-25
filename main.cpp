#include <boost/multi_array.hpp>
#include <exception>
#include <iostream>
#include <fstream>

class Colour_exception : public std::exception
{
};

class Pixel
{
  public:
    constexpr Pixel() noexcept = default;

    Pixel(float red, float green, float blue) : red_{red}, green_{green}, blue_{blue}
    {
        validate(red_);
        validate(blue_);
        validate(green_);
    }

    [[nodiscard]]
    constexpr float red() const noexcept
    {
        return red_;
    }

    [[nodiscard]]
    constexpr float green() const noexcept
    {
        return green_;
    }

    [[nodiscard]]
    constexpr float blue() const noexcept
    {
        return blue_;
    }

    void red(float value)
    {
        validate(value);
        red_ = value;
    }

    void green(float value)
    {
        validate(value);
        green_ = value;
    }

    void blue(float value)
    {
        validate(value);
        blue_ = value;
    }

  private:
    float red_{0};
    float green_{0};
    float blue_{0};

    static constexpr void validate(float value)
    {
        if (value < 0 || value > 1)
            throw Colour_exception{};
    }
};

template <typename T> class Image
{
  public:
    explicit Image(std::size_t width, std::size_t height) : pixels_{boost::extents[height][width]}
    {
    }

    [[nodiscard]]
    T &at(std::size_t row, std::size_t column)
    {
        return pixels_[row][column];
    }

    [[nodiscard]]
    const T &at(std::size_t row, std::size_t column) const
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

using Image_8bit_colour = Image<Pixel>;

void render_gradient(Image_8bit_colour *image)
{
    size_t width = image->width();
    size_t height = image->height();

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            Pixel& pixel = image->at(i, j);
            pixel.red(static_cast<float>(j) / static_cast<float>(width));
            pixel.green(static_cast<float>(i) / static_cast<float>(height));
        }
    }
}

inline int convert_to_range(float value, int max)
{
    return static_cast<int>(std::round(value * static_cast<float>(max)));
}

void write_ppm_file(const Image_8bit_colour& image, const std::string& file_name)
{
    size_t width = image.width();
    size_t height = image.height();

    std::ofstream file {file_name};

    file << "P3\n" << width << ' ' << height << "\n255\n";

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            const Pixel &pixel = image.at(i, j);
            int red = convert_to_range(pixel.red(), 255);
            int green = convert_to_range(pixel.green(), 255);
            int blue = convert_to_range(pixel.blue(), 255);

            file << red << ' ' << green << ' ' << blue << '\n';
        }
    }
} 

int main(int argc, char const *argv[])
{
    Image_8bit_colour image{800, 600};
    render_gradient(&image);
    write_ppm_file(image, "gradient.ppm");
    return 0;
}
