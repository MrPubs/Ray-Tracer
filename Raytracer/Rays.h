
// Rays.h
#pragma once
#include <opencv2.4/opencv2/opencv.hpp>
#include "Geometry.h"

// Forward Declarations
class Scene;

// Declare Rays
class Ray
{

public:

	// Attributes
	cv::Vec3b pixel;
	Vec3d m_vec;
	int iter;

	// Cons & Dest
	Ray(cv::Vec3b pixel = { 0,0,0 }, Vec3d m_vec = {0,0,1});
	
	// Methods
	bool castRay(const int row,const int col, const Scene& scene);

};