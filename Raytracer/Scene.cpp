

// Scene.cpp
#include <iostream>
#include <algorithm>
#include <opencv2.4/opencv2/opencv.hpp>
#include <cstdlib>
#include <chrono>
#include <future>

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
		rays(width*height, PrimaryRay(scene, location))

	{

		// Update Image Plane Distance
		calculateImageDistance();

		// Update MVecs
		SetRaysDirection();
	}

	// Update Frame
	void Camera::updateFrame()
	{
		// Reset Frame
		std::fill(frame.begin(), frame.end(), cv::Vec3b(235, 206, 135));

		// Reset Zbuffer
		std::fill(zbuffer.begin(), zbuffer.end(), 0.0f);

		// Vector to hold the threads
		std::vector<std::thread> threads;

		// Calculate the number of rows each thread should handle
		const int numThreads = std::thread::hardware_concurrency();
		int rowsPerThread = height / numThreads;

		// Launch threads
		for (int t = 0; t < numThreads; ++t)
		{
			int startRow = t * rowsPerThread;
			int endRow = (t == numThreads - 1) ? height : startRow + rowsPerThread;

			// Launch a thread to process this chunk of rows
			threads.emplace_back(&Camera::processRows, this, startRow, endRow);
		}

		// Wait for all threads to finish
		for (auto& thread : threads)
		{
			thread.join();  // Block until each thread has completed
		}
	}

	// Function to process a range of rows in parallel
	void Camera::processRows(int startRow, int endRow)
	{
		for (int col = 0; col < width; col++)
		{
			for (int row = startRow; row < endRow; row++)
			{
				int index = row * width + col;

				// Cast the PrimaryRay
				rays[index].cast(*this);
			}
		}
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
	void Camera::SetRaysDirection()
	{

		std::cout << "Calculating MVecs.." << std::endl;

		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{

				// Calculate Slope..
				rays[row * width + col].direction = Vec3d((col - width / 2)*1, (height / 2 - row) * 1, img_d).rotate(location, rotation.toRad());

			}
		}

		std::cout << "Done Calculating MVecs!" << std::endl;

	}


// --~-- Implement Scene --~--
	
	// Constructor
	Scene::Scene(std::vector<GeomObj>& geomObjs, std::vector<PointLight>& lightObjs):
		geomObjs(geomObjs),
		lightObjs(lightObjs)
	{

	}

	// Add GeomObj to geomObjs
	bool Scene::expand(const GeomObj& obj)
	{

		geomObjs.push_back(obj);
		return true;
	}	
	
	// Add LightObj to lightObjs
	bool Scene::expand(const PointLight& obj)
	{

		lightObjs.push_back(obj);
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

			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;

			// Post Process
			//camera.applyPP();

			// Display Image
			cv::imshow("Raytracing Viewport", image);

			// Wait & Check for Exit
			//checkInput();

			auto time = elapsed_seconds.count();
			system("cls");
			std::cout << "Frame #" << frameno << "(" << time << " s) [" << 1 / time << " FPS]" << std::endl;

			//// testers
			camera.scene.geomObjs[0].setRotation(Rotator3d
			(
				2, 2, 2)
			);
			cv::waitKey(1);


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
				camera.SetRaysDirection();

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