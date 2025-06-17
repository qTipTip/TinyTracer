#pragma once

#include <array>
#include <cmath>
#include <iostream>

class Vec3 {
private:
    std::array<float, 3> coordinates;

    public:

    // Constructors
    constexpr Vec3() : coordinates({0.0f, 0.0f, 0.0f}) {}
    constexpr Vec3(float x, float y, float z) : coordinates({x, y, z}) {}

    // Access elements
    constexpr float x() const { return coordinates[0]; }
    constexpr float y() const { return coordinates[1]; }
    constexpr float z() const { return coordinates[2]; }

    // Subscript operators, first one allows reading and writing
    // second one allows reading only.
    constexpr float& operator[](int i) { return coordinates[i]; }
    constexpr const float& operator[](int i) const { return coordinates[i]; }

    // Arithmetic

    // Negation
    constexpr Vec3 operator-() const {
        return Vec3(-coordinates[0], -coordinates[1], -coordinates[2]);
    }

    // Addition
    constexpr Vec3& operator+=(const Vec3& rhs) {
        coordinates[0] += rhs.coordinates[0];
        coordinates[1] += rhs.coordinates[1];
        coordinates[2] += rhs.coordinates[2];
        return *this;
    }

    // Scalar multiplication
    constexpr Vec3& operator*=(float t) {
        coordinates[0] *= t;
        coordinates[1] *= t;
        coordinates[2] *= t;
        return *this;
    }

    // Scalar division
    constexpr Vec3& operator/=(float t) {
        return *this *= (1.0f / t);
    }

    // Properties
    constexpr float length_squared() const {
        return
            coordinates[0] * coordinates[0] +
            coordinates[1] * coordinates[1] +
                coordinates[2] * coordinates[2];
    }

    float length() const {
        return std::sqrt(length_squared());
    }

    friend constexpr Vec3 operator/(const Vec3& v, float t);


    Vec3 unit_vector() const {
        return *this / length();
    }
};

using Point3 = Vec3;
using Color = Vec3;

// Vector utility functions
constexpr Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

constexpr Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

constexpr Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

constexpr Vec3 operator*(float t, const Vec3& v) {
    return Vec3(t * v.x(), t * v.y(), t * v.z());
}

constexpr Vec3 operator*(const Vec3& v, float t) {
    return t * v;
}

constexpr Vec3 operator/(const Vec3& v, float t) {
    return (1.0f / t) * v;
}

constexpr float dot(const Vec3& u, const Vec3& v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

constexpr Vec3 cross(const Vec3& u, const Vec3& v) {
    return Vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

// Output stream
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << '(' << v.x() << ',' << v.y() << ',' << v.z() << ')';
}