#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "image.h"
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

#endif // VIEWPORT_H