
// Anti-Aliasing.h
#pragma once
#include "Vectors.h"

// Forward Declarations

// Declare Base AA Class
class AntiAliasing
{
public:

	virtual void foo() = 0; // Force polymorphic class

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
	Vec3d apply();
	Vec3d calculateSample(int sample_index); // Helper
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
