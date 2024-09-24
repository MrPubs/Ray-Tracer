
// Anti-Aliasing.cpp
#include <iostream>
#include <array>

#include "Anti-Aliasing.h"
#include "Vectors.h"
#include "Scene.h"
#include "Rays.h"

// Forward Declarations
class Ray;

// Implement MSAA Real-time AA	

	void MSAA::foo() {} // Force polymorphic class

	MSAA::MSAA(int sample_count) :
		sample_count(sample_count)
	{

	}

	Vec3d MSAA::apply(int row, int col)
	{

		int pixel_index = row * camera_ptr->width + col;

		// 1. Detect Edges
		if (isEdge(pixel_index));
		{

			// 2. Trace Rays to Sample Locations
			Vec3d result(0, 0, 0);
			for (int sample_index = 0; sample_index < sample_count; sample_index++)
			{

				result += calculateSample();
			}

			// Average
			result /= sample_count;
			return result;
		}
	}

	bool MSAA::isEdge(int pixel_index)
	{

		bool flag = true;
		Camera& camera_ref = *this->camera_ptr;
		// depth detection
		// color detection
		// normal detection
		
		// Left neighbor
		if (pixel_index % camera_ref.width != 0)
		{

			int left_index = pixel_index - 1;
			//camera_ref.frame[];
			//camera_ref.zbuffer[];
			//camera_ref.nbuffer[];
		}

		// Right neighbor
		if ((pixel_index + 1) % camera_ref.width != 0)
		{

			int right_index = pixel_index + 1;
		}

		// Up neighbor
		if (pixel_index - camera_ref.width >= 0)
		{

			int up_index = pixel_index - camera_ref.width;
		}

		// Down neighbor
		if (pixel_index + camera_ref.width < camera_ref.width * camera_ref.height)
		{

			int down_index = pixel_index + camera_ref.width;
		}

		return true;
	}

	Vec3d MSAA::calculateSample()
	{

		// sample result
		Vec3d sample_result(0, 0, 0);

		// Get Variation of main Ray
		Vec3d direction();
		return sample_result;
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

