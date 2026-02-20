#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

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

/**
 * 광선의 색을 계산하는 함수
 * 충돌시 충돌한 점의 법선 벡터를 색으로 표현 함
 * 충돌하지 않았다면 광선 방향의 Y에 따라 파란색 -> 하얀색의 그라데이션 색 표현
 */
Color RayColor(const Ray& ray)
{
    double t = HitSphere(Point3(0.0, 0.0, -1.0), 0.5, ray);
    
    // 충돌시
    if (0.0 < t)
    {
        Vec3 surfaceNormal = UnitVector(ray.At(t) - Vec3(0.0, 0.0, -1.0));
        return 0.5 * Color(
            surfaceNormal.X() + 1.0,
            surfaceNormal.Y() + 1.0,
            surfaceNormal.Z() + 1.0
        );
    }

    // 충돌하지 않았을 때 (배경)
    Vec3 unitDirection = UnitVector(ray.Direction());
	auto a = 0.5 * (unitDirection.Y() + 1.0);

	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color	(0.5, 0.7, 1.0);
}

int main()
{
    // 목표 : 픽셀마다 광선을 만들어 장면에 쏘고, 가장 가까운 물체의 색을 계산한다.
    /*************************************************/
    // 이미지 설정
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int imageHeight = int(imageWidth / aspectRatio);
    /**
     * 이미지 높이를 계산하고, 최소 1 이상인지 확인한다.
     * 최소한 1픽셀은 있어야 유효한 이미지이기 때문이고, 
       0이 되면 이후 0 나누기에 대한 문제에 대한 방지를 위함이다.
     */
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;


    /*************************************************/
    // 카메라 설정
    // 카메라는 -Z를 바라본다고 가정
    auto focalLength = 1.0;
    auto viewportHeight = 2.0; // 임의의 값
    // 뷰포트의 높이를 이용해 가로크기를 이미지 해상도와 동일하게 유지한다.
    auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
    auto cameraCenter = Point3(0, 0, 0);
    
    // 뷰포트의 UV좌표 생성
    auto viewportU = Vec3(viewportWidth, 0, 0);
    // -viewportHeight로 음수인 이유는 이미지 좌표계의 y는 아래로 증가하기 때문
    auto viewportV = Vec3(0, -viewportHeight, 0); 

    // 픽셀 간 수평 및 수직 델타 벡터를 계산합니다.
    // 가로 방향으로 한 픽셀 이동할 때 월드 공간에서의 이동 벡터
    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    // 왼쪽 위 픽셀의 위치를 계산합니다.
    auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) 
        {
            auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            Color pixelColor = RayColor(r);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
    return 0;
}
