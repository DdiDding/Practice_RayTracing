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
    explicit Lambertian(const Color& albedo) : mAlbedo(albedo) {}
    
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
    explicit Metal(const Color& albedo, double fuzz)
        : mAlbedo(albedo), mFuzz(fuzz < 1 ? fuzz : 1)
    {
    }

    bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = Reflect(rayIn.Direction(), hitRecord.Normal);
        reflected = UnitVector(reflected) + (mFuzz * RandomUnitVector());

        scattered = Ray(hitRecord.Point, reflected);
        attenuation = mAlbedo;

        return (Dot(scattered.Direction(), hitRecord.Normal) > 0);
    }

private:
    Color mAlbedo;
    double mFuzz;
};

class Dielectric : public Material
{
public:
    explicit Dielectric(double refractionIndex)
        : mRefractionIndex(refractionIndex) { }
    

    bool Scatter(
        const Ray& rayIn,
        const HitRecord& hitRecord,
        Color& attenuation,
        Ray& scattered
    ) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);

        const double refractionRatio =
            hitRecord.bFrontFace ? (1.0 / mRefractionIndex) : mRefractionIndex;

        const Vec3 unitDirection = UnitVector(rayIn.Direction());

        const double cosTheta =
            std::fmin(Dot(-unitDirection, hitRecord.Normal), 1.0);

        const double sinTheta =
            std::sqrt(1.0 - cosTheta * cosTheta);

        const bool cannotRefract =
            refractionRatio * sinTheta > 1.0;

        Vec3 direction;

        if (cannotRefract)
        {
            direction = Reflect(unitDirection, hitRecord.Normal);
        }
        else
        {
            direction = Refract(unitDirection, hitRecord.Normal, refractionRatio);
        }

        scattered = Ray(hitRecord.Point, direction);
        return true;
    }

private:
    // Refraction index (IOR). For air/vacuum -> material, typical  glass is ~1.5.
    double mRefractionIndex = 1.0;
};