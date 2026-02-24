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
