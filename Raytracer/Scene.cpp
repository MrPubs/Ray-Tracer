

// Scene.cpp
#include <iostream>
#include <algorithm>
#include <opencv2.4/opencv2/opencv.hpp>
#include<cstdlib>

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
		
		// Update MVecs
		calculateMVecs();
	}

	void Camera::updateFrame()
	{
		std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

		// Reset Frame
		std::fill(frame.begin(), frame.end(), cv::Vec3b(235, 206, 135));

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

	// Apply Post Process to Frame
	void Camera::applyPP()
	{

		// Calculate Distance Shader
		auto zbuffer_max = std::max_element(zbuffer.begin(), zbuffer.end());

		// Get Pixel Based Access
		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{	

				int index = row * width + col;

				// if found
				if (zbuffer[index] != 0)
				{
					frame[index] *= (1-(zbuffer[index] / *zbuffer_max));
				}

			}
		}
	}

	// Calculate MVecs
	void Camera::calculateMVecs()
	{

		std::cout << "Calculating MVecs.." << std::endl;

		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{

				// Calculate Slope..
				mvecs[row * width + col] = Vec3d(col - width / 2, height / 2 - row, 1).rotate(location, rotation.toRad());

			}
		}

		std::cout << "Done Calculating MVecs!" << std::endl;

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

			// Post Process
			camera.applyPP();

			// Display Image
			cv::imshow("Raytracing Viewport", image);

			// Wait & Check for Exit
			checkInput();

		}
	}

	void Viewport::checkInput()
	{

		bool flag = false;
		int key = cv::waitKey();
		if (key >= 0)
		{

			if (key == 27)
			{

				std::cout << " Closing Viewport.. ";
				exit(0);
			}

			//// Rotations
			//else if (key == 'q') // Pitch up
			//{

			//	std::cout << "Pitch Up.." << std::endl;
			//	camera.location.x += 15;
			//	flag = true;
			//}
			//else if (key == 'w') // Yaw up
			//{

			//	std::cout << "Yaw Up.." << std::endl;
			//	camera.location.y -= 5;
			//	flag = true;
			//}
			//else if (key == 'e') // Roll up
			//{

			//	std::cout << "Roll Up.." << std::endl;
			//	camera.location.z -= 5;
			//	flag = true;
			//}
			//else if (key == 'a') // Pitch down
			//{

			//	std::cout << "Pitch Down.." << std::endl;
			//	camera.location.x -= 5;
			//	flag = true;
			//}
			//else if (key == 's') // Yaw down
			//{

			//	std::cout << "Yaw Down.." << std::endl;
			//	camera.location.y += 5;
			//	flag = true;
			//}
			//else if (key == 'd') // Roll down
			//{

			//	std::cout << "Roll Down.." << std::endl;
			//	camera.location.z += 5;
			//	flag = true;
			//}
			//else if (key == 'z') // Reset Orientation
			//{

			//	std::cout << "Yaw Down.." << std::endl;
			//	camera.location.x = 0;
			//	camera.location.y = 0;
			//	camera.location.z = 0;
			//	flag = true;
			//}
			//if (flag);
			//{

			//	camera.calculateMVecs();
			//}
		}
	}