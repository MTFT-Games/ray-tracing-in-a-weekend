#include <iostream>

#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"

// TODO: Re-style everythign to preference that was copied from the book 
int main() {
    // World
    HittableList world;
    world.Add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera camera;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 1000;
    camera.maxDepth = 50;

    // Render
    camera.Render(world);
}
