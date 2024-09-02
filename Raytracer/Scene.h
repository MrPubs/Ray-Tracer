
// Scene.h
#pragma once
#include <vector>
#include <opencv2.4/opencv2/opencv.hpp>

#include "Rays.h"
#include "Geometry.h"

// --~-- Declare Camera - Serves as a Window to the Scene --~--
class Camera
{
public:

	// Attributes
	std::vector<Ray> rays;
	std::vector<Ray> zbuff;
	int framerate, fov;
	double frametime;
	Point3d location;
	Rotator3d rotation;

	// Constructor
	Camera(Point3d location, Rotator3d rotation, int w, int h, int framerate = 24, int fov = 90);

};


// --~-- Declare Scene - Contains Every Geometry, Camera and Light Source. Viewport References this for getting data --~--
class Scene
{
public:

	// Attributes
	Camera& camera; // POV
	std::vector<GeomObj>& geomObjs; // All Present Game Objects

	// Constructor
	Scene(Camera& camera, std::vector<GeomObj>& geomObjs);

	// Add GeomObj to geomObjs
	bool expand(const GeomObj& obj);
};


// --~-- Declare Viewport - Displays the Window --~--
class Viewport
{
public:

	// Attributes
	int width, height, frameno, framerate;
	double frametime;

	Scene& scene;
	std::vector<cv::Vec3b> frame;
	cv::Mat image;

	// Constructor
	Viewport(int w, int h, Scene& scene);

	// Refresh Viewport
	bool refreshVP();

	// Session Loop
	bool work();

	// Close Viewport
	bool closeVP();
};


