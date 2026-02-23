#pragma once
#include <iostream>
#include "interval.h"
#include "vec3.h"

using Color = Vector3;

/**
 * 감마 보정을 위해 선형 공간에서 감마 공간으로 이동, 감마2의 역을 취한다.
 */
inline double LinearToGamma(double linearComponent)
{
    if (linearComponent > 0.0)
    {
        return std::sqrt(linearComponent);
    }

    return 0.0;
}

// vec3클래스를 사용하여 단일 색상을 기록하는 함수
void WriteColor(std::ostream& out, const Color& pixelColor)
{
    auto red = pixelColor.X();
    auto green = pixelColor.Y();
    auto blue = pixelColor.Z();

    // 감마 2.0공간으로 이동
    red = LinearToGamma(red);
    green = LinearToGamma(green);
    blue = LinearToGamma(blue);


    // [0,1] 범위의 컴포넌트 값을 바이트 범위 [0,255]로 변환
    static const Interval intensity(0.000, 0.999);

    red = intensity.Clamp(red);
    green = intensity.Clamp(green);
    blue = intensity.Clamp(blue);
    
    int redByte = static_cast<int>(256.0 * red);
    int greenByte = static_cast<int>(256.0 * green);
    int blueByte = static_cast<int>(256.0 * blue);

    // 픽셀 색상 컴포넌트를 출력합니다.
    out << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}