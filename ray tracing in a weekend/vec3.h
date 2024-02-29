#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

// TODO: SIMD math, maybe seperate header and implimentation.
/// <summary>
/// Standard 3 component (x, y, z) vector.
/// </summary>
class Vec3 {
public:
    double values[3];

    // Constructors
    Vec3() : values{ 0,0,0 } {}
    Vec3(double x, double y, double z) : values{ x, y, z } {}

    // Getters
    double x() const { return values[0]; }
    double y() const { return values[1]; }
    double z() const { return values[2]; }

    // Operator overrides
    Vec3 operator-() const { return Vec3(-values[0], -values[1], -values[2]); }
    double operator[](int i) const { return values[i]; }
    double& operator[](int i) { return values[i]; }

    Vec3& operator+=(const Vec3& v) {
        values[0] += v.values[0];
        values[1] += v.values[1];
        values[2] += v.values[2];
        return *this;
    }

    Vec3& operator*=(double t) {
        values[0] *= t;
        values[1] *= t;
        values[2] *= t;
        return *this;
    }

    Vec3& operator/=(double t) {
        return *this *= 1 / t;
    }

    // Common quick calculations
    double Length() const {
        return sqrt(LengthSquared());
    }

    double LengthSquared() const {
        return values[0] * values[0] + values[1] * values[1] + values[2] * values[2];
    }

    static Vec3 Random() {
        return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    static Vec3 Random(double min, double max) {
        return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using Point3 = Vec3;


// Vector Utility Functions
// Operators
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v.values[0] << ' ' << v.values[1] << ' ' << v.values[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u.values[0] + v.values[0], u.values[1] + v.values[1], u.values[2] + v.values[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u.values[0] - v.values[0], u.values[1] - v.values[1], u.values[2] - v.values[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u.values[0] * v.values[0], u.values[1] * v.values[1], u.values[2] * v.values[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t * v.values[0], t * v.values[1], t * v.values[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1 / t) * v;
}

// Functions
inline double Dot(const Vec3& u, const Vec3& v) {
    return u.values[0] * v.values[0]
        + u.values[1] * v.values[1]
        + u.values[2] * v.values[2];
}

inline Vec3 Cross(const Vec3& u, const Vec3& v) {
    return Vec3(u.values[1] * v.values[2] - u.values[2] * v.values[1],
        u.values[2] * v.values[0] - u.values[0] * v.values[2],
        u.values[0] * v.values[1] - u.values[1] * v.values[0]);
}

inline Vec3 UnitVector(Vec3 v) {
    return v / v.Length();
}

inline Vec3 RandomInUnitSphere() {
    while (true) {
        Vec3 vec = Vec3::Random(-1,1);
        if (vec.LengthSquared() < 1) {
            return vec;
        }
    }
}

inline Vec3 RandomUnitVector() {
    return UnitVector(RandomInUnitSphere());
}

inline Vec3 RandomOnHemisphere(const Vec3& normal) {
    Vec3 onUnitSphere = RandomUnitVector();
    if (Dot(onUnitSphere, normal) > 0.0) {
        return onUnitSphere;
    }
    return -onUnitSphere;
}
