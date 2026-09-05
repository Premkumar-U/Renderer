#ifndef COLOUR_H
#define COLOUR_H

#include <exception>

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

#endif // COLOUR_H