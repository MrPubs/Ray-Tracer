
// Rays.h
#pragma once
#include <opencv2.4/opencv2/opencv.hpp>
#include "Geometry.h"

// Forward Declarations
class Camera;

// Declare PrimaryRay
class PrimaryRay
{

public:

	// Attributes
	cv::Vec3b pixel;
	int iter;

	// Constructor
	PrimaryRay(cv::Vec3b pixel = { 0,0,0 });
	
	// Methods
	void cast(const int row,const int col, Camera& camera);

};

// Declare ShadowRay
class ShadowRay
{

	// Attributes

	// Constructor
	ShadowRay();

	// Methods
	void cast();

};