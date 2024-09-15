
// Lighting.h
#pragma once
#include "vectors.h"


// --~-- Declare PointLight --~--
class PointLight 
{
public:

	// Attributes 
	Point3d origin;
	Rotator3d rotation;
	float intensity;

	// Constructor
	PointLight(Point3d origin, Rotator3d rotation, float intensity);

	// Methods
	void setIntensity(const float intensity);
};