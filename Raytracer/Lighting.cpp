
// Lighting.cpp
#include "Lighting.h"


// --~-- Implement PointLight --~--
	
	// Construct
	PointLight::PointLight(Point3d origin, Rotator3d rotation, float intensity) :
		origin(origin),
		rotation(rotation),
		intensity(intensity)
	{

	}

	// Methods
	void PointLight::setIntensity(const float intensity)
	{

		this->intensity = intensity;
	}