#ifndef IMAGE_H
#define IMAGE_H
#include "colour.h"

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

#endif // IMAGE_H