
// Anti-Aliasing.cpp
#include <iostream>
#include <Vector>

#include "Anti-Aliasing.h"
#include "Vectors.h"

// Implement MSAA Real-time AA
	
	MSAA::MSAA(int sample_count):
		sample_count(sample_count)
	{
		
		
	}

	void MSAA::apply()
	{

		result.clear();

		// Work Per Sample
		for (int sample_i = 0; sample_i < sample_count; sample_i++)
		{

			// Implement Sample

			// Populate Results
			float R = 0, G = 0, B = 0;
			result.emplace_back(Vec3d(R, G, B));
		}

		//return result;
	}

// Implement FXAA Post-process AA

	FXAA::FXAA()
	{

	}

	void FXAA::apply()
	{

		//std::cout << "Applying FXAA.." << std::endl;
	}

