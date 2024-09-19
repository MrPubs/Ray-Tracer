
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
    const int height = width / aspect_ratio;
    const int framerate = 0;
    const int fov = 90;
    const float environmentLight_level = 0.2f;

    // Set up Scene
    std::vector<GeomObj> geomObjs;
    std::vector<PointLight> lightObjs;
    Scene scene(geomObjs, lightObjs, environmentLight_level);

    // Expand Scene
    GeomObj gob1 = MakeFallenPyramid(Point3d(-6, 0, 10), 4, 2);
    gob1.setRotation(Rotator3d(0, 180, 0));
    GeomObj gob2 = MakeFallenPyramid(Point3d(0, 0, 10), 4, 2);
    gob2.setRotation(Rotator3d(0, 180, 0));
    GeomObj gob3 = MakeFallenPyramid(Point3d(6, 0, 10), 4, 2);
    gob3.setRotation(Rotator3d(0, 180, 0));
    //GeomObj gob4({Triangle({ Point3d(-10,-6,20), Point3d(0,6,20), Point3d(10,-6,20) }, Material({ 255, 255, 255 }))});
    scene.expand(gob1), scene.expand(gob2), scene.expand(gob3);
    //scene.expand(gob4);

    PointLight plob1(Point3d(-6, 0, 10), Rotator3d(0, 0, 0), 20, 50);
    scene.expand(plob1);
    PointLight plob2(Point3d(0, 0, 10), Rotator3d(0, 0, 0), 20, 50);
    scene.expand(plob2);
    PointLight plob3(Point3d(6, 0, 10), Rotator3d(0, 0, 0), 20, 50);
    scene.expand(plob3);


    // Set Up Camera
    Point3d location(0, 0, 0);
    Rotator3d rotation(0, 0, 0);
    Camera camera(width, height, fov, location, rotation, scene);

    // Set up Viewport
    Viewport viewport(camera, framerate);
    viewport.work();
    
}