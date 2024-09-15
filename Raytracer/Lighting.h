
// Lighting.h
#pragma once
#include "vectors.h"


// --~-- Declare PointLight --~--
class PointLight 
{
public:

	// Attributes 
	Point3d location;
	Rotator3d rotation;
	float intensity;
	float range;

	// Constructor
	PointLight(Point3d location, Rotator3d rotation, float intensity, float range);

	// Methods
	void setIntensity(const float intensity);
	void setRange(const float range);
};