// Material.h
#pragma once

#include "Hittable.h"

class Material
{
public:
    virtual ~Material() = default;


    // »ê¶õ
    virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const
    {
        return false;
    }
};


class Labertian : public Material
{
public:
    explicit Labertian(const Color& albedo) {}
    
    bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override
    {
        Vec3 scatterDirection = hitRecord.Normal + RandomUnitVector();

        // Catch degenerate scatter direction
        if (scatterDirection.NearZero())
        {
            scatterDirection = hitRecord.Normal;
        }

        scattered = Ray(hitRecord.Point, scatterDirection);
        attenuation = mAlbedo;

        return true;
    }
private:
    Color mAlbedo;
};