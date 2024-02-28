#include <iostream>

#include "Color.h"
#include "Vec3.h"

// TODO: Re-style everythign to preference that was copied from the book 
int main() {

    // Image

    int imageWidth = 256;
    int imageHeight = 256;

    // Render

    // PPM header: ASCII, image size, max value
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int y = 0; y < imageHeight; ++y) {
        // Progress updates as this will take a while later. Goes to log stream not stdout
        // \r goes to line start without entering a new line, overwriting the last update
		std::clog << "\rScanlines remaining: " << (imageHeight - y) << ' ' << std::flush;
        for (int x = 0; x < imageWidth; ++x) {
            // For now just test with a green to red gradient, bot left to top right
            Color pixelColor = Color(
                double(x) / (imageWidth - 1), 
                double(y) / (imageHeight - 1),
                0);

            WriteColor(std::cout, pixelColor);
        }
    }

    // Extra spaces to blank out last progress msg
	std::clog << "\rDone.                           \n";
}
