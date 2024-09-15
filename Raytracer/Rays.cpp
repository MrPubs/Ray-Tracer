

// Rays.cpp
//#include <vector> // reactivate if missing vector..

#include "Rays.h"
#include "Scene.h"

// Implement Ray

	//Ray::HitData::HitData(Triangle triangle, Point3d hit_pt, float distance) triangle(triangle), hit_pt(hit_pt), distance(distance)
	//{

	//};
	
	Ray::HitData::HitData(Triangle triangle, Point3d hit_pt, float distance): triangle(triangle), hit_pt(hit_pt), distance(distance)
	{

	};

	// Constructor
	Ray::Ray(Scene& scene, Point3d origin, Vec3d direction):
		scene(scene),
		origin(origin),
		direction(direction)
	{

	}

	// Methods
	void Ray::cast(Camera& camera, bool quick)
	{

		// Result!
		//std::vector<HitData> result;

		// Params
		Point3d hit_pt({ 0,0,0 });
		float distance = 0.0f;

		// Every Objects..
		for (GeomObj& geometry : camera.scene.geomObjs)
		{

			// Every Triangle
			for (Triangle& T : geometry.members)
			{

				// Check if hit Plane:
				distance = -1 * (T.normal * origin + T.k) / (T.normal * direction);
				if (distance > 0)
				{

					// Check hit Location
					hit_pt = direction * distance + origin;

					// Check for Triangle Bounding Box Extent
					if ((hit_pt.x <= T.max_ext.x && hit_pt.x >= T.min_ext.x) && // Check for hit x in Triangle Bounding Box Extent
						(hit_pt.y <= T.max_ext.y && hit_pt.y >= T.min_ext.y) && // Check for hit y in Triangle Bounding Box Extent
						(hit_pt.z <= T.max_ext.z && hit_pt.z >= T.min_ext.z))   // Check for hit z in Triangle Bounding Box Extent
					{

						// Valid Intersection - Ray Triangle!
						if (T.isInside(hit_pt))
						{
							// Started from the bottom now we here!

							// Add Result
							//result.push_back(HitData(T, hit_pt, distance));
							
							if (quick)
							{

								// Leave with First Hit
								//return result;
							}
						}
					}
				}
			}
		}

		// Leave with All Hits
		return;
	}


// Implement PrimaryRay

	// Constructor
	PrimaryRay::PrimaryRay(Scene& scene, Point3d origin, Vec3d direction , cv::Vec3b pixel):
		Ray(scene, origin, direction),
		pixel(pixel)
	{

		// Reserve Memory for shadowRays based on lightObjs Count
		int lightObjs_Count = scene.lightObjs.size();
		shadowRays.reserve(lightObjs_Count);

		// Make a Shadow Ray for every Light Object per Ray
		for (int i = 0; i < lightObjs_Count; i++)
		{
			
			shadowRays.emplace_back(ShadowRay(scene));
		}
	}


	// PrimaryRay Casting, Calculate Pixel Color.
	void PrimaryRay::castPrimary(const int row, const int col, Camera& camera)
	{

		// Cast Ray Forward
		//std::vector<Ray::HitData> result = cast(camera);
		cast(camera);

		// Check Hits
		//int ray_ind = row * camera.width + col;
		//for (const Ray::HitData& item : result)
		//{

		//	// Get Tuple Breakdown
		//	const Triangle T = std::get<0>(item);
		//	const Vec3d hit_pt = std::get<1>(item);
		//	const float distance = std::get<2>(item);
		//	
		//	// Check if closer than current pixel
		//	if (camera.zbuffer[ray_ind] == 0 || distance < camera.zbuffer[ray_ind])
		//	{

		//		// Update Z Buffer
		//		camera.zbuffer[ray_ind] = distance;

		//		// Adjust Pixel - make better depth adjust function
		//		pixel[0] = T.material.color.z; // B
		//		pixel[1] = T.material.color.y; // G
		//		pixel[2] = T.material.color.x; // R

		//		// here goes shadow ray operation!

		//		// Update Pixel Color
		//		camera.frame[ray_ind] = pixel;
		//		continue;

		//	}
		//}

		// Temporary Remenants of old times!!
		//// Cast Shadow Rays -----------------------
		//for (int i = 0; i < light_source_count; i++)
		//{

		//	// Get Distance to Light Obj..
		//	PointLight light_object = camera.scene.lightObjs.at(i);
		//	int distance = hit_pt.distanceTo(light_object.location);

		//	// If not too far..
		//	if (distance < light_object.range)
		//	{
		//		

		//		// Cast Ray!
		//	}

		//}

	}


// Implement ShadowRay

	// Constructor
	ShadowRay::ShadowRay(Scene& scene):
		origin(Point3d(0,0,0))
	{

	}

	// Methods
	void ShadowRay::cast()
	{

		// Check if not blocked
		
		  // Calculate Shadow Ray Effect
	}