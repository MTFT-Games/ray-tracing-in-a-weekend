#pragma once

#include "utility.h"
#include "Color.h"
#include "Hittable.h"

class Camera {
public:
    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
	
	void Render(const Hittable& world) {
        Initialize();

        // PPM header: ASCII, image size, max value
        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int y = 0; y < imageHeight; ++y) {
            // Progress updates as this will take a while later. Goes to log stream not stdout
            // \r goes to line start without entering a new line, overwriting the last update
            std::clog << "\rScanlines remaining: " << (imageHeight - y) << ' ' << std::flush;
            for (int x = 0; x < imageWidth; ++x) {
                // Calculate and launch ray
                Vec3 pixelCenter = firstPixelPos + (x * pixelDeltaU) + (y * pixelDeltaV);
                Vec3 rayDirection = pixelCenter - cameraCenter;
                Ray ray(cameraCenter, rayDirection);

                Color pixelColor = RayColor(ray, world);

                WriteColor(std::cout, pixelColor);
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

    // Calculate color of first hit or sky
    Color RayColor(const Ray& ray, const Hittable& world) const {
        HitRecord record;
        if (world.Hit(ray, Interval(0, infinity), record)) {
            return 0.5 * (record.normal + Color(1, 1, 1));
        }

        // Miss to skybox
        Vec3 unitVector = UnitVector(ray.Direction());
        double scaledY = 0.5 * (unitVector.y() + 1.0);
        // Scale from white to blue based on y
        return (1.0 - scaledY) * Color(1.0, 1.0, 1.0) + scaledY * Color(0.5, 0.7, 1.0);
    }
};