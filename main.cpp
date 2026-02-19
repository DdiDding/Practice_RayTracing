#include <iostream>
#include "color.h"
#include "vec3.h"

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
            auto PixelColor = Color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
            WriteColor(std::cout, PixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
    return 0;
}
