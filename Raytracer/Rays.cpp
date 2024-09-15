

// Rays.cpp
#include "Rays.h"
#include "Scene.h"

// Implement PrimaryRay

	// Constructor
	PrimaryRay::PrimaryRay(cv::Vec3b pixel):
		pixel(pixel),
		iter(0)
	{

	}


	// PrimaryRay Casting, Calculate Pixel Color.
	void PrimaryRay::cast(const int row, const int col, Camera& camera)
	{
		// Params
		iter++;
		int ray_ind = row * camera.width + col;
		float ray_len = 0;
		Point3d hit_pt({ 0,0,0 });

		// Every Objects..
		for (GeomObj& obj : camera.scene.geomObjs)
		{

			// Every Triangle
			for (Triangle& t : obj.members)
			{
				
				// Check if hit Plane:
				ray_len = -1 * (t.normal * camera.location + t.k) / (t.normal * camera.mvecs[ray_ind]);
				if (ray_len > 0)
				{	

					// Check hit Location
					hit_pt = camera.mvecs[ray_ind] * ray_len + camera.location;

					// Check for Triangle Bounding Box Extent
					if ((hit_pt.x <= t.max_ext.x && hit_pt.x >= t.min_ext.x)  && // Check for hit x in Triangle Bounding Box Extent
						(hit_pt.y <= t.max_ext.y && hit_pt.y >= t.min_ext.y)  && // Check for hit y in Triangle Bounding Box Extent
						(hit_pt.z <= t.max_ext.z && hit_pt.z >= t.min_ext.z))    // Check for hit z in Triangle Bounding Box Extent
					{
						
						// Valid Intersection - PrimaryRay Hit Inside Triangle!
						if (t.isInside(hit_pt))
						{

							// std::cout << "Started from the bottom now we here!" << std::endl; // !!!
							
							// Check if closer than current pixel
							if (camera.zbuffer[ray_ind] == 0 || ray_len < camera.zbuffer[ray_ind])
							{

								// Update Z Buffer
								camera.zbuffer[ray_ind] = ray_len;

								// Adjust Pixel - make better depth adjust function
								pixel[0] = t.material.color.z; // B
								pixel[1] = t.material.color.y; // G
								pixel[2] = t.material.color.x; // R

								// Cast Shadow Rays
								// Shade based on angle


								// Update Pixel Color
								camera.frame[ray_ind] = pixel;

								continue;
							}
						}
					}
				}
			}
		}

		return;
	}


// Implement ShadowRay

	// Constructor
	ShadowRay::ShadowRay()
	{

	}

	// Methods
	void ShadowRay::cast()
	{

	}