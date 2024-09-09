

// Scene.cpp
#include <iostream>
#include <algorithm>
#include <opencv2.4/opencv2/opencv.hpp>
#include<cstdlib>
#include <chrono>

#include "Scene.h"

// --~-- Implement Camera --~--
	
	// Constructor
	Camera::Camera(int width, int height, float fov, Point3d location, Rotator3d rotation, Scene& scene) :
		width(width),
		height(height),
		fov(fov),
		location(location),
		rotation(rotation),
		scene(scene),

		frame(width*height, cv::Vec3b(250,206,135)),
		zbuffer(width*height, 0.0f),
		mvecs(width*height, Vec3d(0,0,0)),
		rays(width*height, Ray())

	{
		
		// Update Image Plane Distance
		calculateImageDistance();

		// Update MVecs
		calculateMVecs();
	}

	// Update Frame
	void Camera::updateFrame()
	{

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
	
	// Calculate Image Distance
	void Camera::calculateImageDistance()
	{
		const float PI = 3.141592653589793f; // TODO: Fix cmath not recognizing the M_PI Identifier
		img_d = (width/2.0f)/(std::tan(fov/2.0f * PI / 180.0f));

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
				mvecs[row * width + col] = Vec3d((col - width / 2)*1, (height / 2 - row) * 1, img_d).rotate(location, rotation.toRad());

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

			auto start = std::chrono::system_clock::now();
			frameno++;
			

			// Update Frame
			camera.updateFrame();

			// Post Process
			//camera.applyPP();

			// Display Image
			cv::imshow("Raytracing Viewport", image);

			// Wait & Check for Exit
			//checkInput();


			//// testers
			camera.scene.geomObjs[0].setRotation(Rotator3d
			(
				2, 2, 2)
			);
			cv::waitKey(24);

			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;

			auto time = elapsed_seconds.count();
			system("cls");
			std::cout << "Frame #" << frameno << "(" << time << " ms) [" << 1/time << " FPS]" << std::endl;

		}
	}

	// Check for input - needs to leave on its own IO Process
	void Viewport::checkInput()
	{
		float x = camera.scene.geomObjs[0].rotation.roll;
		bool flag = false;
		int key = cv::waitKey(24);
		if (key >= 0)
		{

			if (key == 27)
			{

				std::cout << " Closing Viewport.. ";
				exit(0);
			}

			// Rotations
			else if (key == 'q')
			{
				camera.rotation.roll += 5;
				flag = true;

			}
			else if (key == 'w')
			{
				camera.rotation.pitch -= 5;
				flag = true;
			}
			else if (key == 'e')
			{
				camera.rotation.yaw -= 5;
				flag = true;
			}
			else if (key == 'a')
			{
				camera.rotation.roll -= 5;
				flag = true;
			}
			else if (key == 's')
			{
				camera.rotation.pitch += 5;
				flag = true;
			}
			else if (key == 'd')
			{
				camera.rotation.yaw += 5;
				flag = true;
			}
			else if (key == 'z') // Reset Orientation
			{
				std::cout << "Yaw Down.." << std::endl;
				camera.rotation.roll = 0;
				camera.rotation.pitch = 0;
				camera.rotation.yaw = 0;
				flag = true;
			}
			else if (key == 'p')
			{

				camera.scene.geomObjs[0].setRotation(Rotator3d(0, 0, 45));

			}

			if (flag);
			{

				// Commit Camera Change
				camera.calculateMVecs();

				for (GeomObj& obj : camera.scene.geomObjs)
				{

					for (Triangle& t : obj.members)
					{


						t.initialize();
					}
				}
			}
		}
	}