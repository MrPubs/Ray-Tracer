# Ray Tracer

This is a basic ray tracing project in C++ designed to explore and challenge C++ implementation through practical use.

## Features

- Camera, scene, and ray setup
- Basic geometric objects (points, triangles, shapes)
- Ray-object intersection handling

## Project Structure

- **Geometry Setup:**
  - `Point` - Implements vector operations.
  - `Triangle` - A collection of 3 points.
  - `GeomObjs` - Collection of triangles forming shapes.
  
- **Rays Setup:**
  - `Ray` - Updates image based on assigned pixel.

- **Scene Setup:**
  - `Scene` - Manages geometries, camera, and light sources.
  - `Camera` - Controls rays that collect scene data.
  - `Viewport` - Displays the scene.
  
- **Future Plans:**
  - Implement material properties and lighting (e.g., reflections, refractions).

## Getting Started

### Prerequisites

- C++11 or later
- OpenCV

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/MrPubs/Ray-Tracer.git
    ```
2. Install OpenCV.
3. Build the project.

### Usage

Run the program to generate a basic ray traced image:
```bash
./RayTracer
