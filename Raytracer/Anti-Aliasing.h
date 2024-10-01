
// Anti-Aliasing.h
#pragma once
#include "Vectors.h"

// Forward Declarations
class Camera;

// Declare Base AA Class
class AntiAliasing
{
public:

	virtual void foo() = 0; // Force polymorphic class

	// Parameters
	Camera* camera_ptr;


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
	Vec3d calculateSample(); // Helper
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
