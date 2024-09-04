

// Scene.cpp
#include <iostream>
#include <algorithm>
#include <opencv2.4/opencv2/opencv.hpp>

#include "Scene.h"


// --~-- Implement Camera --~--
	
	// Constructor
	Camera::Camera(Point3d location, Rotator3d rotation, Scene& scene, int width, int height, int framerate):
		location(location),
		rotation(rotation),

		scene(scene),
		width(width),
		height(height),
		framerate(framerate),

		frame(width*height, cv::Vec3b(250,206,135)),
		zbuffer(width*height, 0.0f),
		mvecs(width*height, Vec3d(0,0,0)),
		rays(width*height, Ray())

	{

		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{

				// Calculate Slope..
				mvecs[row * width + col] = Vec3d(col - width / 2, height / 2 - row, 1).rotate(location, rotation.toRad());

			}
		}

	}

	void Camera::updateFrame()
	{

		// Reset Zbuffer
		std::fill(zbuffer.begin(), zbuffer.end(), 0.0f);

		// Render frame..
		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{	

				// Flat arrays index
				int index = row * width + col;
				
				// Calculate Pixel based on Ray Casting
				rays[index].castRay(row, col, *this);

			}

		}
		return;

	}


// --~-- Implement Scene --~--
	
	// Constructor
	Scene::Scene(std::vector<GeomObj>& geomObjs):
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
	Viewport::Viewport(Camera& camera):
		camera(camera),
		image(cv::Mat(camera.height, camera.width, CV_8UC3, camera.frame.data())),
		frameno(0)
	{

	}

	// Work
	void Viewport::work()
	{

		while (true)
		{
			frameno++;
			std::cout << "Frame #" << frameno << std::endl;

			// Update Frame
			camera.updateFrame();

			// Display Image
			cv::imshow("Raytracing Viewport", image);
			
			// Wait & Check for Exit
			if (cv::waitKey(camera.framerate) >= 0)
			{
				return ;
			}


		}

	}