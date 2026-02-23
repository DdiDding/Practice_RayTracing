#include <iostream>
#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

/**
 * 충돌 지점을 반환한다, 충돌하지 않으면 -1을 반환
 */
double HitSphere(const Point3& center, double radius, const Ray& r)
{
    // 광선 시작 지점과 구의 중앙의 위치 차이 벡터
    Vec3 oc = center - r.Origin();

    // 광선의 방향벡터 길이 제곱
    auto a = Dot(r.Direction(), r.Direction());

    // ray 방향 벡터와 중심 방향 벡터의 내적
    // → 구 중심 방향으로 얼마나 향하는지 나타내는 값
    auto b = Dot(r.Direction(), oc);

    // 레이 시작점이 구 중심에서 얼마나 떨어져 있는지를 나타내는 값
    // (구 내부/외부 판별 가능)
    auto c = oc.LengthSquared() - radius * radius;

    // 2차 방정식 판별식
    auto discriminant = (b * b) - (a * c);

    // 충돌 없음
    if (discriminant < 0.0) { return -1.0f; }

    // 근의 공식 이용하여 두 해중 작은 t 반환 => 먼저 만나는 지점이 필요하기 때문
    return (b - std::sqrt(discriminant)) / a;
}

int main()
{
    /*************************************************/
    // world 설정
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

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
