#include <iostream>
#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

int main()
{
    /*************************************************/
    // Material 설정
    auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto materialLeft = std::make_shared<Dielectric>(1.00 / 1.33);
	auto materialRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    /*************************************************/
    // world 설정
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));                     
    world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, materialCenter));
    world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));
    /*************************************************/
    // camera 설정
    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 100;
    camera.maxDepth = 50;

    camera.Render(world);

    return 0;
}
