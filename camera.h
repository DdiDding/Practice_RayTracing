#pragma once
#include "Hittable.h"

class Camera
{
public:
    double aspectRatio = 1.0;   // Ratio of image width over height
    int imageWidth = 100;       // Rendered image width in pixel count
    int samplesPerPixel = 10;
    int maxDepth = 10; // RayColor의 최대 재귀 깊이


    void Render(const Hittable& world)
    {
        Initialize();

        std::cout << "P3\n" << imageWidth << ' ' << mImageHeight << "\n255\n";

        for (int scanlineIndex = 0; scanlineIndex < mImageHeight; scanlineIndex++)
        {
            std::clog
                << "\rScanlines remaining: "
                << (mImageHeight - scanlineIndex)
                << ' '
                << std::flush;

            for (int pixelIndex = 0; pixelIndex < imageWidth; pixelIndex++)
            {
                Color pixelColor(0.0, 0.0, 0.0);

                for (int sampleIndex = 0; sampleIndex < samplesPerPixel; ++sampleIndex)
                {
                    Ray ray = GetRay(pixelIndex, scanlineIndex);
                    pixelColor += RayColor(ray, maxDepth, world);
                }

                // 평균내는 코드
                pixelColor *= mPixelSamplesScale;
                WriteColor(std::cout, pixelColor);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:

    void Initialize()
    {
        mImageHeight = static_cast<int>(imageWidth / aspectRatio);
        mImageHeight = (mImageHeight < 1) ? 1 : mImageHeight;

        mPixelSamplesScale = 1.0 / static_cast<double>(samplesPerPixel);

        mCenter = Point3(0.0, 0.0, 0.0);

        // Determine viewport dimensions
        auto focalLength = 1.0;
        auto viewportHeight = 2.0;
        auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / mImageHeight);

        // Calculate the vectors across the horizontal and down the vertical viewport edges
        auto viewportU = Vec3(viewportWidth, 0.0, 0.0);
        auto viewportV = Vec3(0.0, -viewportHeight, 0.0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        mPixelDeltaU = viewportU / imageWidth;
        mPixelDeltaV = viewportV / mImageHeight;

        // Calculate the location of the upper left pixel
        auto viewportUpperLeft =
            mCenter
            - Vec3(0.0, 0.0, focalLength)
            - viewportU / 2.0
            - viewportV / 2.0;

        mPixel00Location = viewportUpperLeft + 0.5 * (mPixelDeltaU + mPixelDeltaV);
    }

    /**
     * 각 픽셀에 대해 다른 샘플을 생성한다.
     */
    Ray GetRay(int pixelIndex, int scanlineIndex) const
    {
        // 원점에서 출발하여 무작위로 샘플링된 카메라 광선을 구성한다
        // 픽셀 위치 pixelIndex, scanlineIndex를 가리킨다
        auto offset = SampleSquare();

        auto pixelSample =
            mPixel00Location
            + ((pixelIndex + offset.X()) * mPixelDeltaU)
            + ((scanlineIndex + offset.Y()) * mPixelDeltaV);

        auto rayOrigin = mCenter;
        auto rayDirection = pixelSample - rayOrigin;

        return Ray(rayOrigin, rayDirection);
    }

    /** 
     * 원점을 중심으로 한 단위 정사각형 내에서 무작위 샘플 포인트를 생성하는 새로운 헬퍼 함수
     */
    Vec3 SampleSquare() const
    {
        // 벡터를 [-.5, -.5] - [+.5, +.5] 단위 제곱의 임의의 점으로 반환한다
        return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0.0);
    }


    Color RayColor(const Ray& ray, int depth, const Hittable& world) const
    {
        // 깊이 한계를 초과하면 빛이 모이지 않는다는 가정하에 검은색으로 설정한다.
        if (depth <= 0) return Color(0.0, 0.0, 0.0);

        HitRecord hitRecord;

        if (world.Hit(ray, Interval(0.0, Infinity), hitRecord))
        {
            Vec3 direction = RandomOnHemisphere(hitRecord.Normal);
            return 0.5 * RayColor(Ray(hitRecord.Point, direction), depth - 1, world);
        }

        Vec3 unitDirection = UnitVector(ray.Direction());
        auto a = 0.5 * (unitDirection.Y() + 1.0);

        return (1.0 - a) * Color(1.0, 1.0, 1.0)
            + a * Color(0.5, 0.7, 1.0);
    }

private:
    double mPixelSamplesScale = 1.0;

    int mImageHeight = 0;        // Rendered image height
    Point3 mCenter;               // Camera center
    Point3 mPixel00Location;      // Location of pixel 0, 0
    Vec3 mPixelDeltaU;           // Offset to pixel to the right
    Vec3 mPixelDeltaV;           // Offset to pixel below
};