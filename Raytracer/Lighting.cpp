
// Lighting.cpp
#include "Lighting.h"


// --~-- Implement PointLight --~--
	
	// Construct
	PointLight::PointLight(Point3d location, Rotator3d rotation, float intensity, float range) :
		location(location),
		rotation(rotation),
		intensity(intensity),
		range(range)
	{

	}

	// Methods
	void PointLight::setIntensity(const float intensity)
	{

		this->intensity = intensity;
	}
	void PointLight::setRange(const float range)
	{

		this->range = range;
	}