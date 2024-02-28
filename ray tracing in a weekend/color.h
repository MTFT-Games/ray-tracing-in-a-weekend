#pragma once

#include "Vec3.h"

#include <iostream>

// Alias
using Color = Vec3;

/// <summary>
/// Writes a given color to a stream as three space seperated 0-255 values 
/// (r, g, b) followed by a newline.
/// </summary>
/// <param name="out">The stream to write to.</param>
/// <param name="pixelColor">A color to output.</param>
void WriteColor(std::ostream& out, Color pixelColor, int samples) {
    double r = pixelColor.x() / samples;
    double g = pixelColor.y() / samples;
    double b = pixelColor.z() / samples;

    static const Interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.Clamp(r)) << ' '
        << static_cast<int>(256 * intensity.Clamp(g)) << ' '
        << static_cast<int>(256 * intensity.Clamp(b)) << '\n';
}
