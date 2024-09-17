
// Main.cpp
#include <iostream>
#include <vector>

#include "Scene.h"
#include "Geometry.h"
#include "Helpers.h"
#include "Lighting.h"

// Helpers
//#include "Helpers.h"

int main()
{

    // Parameters
    const float aspect_ratio = 16 / 9.0f;
    const int width = 640;
    const int height = width/aspect_ratio;
    const int framerate = 24;
    const int fov = 90;

    // Set up Scene
    std::vector<GeomObj> geomObjs;
    std::vector<PointLight> lightObjs;
    Scene scene(geomObjs, lightObjs);
   
    // Expand Scene
    GeomObj gob1 = MakeFallenPyramid(Point3d(0, 0, 10), 4, 2);
    gob1.setRotation(Rotator3d(0, 180, 0));
    PointLight plob1(Point3d(0, 0, 0), Rotator3d(0, 0, 0), 20, 20);
    scene.expand(gob1);
    scene.expand(plob1);

    // Set Up Camera
    Point3d location(0, 0, 0);
    Rotator3d rotation(0, 0, 0);
    Camera camera(width, height, fov, location, rotation, scene);

    // Set up Viewport
    Viewport viewport(camera);
    viewport.work();

}