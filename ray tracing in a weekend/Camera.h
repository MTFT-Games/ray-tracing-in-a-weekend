#pragma once

#include "utility.h"
#include "Color.h"
#include "Hittable.h"

class Camera {
public:
    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int samplesPerPixel = 1;
    int maxDepth = 10;
	
	void Render(const Hittable& world) {
        Initialize();

        // PPM header: ASCII, image size, max value
        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int y = 0; y < imageHeight; ++y) {
            // Progress updates as this will take a while later. Goes to log stream not stdout
            // \r goes to line start without entering a new line, overwriting the last update
            std::clog << "\rScanlines remaining: " << (imageHeight - y) << ' ' << std::flush;
            for (int x = 0; x < imageWidth; ++x) {
                // Calculate and launch rays
                Color pixelColor(0,0,0);
                for (size_t sample = 0; sample < samplesPerPixel; sample++)
                {
                    Ray ray = GetRay(x, y);
                    pixelColor += RayColor(ray, maxDepth, world);
                }

                WriteColor(std::cout, pixelColor, samplesPerPixel);
            }
        }

        // Extra spaces to blank out last progress msg
        std::clog << "\rDone.                           \n";
	}

private:
    int imageHeight;
    Point3 cameraCenter;
    Vec3 firstPixelPos;
    Vec3 pixelDeltaU;
    Vec3 pixelDeltaV;

	void Initialize() {
        // Calculate height from aspect and ensure its at least 1
        imageHeight = imageWidth / aspectRatio;
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        cameraCenter = Point3();

        double focalLength = 1.0;
        double viewportHeight = 2.0;
        double viewportWidth = viewportHeight * ((double)imageWidth / imageHeight);

        Vec3 viewportU = Vec3(viewportWidth, 0, 0);
        Vec3 viewportV = Vec3(0, -viewportHeight, 0);

        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        Vec3 viewportUpperLeft =
            cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
        firstPixelPos = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
	}

    // Get a randomly sampled camera ray for the pixel
    Ray GetRay(int x, int y) const {
        Vec3 pixelCenter = firstPixelPos + (x * pixelDeltaU) + (y * pixelDeltaV);
        Vec3 pixelSample = pixelCenter + PixelDeviance();

        Vec3 rayDirection = pixelSample - cameraCenter;

        return Ray(cameraCenter, rayDirection);
    }

    Vec3 PixelDeviance() const {
        double xDelta = -0.5 + RandomDouble();
        double yDelta = -0.5 + RandomDouble();
        return (xDelta * pixelDeltaU) + (yDelta * pixelDeltaV);
    }

    // Calculate color of first hit or sky
    Color RayColor(const Ray& ray, int depth, const Hittable& world) const {
        HitRecord record;
        if (depth <= 0)
        {
            return Color();
        }

        if (world.Hit(ray, Interval(0.001, infinity), record)) {
            Vec3 direction = record.normal + RandomUnitVector();
            return 0.5 * RayColor(Ray(record.position, direction), depth-1, world);    //normal test 0.5* (record.normal + Color(1, 1, 1));
        }

        // Miss to skybox
        Vec3 unitVector = UnitVector(ray.Direction());
        double scaledY = 0.5 * (unitVector.y() + 1.0);
        // Scale from white to blue based on y
        return (1.0 - scaledY) * Color(1.0, 1.0, 1.0) + scaledY * Color(0.5, 0.7, 1.0);
    }
};