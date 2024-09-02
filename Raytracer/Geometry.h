
// Geometry.h
#pragma once

#include <array>
#include <vector>

// Forward Declaration
struct Rotator3d;

// --~-- Declare Vec3d --~--
struct Vec3d
{

	// Attributes
	float x, y, z;

	// Constructor
	Vec3d(float x, float y, float z);

	// Operators
	Vec3d operator+(const Vec3d& other) const;
	Vec3d operator-(const Vec3d& other) const;
	float operator*(const Vec3d& other) const;
	Vec3d operator*(float scale) const;

	// Methods
	Vec3d cross(const Vec3d& other) const;
	Vec3d rotate(const Rotator3d& rotator) const;
	float distanceTo(const Vec3d& other) const;
};


// --~-- Declare Point3d --~-- 
struct Point3d : public Vec3d
{	
	/*
	Future Proofing
	*/

	// Constructor
	Point3d(float x, float y, float z);

	// Operators
	Point3d operator=(const Vec3d& vec);

};


// --~-- Declare Rotator3d --~--
struct Rotator3d : public Vec3d
{

	// Attributes
	const float PI = 3.141592653589793f; // TODO: Fix cmath not recognizing the M_PI Identifier

	// Constructor
	Rotator3d(float roll, float pitch, float yaw);
	
	// Methods
	Rotator3d toRad();
	Rotator3d toDeg();

	// Helpers
	// Helper function for matrix multiplication
	std::array<std::array<float, 3>, 3> multiplyMatrices(const std::array<std::array<float, 3>, 3>& a, const std::array<std::array<float, 3>, 3>& b);
};


// --~-- Declare Triangle --~--
class Triangle
{
public:

	// Attributes
	std::array<Point3d, 3> vertices;
	Vec3d min_ext; // Extents
	Vec3d max_ext; // Extents
	Vec3d normal;
	float k; // Plane Constant
	
	// Constructor
	Triangle(std::array<Point3d, 3> vertices);

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
	Vec3d color;

	// Constructor
	GeomObj(std::vector<Triangle> members, Vec3d color={255,255,255});

	// Expand Object
	bool Expand(const std::vector<Triangle>& new_members);

};