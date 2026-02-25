#include <iostream>
#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

using std::make_shared;

int main()
{
    /*************************************************/
    // Material 설정


    /*************************************************/
    // world 설정
    HittableList world;

    auto R = std::cos(Pi / 4);

    auto materialLeft = make_shared<Lambertian>(Color(0, 0, 1));
    auto materialRight = make_shared<Lambertian>(Color(1, 0, 0));

    world.Add(make_shared<Sphere>(Point3(-R, 0, -1), R, materialLeft));
    world.Add(make_shared<Sphere>(Point3(R, 0, -1), R, materialRight));

    /*************************************************/
    // camera 설정
    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 100;
    camera.maxDepth = 50;

    camera.vFov = 90;

    camera.Render(world);

    return 0;
}
