#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <ostream>

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

#endif // VECTOR_H