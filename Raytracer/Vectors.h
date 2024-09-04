

// Vectors.h
#pragma once

#include <array>

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
	Vec3d rotate(const Vec3d origin, const Rotator3d& rotator) const;
	float distanceTo(const Vec3d& other) const;
};

using Point3d = Vec3d;
using ColorRGB = Vec3d;

//// --~-- Declare Point3d --~-- 
//struct Point3d : public Vec3d
//{
//	/*
//	Future Proofing
//	*/
//
//	// Constructor
//	Point3d(float x, float y, float z);
//
//	// Operators
//	Point3d operator=(const Vec3d& vec);
//
//};


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
	// Helper function for matrix mul - 3x3 matrices only
	std::array<std::array<float, 3>, 3> multiplyMatrices(const std::array<std::array<float, 3>, 3>& a, const std::array<std::array<float, 3>, 3>& b);
};
