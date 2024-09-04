

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
	//std::vector<Ray> rays;
	//std::vector<float> zbuffer;
	//std::vector<Vec3d> mvecs;

	//int framerate, fov;
	//int width, height;
	//double frametime;
	//

	//Point3d location;
	//Rotator3d rotation;

	//// Constructor
	//Camera(Point3d location, Rotator3d rotation, int w, int h, int framerate = 24, int fov = 90);
	
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
};


// --~-- Declare Scene --~--
class Scene
{
public:

	// Attributes
	//Camera& camera; // POV
	//std::vector<GeomObj>& geomObjs; // All Present Game Objects

	//// Constructor
	//Scene(Camera& camera, std::vector<GeomObj>& geomObjs);

	//// Add GeomObj to geomObjs
	//bool expand(const GeomObj& obj);

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

	// Attributes
	//int width, height, frameno, framerate;
	//double frametime;

	//Scene& scene;
	//std::vector<cv::Vec3b> frame;
	//cv::Mat image;

	//// Constructor
	//Viewport(int w, int h, Scene& scene);

	//// Refresh Viewport
	//bool refreshVP();

	//// Session Loop
	//bool work();

	//// Close Viewport
	//bool closeVP();


	// Variables
	Camera& camera;
	cv::Mat image;
	int frameno;

	// Constructor
	Viewport(Camera& camera);

	// Work - Live Session Loop
	void work();


};


