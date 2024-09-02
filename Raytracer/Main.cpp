
// Main.cpp
#include <iostream>
#include <vector>
#include "Scene.h"
#include "Geometry.h"

int main()
{

    // Controls
    int width = 601;
    int height = 301;
    int framerate = 24;
    int fov = 90;

    // Set up Camera
    Camera camera = Camera(Point3d(0,0,0), Rotator3d(0,0,0), width=width, height=height, framerate=framerate, fov=fov);

    // Set up Scene
    std::vector<GeomObj> geomObjs; // to populate
    Scene scene = Scene(camera, geomObjs);

    //// --~-- Example for Definition of Triangles, Geometry objects, And expansion of Geometry Objects --~--
    //Triangle tri1({ Point3d(1,1,1), Point3d(2,2,2), Point3d(3,3,3) });
    //Triangle tri2({ Point3d(10,10,10), Point3d(20,20,20), Point3d(30,30,30) });
    //GeomObj gob1({ tri1 });
    //gob1.Expand({ tri2 });
  
    //GeomObj gob1({ Triangle({ Point3d(-15,-15,0.5f), Point3d(15,-15,0.5f), Point3d(0,45,0.5f) }) });
    //GeomObj gob1({ Triangle({ Point3d(45,-15,0.5f), Point3d(15,-15,0.5f), Point3d(30,-45,0.5f) }) });
     
    GeomObj gob1({ Triangle({ Point3d(-90,-90,5), Point3d(90,-90,5), Point3d(0,270,5) }) });
    gob1.Expand({ Triangle({ Point3d(90,90,5), Point3d(270,90, 5), Point3d(180,-270,3) }) });
    gob1.Expand({ Triangle({ Point3d(-90,-120,5), Point3d(-150,-120,5), Point3d(-120,-360,5) }) });
    gob1.Expand({ Triangle({ Point3d(-150,-60,3), Point3d(-210,-60,3), Point3d(-180,-360,2) }) });
    gob1.Expand({ Triangle({ Point3d(-210,-120,5), Point3d(-500,-120,5), Point3d(-350,-500,10) }) });

    // --~-- Example for Expansion of Scene GeoObjs --~--
    //scene.expand(gob1);
    scene.expand(gob1);

    // Set up Viewport
    Viewport viewport = Viewport(width, height, scene);
    viewport.work();
    std::cout << "Done!" << std::endl;

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