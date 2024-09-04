

// Rays.cpp
#include "Rays.h"
#include "Scene.h"

// Implement Ray

	// Constructor
	Ray::Ray(cv::Vec3b pixel):
		pixel(pixel),
		iter(0)
	{

	}


	// Ray Casting, Calculate Pixel Color.
	bool Ray::castRay(const int row, const int col, Camera& camera)
	{
		// Params
		iter++;
		int ray_ind = row * camera.width + col;
		float ray_len = 0, distance = 0;
		Point3d hit_pt({ 0,0,0 });

		pixel[0] = 235; // B
		pixel[1] = 206; // G
		pixel[2] = 135; // R


		// Every Objects..
		for (GeomObj obj : camera.scene.geomObjs)
		{

			// Every Triangle
			for (Triangle t : obj.members)
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
						
						// Check if Hit actual Triangle!
						if (t.isInside(hit_pt))
						{

							// std::cout << "Started from the bottom now we here!" << std::endl; // !!!
							
							// Check if closer than current pixel
							if (camera.zbuffer[ray_ind] == 0 || ray_len < camera.zbuffer[ray_ind])
							{

								// Update Z Buffer
								camera.zbuffer[ray_ind] = ray_len;

								// Set Distance
								if (ray_len < 255) { distance = ray_len; }
								else { distance = 255; }
								
								// Adjust Pixel - make better depth adjust function
								pixel[0] = t.material.color.z * 50 /distance;// B
								pixel[1] = t.material.color.y * 50 /distance;// G
								pixel[2] = t.material.color.x * 50 /distance;// R

								camera.frame[ray_ind] = pixel;

								continue;
							}
						}
					}
				}
			}
		}

		// Change Pixel Color
		//pixel[0] = pixel[0] + 0; // B
		//pixel[1] = pixel[1] + 5; // G
		//pixel[2] = pixel[2] + 0; // R
	
		return true;
	}