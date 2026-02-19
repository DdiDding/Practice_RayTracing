#include <iostream>
#include "color.h"
#include "vec3.h"

int main()
{
    // Image
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    // 이미지 높이를 계산하고, 최소 1 이상인지 확인한다.
    // 0이 되면 이후 0나누기에 대한 문제 발생 가능,
    // 최소한 1픽셀은 있어야 유효한 이미지이기 때문.
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // 뷰포트의 높이를 임의의 값 2로 설정
    auto viewportHeight = 2.0; 
    // 뷰포트의 높이를 이용해 가로크기를 이미지 해상도와 동일하게 유지한다.
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

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
