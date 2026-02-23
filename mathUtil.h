#pragma once

#include <cmath>
#include <limits>
#include <memory>

// Constants

constexpr double Infinity = std::numeric_limits<double>::infinity();
constexpr double Pi = 3.1415926535897932385;

// Utility Functions

inline double DegreesToRadians(double degrees)
{
    return degrees * Pi / 180.0;
}

// 0 ~ 1사이의 실수형 난수 생성
inline double RandomDouble()
{
    return std::rand() / (RAND_MAX + 1.0); // 1을 포함하지 않기 위한 +1
}

// 특정 범위의 난수 생성
inline double RandomDouble(double minimum, double maximum)
{
    return minimum + (maximum - minimum) * RandomDouble();
}