#pragma once
#include "Vec3.h"

/**
 * @class ray 광선의 개념을 의미하는 클래스
 */
class Ray
{
public:
    Ray() {}

    Ray(const Point3& origin, const Vector3& direction)
        : mOrigin(origin), mDir(direction) {}

    // 광선의 원점(쏘아지는 위치)
    const Point3& Origin() const { return mOrigin; }
    // 광선의 방향 벡터
    const Vector3& Direction() const { return mDir; }

    /**
     * 매개변수 t에 해당하는 광선 상의 점을 반환한다.
     */
    Point3 At(double t) const
    {
        return mOrigin + t * mDir;
    }

private:
    Point3 mOrigin;
    Vector3 mDir;
};