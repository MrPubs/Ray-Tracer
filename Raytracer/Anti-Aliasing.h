
// Anti-Aliasing.h
#pragma once

// Forward Declarations

// Declare Base AA Class
class AntiAliasing
{
public:

	virtual void apply() = 0;
	std::vector<Vec3d()> result;

};

// Declare MSAA AntiAliasing
class MSAA : public AntiAliasing
{
public:

	// Parameters
	int sample_count;

	// Constructor
	MSAA(int sample_count = 4);

	// Methods
	void apply() override;


};


// Declare FXAA AntiAliasing
class FXAA : public AntiAliasing
{
public:

	// Parameters

	// Constructor
	FXAA();

	// Methods
	void apply() override;
};
