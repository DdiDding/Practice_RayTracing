#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class HitRecord 
{
public:

    void SetFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
        bFrontFace = Dot(r.Direction(), outwardNormal) < 0;
        Normal = bFrontFace ? outwardNormal : -outwardNormal;
    }

    Point3 Point;
    Vec3 Normal;
    double T;
    bool bFrontFace;
};

class Hittable 
{
public:
    virtual ~Hittable() = default;

    virtual bool Hit(const Ray& r, double rayTMin, double rayTMax, HitRecord& rec) const = 0;
};

#endif