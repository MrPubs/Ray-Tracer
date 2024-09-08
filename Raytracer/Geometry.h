
// Geometry.h
#pragma once

#include <array>
#include <vector>
#include "Vectors.h"
#include "Materials.h"

// --~-- Declare Triangle --~--
class Triangle
{
public:
	
	// Attributes
	std::array<Point3d, 3> vertices;
	Vec3d min_ext, max_ext; // Extents
	Vec3d normal;
	float k; // Plane Constant
	Material material;

	// Constructor
	Triangle(std::array<Point3d, 3> vertices, Material material = Material({ 255, 0, 0 }));

	//// Methods
	bool isIntersecting(const Point3d& pt);
	void setExtents();
	bool isInside(const Point3d& pt);

	// Helpers
	bool sameSide(const Point3d& pt, int vertex_ind);
};


// --~-- Declare GeomObj --~--
class GeomObj
{
public:

	// Attributes
	std::vector<Triangle> members;
	Point3d origin;
	Rotator3d rotation;

	// Constructor
	GeomObj(std::vector<Triangle> members);

	// Methods
	bool Expand(const std::vector<Triangle>& new_members); // Expand GeomObj	
	void setRotation(const Rotator3d& new_rotation);
};