
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
    const int width = 601;
    const int height = 301;
    const int framerate = 24;

    // Set up Scene
    std::vector<GeomObj> geomObjs;
    Scene scene(geomObjs);
    
    // Pyramids
    //GeomObj gob1 = MakeFallenPyramid(Point3d(500, 0, 5), 500, -2);
    //GeomObj gob2 = MakeFallenPyramid(Point3d(-500, 0, 20), 2000, -10);
    //GeomObj gob3 = MakeFallenPyramid(Point3d(0, 500, 10), 500, 25);
    //scene.expand(gob1);
    //scene.expand(gob2);
    //scene.expand(gob3);

    GeomObj gob1 = MakeFallenPyramid(Point3d(0, 0, 3), 250, -2);
    scene.expand(gob1);

    // Set Up Camera
    Point3d location(0, 0, 0);
    Rotator3d rotation(0, 0, 0);
    Camera camera(location, rotation, scene, width, height, framerate);
 

    // Set up Viewport
    Viewport viewport(camera);
    viewport.work();

}