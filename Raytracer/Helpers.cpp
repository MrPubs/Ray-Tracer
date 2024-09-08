

// Helpers.cpp
#include "Geometry.h"

// Fallen, tip away from camera
GeomObj MakeFallenPyramid(Point3d center, float baseLength, float height) {
    // Half the base length to position the base points relative to the center
    float halfBase = baseLength / 2.0f;

    // Define the base points relative to the center
    Point3d base1(center.x - halfBase, center.y - halfBase, center.z);
    Point3d base2(center.x + halfBase, center.y - halfBase, center.z);
    Point3d base3(center.x + halfBase, center.y + halfBase, center.z);
    Point3d base4(center.x - halfBase, center.y + halfBase, center.z);

    // Define the apex point above the center of the base
    Point3d apex(center.x, center.y, center.z + height);

    // Create the geometry object for the pyramid
    GeomObj pyramid({
        Triangle({ base1, base2, apex }),                          // Side 1
        Triangle({ base2, base3, apex }, Material({0,255,0})),     // Side 2
        Triangle({ base3, base4, apex }, Material({0,0,255})),     // Side 3
        Triangle({ base4, base1, apex }, Material({155,0,155})),   // Side 4
        });

    pyramid.origin = center;
    return pyramid;
}
