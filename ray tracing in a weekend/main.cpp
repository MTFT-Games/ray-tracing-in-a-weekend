#include <iostream>

#include "Color.h"
#include "Vec3.h"
#include "Ray.h"

// Blend from white to blue on elevation of ray
Color RayColor(const Ray& ray) {
    Vec3 unitVector = UnitVector(ray.Direction());
    double scaledY = 0.5 * (unitVector.y() + 1.0);
    // Scale from white to blue based on y
    return (1.0 - scaledY) * Color(1.0, 1.0, 1.0) + scaledY * Color(0.5, 0.7, 1.0);
}

// TODO: Re-style everythign to preference that was copied from the book 
int main() {

    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    // Calculate height from aspect and ensure its at least 1
    int imageHeight = imageWidth / aspectRatio;
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Camera
    double focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * ((double)imageWidth / imageHeight);
    Point3 cameraCenter = Point3();

    Vec3 viewportU = Vec3(viewportWidth, 0, 0);
    Vec3 viewportV = Vec3(0, -viewportHeight, 0);

    Vec3 pixelDeltaU = viewportU / imageWidth;
    Vec3 pixelDeltaV = viewportV / imageHeight;

    Vec3 viewportUpperLeft = 
        cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    Vec3 firstPixelPos = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Render

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

            Color pixelColor = RayColor(ray);

            WriteColor(std::cout, pixelColor);
        }
    }

    // Extra spaces to blank out last progress msg
	std::clog << "\rDone.                           \n";
}
