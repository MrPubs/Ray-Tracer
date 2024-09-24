
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
	bool isEdge(int pixel_index);
	Vec3d calculateSample(); // Helper
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
