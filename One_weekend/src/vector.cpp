#include "vector.h"

Vector cross_product(const Vector& lhs, const Vector& rhs)
{
    return Vector(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
}

double dot_product(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
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
inline double length(const Vector& vector)
{
    return std::sqrt(length_squared(vector));
}

[[nodiscard]]
Vector unit_vector(const Vector& vector)
{
    return vector / length(vector);
}
