
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
    GeomObj gob1 = MakeFallenPyramid(Point3d(15000, 0, 100), 12500, -40);
    GeomObj gob2 = MakeFallenPyramid(Point3d(-15000, 0, 100), 12500, -40);
    GeomObj gob3 = MakeFallenPyramid(Point3d(0, 5000, 50), 2500, 80);
    scene.expand(gob1);
    scene.expand(gob2);
    scene.expand(gob3);


    // Set Up Camera
    Point3d location(0, 0, 0);
    Rotator3d rotation(0, 0, 0);
    Camera camera(location, rotation, scene, width, height, framerate);
    

    // Set up Viewport
    Viewport viewport(camera);
    viewport.work();

    //// --~-- Example for Definition of Triangles, Geometry objects, And expansion of Geometry Objects --~--
    //Triangle tri1({ Point3d(1,1,1), Point3d(2,2,2), Point3d(3,3,3) });
    //Triangle tri2({ Point3d(10,10,10), Point3d(20,20,20), Point3d(30,30,30) });
    //GeomObj gob1({ tri1 });
    //gob1.Expand({ tri2 });
     
    
    // Triangle Collection
    //GeomObj gob1({ Triangle({ Point3d(-900,-900,100), Point3d(900,-900,100), Point3d(0,2700,50) }) });
    //gob1.Expand({ Triangle({ Point3d(900,900,50), Point3d(2700,900, 50), Point3d(1800,-2700,100) }) });
    //gob1.Expand({ Triangle({ Point3d(-900,-1200,80), Point3d(-1500,-1200,50), Point3d(-1200,-3600,100) }) });
    //gob1.Expand({ Triangle({ Point3d(-1500,-1800,100), Point3d(-3000,0,20), Point3d(-8000,-6000,150) }) });
    //gob1.Expand({ Triangle({ Point3d(-2100,-1200,100), Point3d(-5000,-1200,100), Point3d(-3500,-5000,50) }) });
    //scene.expand(gob1);

    // 1. Initialize the Screen
    // Define the screen dimensions and other necessary settings (e.g., resolution).

    // 2. Set Up the Camera
    // Define the camera position, orientation, and projection details.

    // 3. Prepare the Scene
    // Load or define objects, lights, and materials in the scene.

    // 4. Shoot Rays from Pixels on Screen
    // Loop over each pixel on the screen:
    //   - For each pixel, generate a ray from the camera through the pixel.
    //   - Trace the ray to determine its interaction with objects in the scene.

    // 5. Return Information from All Rays
    //   - Compute the color of each pixel based on the ray-object interactions.
    //   - Consider shading, shadows, reflections, and other effects.

    // 6. Display Returned Information to Create a Frame
    //   - Write the computed pixel colors to an image buffer or file.
    //   - Display or save the final rendered frame.


}