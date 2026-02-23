#pragma once
#include <iostream>
#include "interval.h"
#include "vec3.h"

using Color = Vector3;

// vec3클래스를 사용하여 단일 색상을 기록하는 함수
void WriteColor(std::ostream& out, const Color& pixelColor)
{
    auto red = pixelColor.X();
    auto green = pixelColor.Y();
    auto blue = pixelColor.Z();

    static const Interval intensity(0.000, 0.999);

    double cRed = intensity.Clamp(red);
    double cGreen = intensity.Clamp(green);
    double cBlue = intensity.Clamp(blue);

    // [0,1] 범위의 컴포넌트 값을 바이트 범위 [0,255]로 변환합니다.
    int redByte = static_cast<int>(256.0 * intensity.Clamp(cRed));
    int greenByte = static_cast<int>(256.0 * intensity.Clamp(cGreen));
    int blueByte = static_cast<int>(256.0 * intensity.Clamp(cBlue));

    // 픽셀 색상 컴포넌트를 출력합니다.
    out << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}