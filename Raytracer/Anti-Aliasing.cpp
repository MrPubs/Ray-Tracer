
// Anti-Aliasing.cpp
#include <iostream>
#include <array>
#include <cmath>

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
		if (isEdge(pixel_index))
		{

			// Multi-Sampled Pixel
			Vec3d result(0, 0, 0);
			
			// Get former Direction
			Vec3d former_direction = camera_ptr->rays[pixel_index].direction;

			// HitDataVector for Ray Casting
			// TODO: find a way to avoid creating new container for this!!
			std::array<Ray::HitDataVector, 2> hitDataVectors;

			// Trace Rays to Sample Locations
			for (int sample_index = 0; sample_index < sample_count; sample_index++)
			{

				// 1. Get Direction Variation
				// 2. Calculate Sample
				result += calculateSample(pixel_index, former_direction, hitDataVectors, row, col);
				//std::cout << "Result #" << sample_index << " [X=" << result.x << ", Y=" << result.y << ", Z=" << result.z << "]" << std::endl;
			}

			// Finish
			camera_ptr->rays[pixel_index].direction = former_direction; // Reset Ray Direction
			result /= sample_count; // Average

			// Debug
			camera_ptr->frame[pixel_index][2] = result.x;
			camera_ptr->frame[pixel_index][1] = result.y;
			camera_ptr->frame[pixel_index][0] = result.z;
			
			return result;
		}
		else
		{
		}
	}

	Vec3d MSAA::calculateSample(int index, Vec3d direction, std::array<Ray::HitDataVector, 2>& HitVectors, int row, int col)
	{

		// Get Variation of main Ray
		camera_ptr->rays[index].direction = direction;
		camera_ptr->rays[index].castPrimary(row, col, HitVectors, camera_ptr);

		// RGB
		//return Vec3d(255, 0 ,0);
		return Vec3d(camera_ptr->frame[index][0], camera_ptr->frame[index][1], camera_ptr->frame[index][0]);

	} // Helper

	bool MSAA::isEdge(int pixel_index)
	{

		// Params
		int result = 0;
		Camera& camera_ref = *this->camera_ptr;

		// Thresholds
		const float depth_threshold = 2;
		const float norm_threshold = 15;
		const float color_threshold = 5;

		// Left neighbor
		if (pixel_index % camera_ref.width != 0)
		{

			int left_index = pixel_index - 1;
			result += assessPixels(camera_ptr, pixel_index, left_index, depth_threshold, norm_threshold, color_threshold);
		}

		// Right neighbor
		if ((pixel_index + 1) % camera_ref.width != 0)
		{

			int right_index = pixel_index + 1;
			result += assessPixels(camera_ptr, pixel_index, right_index, depth_threshold, norm_threshold, color_threshold);
		}

		// Up neighbor
		if (pixel_index - camera_ref.width >= 0)
		{

			int up_index = pixel_index - camera_ref.width;
			result += assessPixels(camera_ptr, pixel_index, up_index, depth_threshold, norm_threshold, color_threshold);
		}
		
		// Down neighbor
		if (pixel_index + camera_ref.width < camera_ref.width * camera_ref.height)
		{

			int down_index = pixel_index + camera_ref.width;
			result += assessPixels(camera_ptr, pixel_index, down_index, depth_threshold, norm_threshold, color_threshold);
		}


		// Evaluate edge
		if (result >= 1) {
			
			/*// Detection Color
			switch (result)
			{
			case 1:

				camera_ptr->frame[pixel_index][0] = 0;
				camera_ptr->frame[pixel_index][1] = 64;
				camera_ptr->frame[pixel_index][2] = 0;
				break;

			case 2:

				camera_ptr->frame[pixel_index][0] = 0;
				camera_ptr->frame[pixel_index][1] = 128;
				camera_ptr->frame[pixel_index][2] = 0;
				break;

			case 3:

				camera_ptr->frame[pixel_index][0] = 0;
				camera_ptr->frame[pixel_index][1] = 196;
				camera_ptr->frame[pixel_index][2] = 0;
				break;

			case 4:

				camera_ptr->frame[pixel_index][0] = 0;
				camera_ptr->frame[pixel_index][1] = 255;
				camera_ptr->frame[pixel_index][2] = 0;
				break;
			}*/

			return true;
		}
		else {

			/*// Undetected Color
			camera_ptr->frame[pixel_index][0] = 0;
			camera_ptr->frame[pixel_index][1] = 0;
			camera_ptr->frame[pixel_index][2] = 0;*/

			return false;
		}
	}

	bool MSAA::assessPixels(Camera* camera_ptr, int main_index, int neighbor_index, float depth_threshold, float normal_threshold, float color_threshold)
	{

		// PI Constant
		const double PI = 3.1415926535897743;

		// Results
		bool depth_flag = false;
		bool normal_flag = false;
		bool color_flag = false;
		
		// Camera Reference
		const Camera& camera_ref = *camera_ptr;

		// Conditions
		float condition_a = std::abs(camera_ref.zbuffer[main_index] - camera_ref.zbuffer[neighbor_index]); // Depth Buffer Delta
		float condition_b = (std::acos(camera_ref.nbuffer[main_index] * camera_ref.nbuffer[neighbor_index]) * (180.0f / PI)); // Normals Angle
		float condition_c = cv::norm(camera_ref.frame[main_index] - camera_ref.frame[neighbor_index]); // Color Delta

		// Comparison
		if (condition_a > depth_threshold) { depth_flag = true; };  //  Depth Difference Test
		if (condition_b > normal_threshold && condition_b != 90) { normal_flag = true; };  //  Normal Angles Test
		if (condition_c > color_threshold) { color_flag = true; };  // Color Difference Test

		// assess pixel
		if ((depth_flag + normal_flag + color_flag) >= 2) { 

			return true; 
		}
		else {

			return false; 
		}
	}


// Implement FXAA Post-process AA

	void FXAA::foo() {} // Force polymorphic class

	FXAA::FXAA()
	{

	}

	void FXAA::apply()
	{

		//std::cout << "FXAA!" << std::endl;
	}

