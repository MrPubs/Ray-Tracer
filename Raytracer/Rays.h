
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
class PointLight;

// Declare Base Ray Class
class Ray
{
public:

	// Datastructure Used for Communicating Hits Between Objects
	struct HitData {
		Triangle* triangle_ptr;
		Point3d hit_pt;
		float distance;

		HitData(Triangle* triangle_ptr, Point3d hit_pt, float distance);
	};
	using HitDataVector = std::vector<Ray::HitData>;

	// Attributes
	Scene& scene;
	Point3d origin;
	Vec3d direction;
	float max_ray_length;

	// Constructor
	Ray(Scene& scene, Point3d origin, Vec3d direction = Vec3d(0, 0, 0));

	// Methods
	bool cast(std::vector<Ray::HitData>& hits, Triangle* avoidTriangle = nullptr, bool quick = false);

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
	void castPrimary(const int row, const int col, std::array<Ray::HitDataVector, 2>& hitVectors, Camera& camera);

};

// Declare ShadowRay
class ShadowRay : public Ray
{

public:

	// Constructor
	ShadowRay(Scene& scene, Point3d origin, Vec3d direction);

	// Methods
	float castShadow(Ray::HitDataVector& shadowHits, Triangle* originTriangle_ptr);

};