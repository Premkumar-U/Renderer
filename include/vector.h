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

Vector cross_product(const Vector& lhs, const Vector& rhs);
double dot_product(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& vector);
[[nodiscard]]
inline double length_squared(const Vector& vector);
[[nodiscard]]
double length(const Vector& vector);
[[nodiscard]]
Vector unit_vector(const Vector& vector);

#endif // VECTOR_H