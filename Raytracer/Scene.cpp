

// Scene.cpp
#include <iostream>
#include <opencv2.4/opencv2/opencv.hpp>
#include <algorithm>

#include "Scene.h"


// --~-- Implement Camera --~--
	
	// Constructor
	Camera::Camera(Point3d location, Rotator3d rotation, int width, int height, int framerate, int fov):
		location(location),
		rotation(rotation),

		width(width),
		height(height),

		rays(width* height, Ray(cv::Vec3b(0,0,0),Vec3d(0,0,1))),
		zbuffer(width*height, 0.0f),
		mvecs(width* height, Vec3d(0.0f, 0.0f, 0.0f)),

		framerate(framerate),
		frametime(1000/framerate),
		fov(fov)
	{	

		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{

				// Calculate Slope..
				mvecs[row * width + col] = Vec3d(col - width / 2, height / 2 - row, 1).rotate(location, rotation.toRad());
				rays[row * width + col].m_vec = mvecs[row * width + col];

			}
		}
	}


// --~-- Implement Scene --~--

	// Constructor
	Scene::Scene(Camera& camera, std::vector<GeomObj>& geomObjs) :
		camera(camera),
		geomObjs(geomObjs)
	{
	}

	// Add GeomObj to geomObjs
	bool Scene::expand(const GeomObj& obj)
	{

		geomObjs.push_back(obj);
		return true;
	}


// --~-- Implement Viewport --~--

	// Constructor
	Viewport::Viewport(int w, int h, Scene& scene):
		width(w),
		height(h),
		scene(scene), // Camera & geomObjs
		framerate(scene.camera.framerate),
		frametime(1000/framerate), // in milliseconds
		frameno(0), // Counter
		frame(std::vector<cv::Vec3b>(width* height)), // Pixel Color
		image(cv::Mat(height, width, CV_8UC3, frame.data())) // cv2 Image Obj

	{
		// Announce
		std::cout << "Setting Framerate to: " << framerate << " (" << frametime << "ms)" << std::endl;
	}

	// Refreshes Viewport Contents based on ray tracing
	bool Viewport::refreshVP()
	{

		// Empty Z Buffer
		std::fill(scene.camera.zbuffer.begin(), scene.camera.zbuffer.end(), 0.0f);


		// Fill the array with RGB values (for example, a gradient from blue to red)
		for (int row = 0; row < height; ++row) {
			for (int col = 0; col < width; ++col) {

				// Cast Rays & Update Pixel
				scene.camera.rays[row * width + col].castRay(row, col, scene);
				frame[row * width + col] = scene.camera.rays[row * width + col].pixel;
			}
		}

		// Show Image
		frameno++; 
		cv::imshow("Generated RGB Image", image);
		std::cout << "Frame #" << frameno << std::endl;

		return true;
	}

	// Session Loop
	bool Viewport::work()
	{
		
		// Session Loop
		while (true)
		{

			// Refresh VP
			refreshVP();

			// Wait & Check for Exit
			if (cv::waitKey(framerate) >= 0)
			{	
				closeVP();
				return true;
			}
		}
	}

	// Closes Viewport
	bool Viewport::closeVP()
	{
		std::cout << "Im inside Viewport closeVP.." << std::endl;

		return true;
	}
