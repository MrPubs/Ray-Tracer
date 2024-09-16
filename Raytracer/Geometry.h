
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
	Material material;

	float k; // Plane Constant
	Vec3d normal;
	Vec3d min_ext, max_ext; // Extents

	// Constructor
	Triangle(std::array<Point3d, 3> vertices, Material material = Material({ 255, 0, 0 }));

	// Operators
	bool operator==(const Triangle& other) const;

	// Querying
	bool isInside(const Point3d& pt);
	bool sameSide(const Point3d& pt, int vertex_ind);

	// Methods
	void initialize();
	void setExtents();
	void setPlaneParams();

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