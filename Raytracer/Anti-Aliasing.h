
// Anti-Aliasing.h
#pragma once
#include <array>

#include "Vectors.h"
#include "Rays.h"

// Forward Declarations
class Camera;

// Declare Base AA Class
class AntiAliasing
{
public:

	virtual void foo() = 0; // Force polymorphic class

	// Parameters
	Camera* camera_ptr;

	// Sampling Lookup Tables
	// 2x2 Grid
	std::array<cv::Vec2d, 4> SampleCoords2By2Grid = {{
		cv::Vec2d(0.0025, 0.0025),
		cv::Vec2d(-0.0025, 0.0025),
		cv::Vec2d(0.0025, -0.0025),
		cv::Vec2d(-0.0025, -0.0025)
	} };


};

// Declare MSAA AntiAliasing
class MSAA : public AntiAliasing
{
public:

	void foo() override; // Force polymorphic class

	// Parameters
	int sample_count;

	// Constructor
	MSAA(int sample_count = 4);

	// Methods
	Vec3d apply(int row, int col);
	Vec3d calculateSample(int index, Vec3d& direction, std::array<Ray::HitDataVector, 2>& HitVectors, int row, int col); // Helper
	Vec3d getSampleDirection(const Vec3d& former_direction, const int& sample_index); // Helper
	bool isEdge(int pixel_index);
	bool assessPixels(Camera* camera_ptr, int main_index, int neighbor_index, float depth_threshold, float normal_threshold, float color_threshold);
};


// Declare FXAA AntiAliasing
class FXAA : public AntiAliasing
{
public:

	void foo() override; // Force polymorphic class

	// Parameters

	// Constructor
	FXAA();

	// Methods
	void apply();
};
