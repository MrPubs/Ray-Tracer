
// Anti-Aliasing.cpp
#include <iostream>

#include "Anti-Aliasing.h"
#include "Vectors.h"

// Implement MSAA Real-time AA	

	void MSAA::foo() {} // Force polymorphic class

	MSAA::MSAA(int sample_count):
		sample_count(sample_count)
	{
		
		// Initialize Result vector

	}

	Vec3d MSAA::apply()
	{

		Vec3d result(0, 0, 0);
		for (int sample_index = 0; sample_index < sample_count; sample_index++)
		{

			// 1. Detect Edges - bonus
			// ??

			// 2. Trace Rays to Sample Locations
			result += calculateSample(sample_index);

		}

		result /= sample_count;
		return result;

	}
	Vec3d MSAA::calculateSample(int sample_index)
	{

		// Get Variation of main Ray
		
		// Cast Ray

		// Average

		return Vec3d(255, 255, 255);
	} // Helper

// Implement FXAA Post-process AA

	void FXAA::foo() {} // Force polymorphic class

	FXAA::FXAA()
	{

	}

	void FXAA::apply()
	{

		//std::cout << "FXAA!" << std::endl;
	}

