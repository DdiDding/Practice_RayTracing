#include <iostream>

// PPM 포맷으로 이미지 출력

int main()
{
    // Image Size
    int ImageWidth = 256;
    int ImageHeight = 256;

    // Render
    std::cout << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";

    // 한 줄에 픽셀 하나의 RGB값을 의미한다.
    for (int j = 0; j < ImageHeight; j++)
    {
        for (int i = 0; i < ImageWidth; i++)
        {
            auto r = double(i) / (ImageWidth - 1);
            auto g = double(j) / (ImageHeight - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}