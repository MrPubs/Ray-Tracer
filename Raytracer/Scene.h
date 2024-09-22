

// Scene.h
#pragma once
#include <vector>
#include <opencv2.4/opencv2/opencv.hpp>
#include <variant>

#include "Rays.h"
#include "Geometry.h"
#include "Vectors.h"
#include "Lighting.h"
#include "Anti-Aliasing.h"

// Forward Declaration
class Scene;

// --~-- Declare Camera --~--
class Camera
{
public:

	// Constants
	const cv::Vec3b backgroundColor = cv::Vec3b(
		250, // B
		206, // G
		135  // R
	)*0.8f;

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
	std::vector<PrimaryRay> rays;
	AntiAliasing* aa_method;

	// Constructor
	Camera(int width, int height, float fov, Point3d location, Rotator3d rotation, Scene& scene, AntiAliasing* aa_method = nullptr);

	// Update Frame
	void updateFrame();
	void processRows(int startRow, int endRow, std::array<Ray::HitDataVector, 2> hits);

	// Post Process Frame
	void applyPP();
	
	// Calculate Image Distance
	void calculateImageDistance();

	// Calculate MVecs
	void SetRaysDirection();
};


// --~-- Declare Scene --~--
class Scene
{
public:

	// Attributes
	std::vector<GeomObj>& geomObjs; // All Present Geometric Objects
	std::vector<PointLight>& lightObjs; // All Present Light Objects
	float environmentLight_level = 0;

	// Constructor
	Scene(std::vector<GeomObj>& geomObjs, std::vector<PointLight>& lightObjs, float environmentLight_level = 0.2f);

	// Methods
	bool expand(const GeomObj& obj);
	bool expand(const PointLight& obj);

};


// --~-- Declare Viewport - Displays image --~--
class Viewport
{
public:

	// Variables
	Camera& camera;
	cv::Mat image;
	int frameno;
	int framerate;

	// Constructor
	Viewport(Camera& camera, int framerate);

	// Work - Live Session Loop
	void work();

	void checkInput();


};


