
// Main.cpp
#include <iostream>
#include <vector>

#include "Scene.h"
#include "Geometry.h"
#include "Helpers.h"
// Helpers
//#include "Helpers.h"

int main()
{

    // Controls
    const int width = 300;
    const int height = 300;
    const int framerate = 24;

    // Set up Scene
    std::vector<GeomObj> geomObjs;
    Scene scene(geomObjs);
   
    GeomObj gob1 = MakeFallenPyramid(Point3d(0, 0, 3), 4, -2);
    scene.expand(gob1);

    // Set Up Camera
    Point3d location(0, 0, 0);
    Rotator3d rotation(0, 0, 0);
    Camera camera(location, rotation, scene, width, height, framerate);
 

    // Set up Viewport
    Viewport viewport(camera);
    viewport.work();

}