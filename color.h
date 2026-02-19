#pragma once
#include <iostream>
#include "Vec3.h"

using Color = Vec3;

// vec3클래스를 사용하여 단일 색상을 작성하는 함수
void WriteColor(std::ostream& out, const Color& pixelColor)
{
    auto r = pixelColor.X();
    auto g = pixelColor.Y();
    auto b = pixelColor.Z();

    // [0,1] 범위의 컴포넌트 값을 바이트 범위 [0,255]로 변환합니다.
    int rByte = int(255.999 * r);
    int gByte = int(255.999 * g);
    int bByte = int(255.999 * b);

    // 픽셀 색상 컴포넌트를 출력합니다.
    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}