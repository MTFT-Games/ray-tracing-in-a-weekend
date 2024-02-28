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
void WriteColor(std::ostream& out, Color pixelColor) {
    out << static_cast<int>(255.999 * pixelColor.x()) << ' '
        << static_cast<int>(255.999 * pixelColor.y()) << ' '
        << static_cast<int>(255.999 * pixelColor.z()) << '\n';
}
