
// Rays.cpp
#include "Rays.h"
#include "Scene.h"

// Implement Ray

	// Constructor
	Ray::Ray(cv::Vec3b pixel, Vec3d m_vec):
		pixel(pixel),
		m_vec(m_vec), // make setter and getter
		iter(0)
	{

	}


	// Ray Casting, Calculate Pixel Color.
	bool Ray::castRay(const int row, const int col, const Scene& scene)
	{
		// Params
		iter++;
		float ray_len = 0;
		Point3d hit_pt({ 0,0,0 });

		pixel[0] = 235; // B
		pixel[1] = 206; // G
		pixel[2] = 135; // R

		// Every Objects..
		for (GeomObj obj : scene.geomObjs)
		{

			// Every Triangle
			for (Triangle t : obj.members)
			{
				
				// Check if hit Plane:
				ray_len = -1 * (t.normal * scene.camera.location + t.k) / (t.normal * m_vec);
				if (ray_len > 0)
				{	

					// Check hit Location
					hit_pt = m_vec * ray_len + scene.camera.location;

					// Check for Triangle Bounding Box Extent
					if ((hit_pt.x <= t.max_ext.x && hit_pt.x >= t.min_ext.x)  && // Check for hit x in Triangle Bounding Box Extent
						(hit_pt.y <= t.max_ext.y && hit_pt.y >= t.min_ext.y)  && // Check for hit y in Triangle Bounding Box Extent
						(hit_pt.z <= t.max_ext.z && hit_pt.z >= t.min_ext.z))    // Check for hit z in Triangle Bounding Box Extent
					{
						
						// Check if Hit actual Triangle!
						if (t.isInside(hit_pt))
						{
							// std::cout << "Started from the bottom now we here!" << std::endl; // !!!
							pixel[0] = 0; // B
							pixel[1] = 0; // G
							pixel[2] = 255*(2/ray_len); // R
							continue;
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