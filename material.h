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


class Lambertian : public Material
{
public:
    explicit Lambertian(const Color& albedo) {}
    
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


class Metal : public Material
{
public:
    explicit Metal(const Color& albedo)
        : mAlbedo(albedo)
    {
    }

    bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = Reflect(rayIn.Direction(), hitRecord.Normal);

        scattered = Ray(hitRecord.Point, reflected);
        attenuation = mAlbedo;

        return true;
    }

private:
    Color mAlbedo;
};