

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
	Camera::Camera(int width, int height, float fov, Point3d location, Rotator3d rotation, Scene& scene, AntiAliasing* aa_method) :
		width(width),
		height(height),
		fov(fov),
		location(location),
		rotation(rotation),
		scene(scene),

		frame(width*height,backgroundColor),
		zbuffer(width*height, 0.0f),
		nbuffer(width*height),
		rays(width*height, PrimaryRay(scene, location)),
		aa_method(aa_method)
	{

		// Update Image Plane Distance
		calculateImageDistance();

		// Update MVecs
		SetRaysDirection();
	}

	// ~*~ Update Frame 
	void Camera::updateFrame()
	{
		// Reset States
		std::fill(frame.begin(), frame.end(), backgroundColor); // Frame
		std::fill(zbuffer.begin(), zbuffer.end(), 0.0f); // Zbuffer
		std::fill(nbuffer.begin(), nbuffer.end(), Vec3d()); // Zbuffer
		
		// Render Pass..
		renderPass();

		// PP Pass
		//postProcessPass();

	}

	// ~*~ Manager for renderPass 
	bool Camera::renderPass()
	{
		// Vector to hold the threads
		std::vector<std::thread> threads;

		// Calculate the number of rows each thread should handle
		const int numThreads = std::thread::hardware_concurrency();
		int rowsPerThread = height / numThreads;

		// Launch threads
		for (int t = 0; t < numThreads; ++t)
		{

			// Position Parameters
			int startRow = t * rowsPerThread;
			int endRow = (t == numThreads - 1) ? height : startRow + rowsPerThread;

			// DataStructure to Document Hits
			std::array<Ray::HitDataVector, 2> hitDataVectors;

			// Launch a thread to process this chunk of rows
			threads.emplace_back(&Camera::renderPass_Worker, this, startRow, endRow, hitDataVectors);
		}

		// Wait for all threads to finish
		for (auto& thread : threads)
		{
			thread.join();  // Block until each thread has completed
		}

		return true;
	}

	// ~*~ Helper Function to process a range of rows in parallel for renderPass 
	void Camera::renderPass_Worker(int startRow, int endRow, std::array<Ray::HitDataVector, 2> primaryHits)
	{
		for (int col = 0; col < width; col++)
		{
			for (int row = startRow; row < endRow; row++)
			{
				int index = row * width + col;

				// Cast the PrimaryRay
				rays[index].castPrimary(row, col, primaryHits, this);
			}
		}
	}

	// ~*~ Apply Post Process to Frame 
	void Camera::postProcessPass()
	{

		// Assign Camera
		aa_method->camera_ptr = this;
		
		// Get Pixel Based Access
		for (int col = 0; col < width; col++)
		{
			for (int row = 0; row < height; row++)
			{	

				// Get Index
				int index = row * width + col;

				// Apply Appropriate AA
				if (aa_method == nullptr)
				{

					continue;
				}
				else if (FXAA* FXAA_ptr = dynamic_cast<FXAA*>(aa_method))
				{

					FXAA_ptr->apply();
				}
				else if (MSAA* MSAA_ptr = dynamic_cast<MSAA*>(aa_method))
				{

					MSAA_ptr->apply(row, col);
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
				rays[row * width + col].direction = Vec3d((col - width / 2)*1, (height / 2 - row) * 1, img_d).rotate(location, rotation.toRad()).normalize();

			}
		}

		std::cout << "Done Calculating MVecs!" << std::endl;

	}


// --~-- Implement Scene --~--
	
	// Constructor
	Scene::Scene(std::vector<GeomObj>& geomObjs, std::vector<PointLight>& lightObjs, float environmentLight_level):
		geomObjs(geomObjs),
		lightObjs(lightObjs),
		environmentLight_level(environmentLight_level)
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
	Viewport::Viewport(Camera& camera, int framerate):
		camera(camera),
		image(cv::Mat(camera.height, camera.width, CV_8UC3, camera.frame.data())),
		frameno(0),
		framerate(framerate)
	{

	}

	// Work
	void Viewport::work()
	{

		while (true)
		{

			// Params
			auto start = std::chrono::system_clock::now();
			frameno++;

			// Update Frame
			camera.updateFrame();

			// Display Image
			cv::imshow("Raytracing Viewport", image);
			cv::waitKey(1);

			// Wait & Check for Exit
			//checkInput();

			// Rotations
			camera.scene.geomObjs[0].setRotation(Rotator3d(3.f, 0.f, 0.f));
			camera.scene.geomObjs[1].setRotation(Rotator3d(1.5f, 1.5f, 1.5f));
			camera.scene.geomObjs[2].setRotation(Rotator3d(0.f, 3.f, 0.f));

			// Framerate Control & announce
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			auto time = elapsed_seconds.count() * 1000;
			if (framerate != 0) // --------------- rework if codeblock! not working...
			{
				int sleeptime = (1000.0f / framerate) - time;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
				std::cout << "Frame #" << frameno << "(" << time + sleeptime << " ms) [" << 1000 / int(time + sleeptime) << " FPS]" << std::endl;
			}
			else
			{
				std::cout << "Frame #" << frameno << "(" << time << " ms) [" << 1000 / int(time) << " FPS]" << std::endl;
			}

			system("cls");
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