
// Rays.h
#pragma once
#include <opencv2.4/opencv2/opencv.hpp>
#include "Geometry.h"

// Forward Declarations
class Camera;

// Declare Rays
class Ray
{

public:

	// Attributes
	cv::Vec3b pixel;
	int iter;

	// Cons & Dest
	Ray(cv::Vec3b pixel = { 0,0,0 });
	
	// Methods
	bool castRay(const int row,const int col, Camera& camera);

};