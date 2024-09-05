

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

	// Attributes
	Point3d location;
	Rotator3d rotation;

	int width, height, framerate;
	int frametime; // in ms

	Scene& scene;
	std::vector<cv::Vec3b> frame;
	std::vector<float> zbuffer;
	std::vector<Vec3d> mvecs;

	std::vector<Ray> rays;

	// Constructor
	Camera(Point3d location, Rotator3d, Scene& scene, int width, int height, int framerate);

	// Update Frame
	void updateFrame();

	// Post Process Frame
	void applyPP();

	// calculateMVecs
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


