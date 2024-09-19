

// Rays.cpp
//#include <vector> // reactivate if missing vector..

#include "Rays.h"
#include "Scene.h"

// Implement Ray

	//Ray::HitData::HitData(Triangle triangle, Point3d hit_pt, float distance) triangle(triangle), hit_pt(hit_pt), distance(distance)
	//{

	//};
	
	Ray::HitData::HitData(Triangle* triangle_ptr, Point3d hit_pt, float distance): triangle_ptr(triangle_ptr), hit_pt(hit_pt), distance(distance)
	{

	};

	// Constructor
	Ray::Ray(Scene& scene, Point3d origin, Vec3d direction):
		scene(scene),
		origin(origin),
		direction(direction),
		max_ray_length(0.0f)
	{

	}

	// Methods
	bool Ray::cast(std::vector<Ray::HitData>& hits, Triangle* avoidTriangle, bool quick)
	{

		// Params
		Point3d hit_pt({ 0,0,0 });
		float distance = 0.0f;

		// Every Objects..
		for (GeomObj& geometry : scene.geomObjs)
		{

			// Every Triangle
			for (Triangle& T : geometry.members)
			{	

				// Check if the Triangle being looked at is classified as avoid!
				if (&T == avoidTriangle)
				{
					continue;
				}

				// Check if hit Plane:
				distance = -1 * (T.normal * origin + T.k) / (T.normal * direction);
				if ((distance > 0 && distance < max_ray_length || max_ray_length == 0 && distance > 0) && !std::isinf(distance))
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

							// Add to Result
							hits.emplace_back(&T, hit_pt, distance);

							if (quick)
							{

								// Leave with First Hit
								return hits.size() > 0;
							}
						}
					}
				}
			}
		}

		// Leave with All Hits
		return hits.size() > 0;
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
			
			shadowRays.emplace_back(ShadowRay(scene, Point3d(0,0,0), Vec3d(0,0,0)));
		}
	}


	// PrimaryRay Casting, Calculate Pixel Color.
	void PrimaryRay::castPrimary(const int row, const int col, std::array<Ray::HitDataVector, 2>& hitVectors, Camera& camera)
	{

		// variable setup
		Ray::HitDataVector& primaryHits = hitVectors[0];
		Ray::HitDataVector& shadowHits = hitVectors[1];
		int light_source_count = camera.scene.lightObjs.size();
		float lightFactor;

		// Cast Ray Forward
		if (cast(primaryHits))
		{

			// Parameters
			int ray_ind = row * camera.width + col;

			for (Ray::HitData& hitData : primaryHits)
			{

				//Check if closer than current pixel
				if (camera.zbuffer[ray_ind] == 0 || hitData.distance < camera.zbuffer[ray_ind])
				{

					// Update Z Buffer
					camera.zbuffer[ray_ind] = hitData.distance;

					// Adjust Pixel - make better depth adjust function
					Triangle& T = *hitData.triangle_ptr;
					pixel[0] = T.material.color.z; // B
					pixel[1] = T.material.color.y; // G
					pixel[2] = T.material.color.x; // R


					// Cast Shadow Rays to every light source thats in range
					lightFactor = scene.environmentLight_level;
					for (int i = 0; i < light_source_count; i++)
					{

						// Get Distance to Light Obj..
						PointLight& light_object = camera.scene.lightObjs.at(i);
						int distance = hitData.hit_pt.distanceTo(light_object.location);

						// If in range..
						if (distance < light_object.range || light_object.range == 0)
						{

							// Setup Ray
							ShadowRay& shadow_ray = shadowRays[i];
							shadow_ray.origin = hitData.hit_pt;
							shadow_ray.direction = (light_object.location - shadow_ray.origin).normalize();
							shadow_ray.max_ray_length = distance;

							// Check if surface is lit (looking at the side that is directed at the light)
							bool litSurface = (shadow_ray.direction * T.normal > 0) == (direction.normalize() * T.normal <= 0);
							if (litSurface)
							{

								// Cast shadow!
								lightFactor += shadow_ray.castShadow(shadowHits, hitData.triangle_ptr);
							}

						}
					}

					// Update Pixel Color
					camera.frame[ray_ind] = pixel*lightFactor;
				}
			}

			// Prepare for next Ray
			primaryHits.clear();
		}
	}


// Implement ShadowRay

	// Constructor
	ShadowRay::ShadowRay(Scene& scene, Point3d origin, Vec3d direction): 
		Ray(scene, origin, direction)
	{

	}

	// Methods
	float ShadowRay::castShadow(Ray::HitDataVector& shadowHits, Triangle* originTriangle_ptr)
	{
		// Result
		float result = 0.0f;

		// Check if not blocked
		if (cast(shadowHits, originTriangle_ptr, true) == false)
		{
			
			// Get origin Triangle
			Triangle& originTriangle = *originTriangle_ptr;

			// Calculate normal Direction based on direction of ray & direction of normal - if same direction set to 1.0f, if not same direction negate.
			float normalDirection = (direction * originTriangle.normal > 0) ? 1.0f : -1.0f;
			float shadingAmplification = 2.0f; // shadingAmplification < 1.0 = Attenuation, shadingAmplification > 1.0 = amplification

			// Set Lambertian Shadin
			float lambertianShading = std::pow(std::max(0.0f, originTriangle.normal.normalize() * direction * normalDirection), shadingAmplification);
			result += lambertianShading;


		}
		else
		{

			// good!
			result += 0;

			// Clear Vector from hit
			shadowHits.clear();
		}

		return result;
	}