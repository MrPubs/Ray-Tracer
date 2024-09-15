
// Rays.h
#pragma once

#include <vector>
#include <tuple>
#include <opencv2.4/opencv2/opencv.hpp>

#include "Geometry.h"

// Forward Declarations
class Camera;
class Scene;
class ShadowRay;

class Ray
{
public:

	struct HitData {
		Triangle triangle;
		Point3d hit_pt;
		float distance;

		HitData(Triangle triangle, Point3d hit_pt, float distance);
	};

	// Attributes
	Scene& scene;
	Point3d origin;
	Vec3d direction;

	// Constructor
	Ray(Scene& scene, Point3d origin, Vec3d direction = Vec3d(0, 0, 0));

	// Methods
	void cast(Camera& camera, bool quick = false);

};

// Declare PrimaryRay
class PrimaryRay : public Ray
{

public:

	// Attributes
	cv::Vec3b pixel;
	std::vector<ShadowRay> shadowRays;

	// Constructor
	PrimaryRay(Scene& scene, Point3d origin, Vec3d direction = Vec3d(0, 0, 0), cv::Vec3b pixel = { 0,0,0 });
	
	// Methods
	void castPrimary(const int row,const int col, Camera& camera);

};

// Declare ShadowRay
class ShadowRay
{

public:
	// Attributes
	Point3d origin;

	// Constructor
	ShadowRay(Scene& scene);

	// Methods
	void cast();

};