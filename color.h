#pragma once
#include <iostream>
#include "interval.h"
#include "Vec3.h"

using Color = Vec3;

// vec3클래스를 사용하여 단일 색상을 기록하는 함수
void WriteColor(std::ostream& out, const Color& pixelColor)
{
    auto red = pixelColor.X();
    auto green = pixelColor.Y();
    auto blue = pixelColor.Z();

    static const Interval intensity(0.000, 0.999);

    // [0,1] 범위의 컴포넌트 값을 바이트 범위 [0,255]로 변환합니다.
    int redByte = static_cast<int>(256.0 * intensity.Clamp(red));
    int greenByte = static_cast<int>(256.0 * intensity.Clamp(green));
    int blueByte = static_cast<int>(256.0 * intensity.Clamp(blue));

    // 픽셀 색상 컴포넌트를 출력합니다.
    out << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}