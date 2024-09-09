

// Scene.h
#pragma once
#include <vector>
#include <opencv2.4/opencv2/opencv.hpp>

#include "Rays.h"
#include "Geometry.h"
#include "Vectors.h"

// Forward Declaration
class Scene;

// --~-- Declare Camera --~--
class Camera
{
public:

	// Perspective
	int width, height;
	float fov, img_d;

	// Transform
	Point3d location;
	Rotator3d rotation;

	// Frame
	Scene& scene;
	std::vector<cv::Vec3b> frame;
	std::vector<float> zbuffer;
	std::vector<Vec3d> mvecs;
	std::vector<Ray> rays;

	// Constructor
	Camera(int width, int height, float fov, Point3d location, Rotator3d rotation, Scene& scene);

	// Update Frame
	void updateFrame();

	// Post Process Frame
	void applyPP();
	
	// Calculate Image Distance
	void calculateImageDistance();

	// Calculate MVecs
	void calculateMVecs();
};


// --~-- Declare Scene --~--
class Scene
{
public:

	// Attributes
	std::vector<GeomObj>& geomObjs; // All Present Geometric Objects
	  // Light Sources

	// Constructor
	Scene(std::vector<GeomObj>& geomObjs);

	// Methods
	bool expand(const GeomObj& obj);
};


// --~-- Declare Viewport - Displays image --~--
class Viewport
{
public:

	// Variables
	Camera& camera;
	cv::Mat image;
	int frameno;

	// Constructor
	Viewport(Camera& camera);

	// Work - Live Session Loop
	void work();

	void checkInput();


};


