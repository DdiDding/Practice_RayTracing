#pragma once
#include <cmath>
#include <iostream>
#include "mathUtil.h"

class Vector3
{
public:

    Vector3() : E{ 0,0,0 } {}
    Vector3(double e0, double e1, double e2) : E{ e0, e1, e2 } {}

    double X() const { return E[0]; }
    double Y() const { return E[1]; }
    double Z() const { return E[2]; }

    Vector3 operator-() const { return Vector3(-E[0], -E[1], -E[2]); }
    double operator[](int i) const { return E[i]; }
    double& operator[](int i) { return E[i]; }

    Vector3& operator+=(const Vector3& v)
    {
        E[0] += v.E[0];
        E[1] += v.E[1];
        E[2] += v.E[2];
        return *this;
    }

    Vector3& operator*=(double t)
    {
        E[0] *= t;
        E[1] *= t;
        E[2] *= t;
        return *this;
    }

    Vector3& operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double Length() const
    {
        return std::sqrt(LengthSquared());
    }

    double LengthSquared() const
    {
        return E[0] * E[0] + E[1] * E[1] + E[2] * E[2];
    }

    static Vector3 Random()
    {
        return Vector3(RandomDouble(), RandomDouble(), RandomDouble());
    }

public:

    double E[3];
};
using Point3 = Vector3;
using Vec3 = Vector3;


// 벡터 클래스의 유틸리티 함수
inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    return out << v.E[0] << ' ' << v.E[1] << ' ' << v.E[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
    return Vector3(u.E[0] + v.E[0], u.E[1] + v.E[1], u.E[2] + v.E[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
    return Vector3(u.E[0] - v.E[0], u.E[1] - v.E[1], u.E[2] - v.E[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v)
{
    return Vector3(u.E[0] * v.E[0], u.E[1] * v.E[1], u.E[2] * v.E[2]);
}

inline Vector3 operator*(double t, const Vector3& v)
{
    return Vector3(t * v.E[0], t * v.E[1], t * v.E[2]);
}

inline Vector3 operator*(const Vector3& v, double t)
{
    return t * v;
}

inline Vector3 operator/(const Vector3& v, double t)
{
    return (1 / t) * v;
}

inline double Dot(const Vector3& u, const Vector3& v)
{
    return u.E[0] * v.E[0]
        + u.E[1] * v.E[1]
        + u.E[2] * v.E[2];
}

inline Vector3 Cross(const Vector3& u, const Vector3& v)
{
    return Vector3(u.E[1] * v.E[2] - u.E[2] * v.E[1],
        u.E[2] * v.E[0] - u.E[0] * v.E[2],
        u.E[0] * v.E[1] - u.E[1] * v.E[0]);
}

inline Vector3 UnitVector(const Vector3& v)
{
    return v / v.Length();
}