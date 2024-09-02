# Ray-Tracer
This is A Basic Readme to mark the start of the project, which will expand, change, and become more thorough as the project evolves.

*IMPORTANT*: this is a learning project to serve as a challenge and a practical use for C++ implementation, and not a state of the art solution.

the architecture involves the following main objects:

*Geometry Setup:*
1. Point - Vector3d that implements Coordinate operations.
2. Triangle - a Collection of 3 Points.
3. GeomObjs - Geometries that serve as a triangle collection that make up a Shape, Triangles are a collection of Vertices in space.

*Rays Setup:*
1. Ray - Responsible to update the image based on the pixel it is assigned to, in the future will serve for Polymorphism Rays (Primary, Secondary, Refraction...).

*Scene Setup:*
1. Scene - a Manager for all Geometries, Camera, And Light Sources.
2. Camera - a Window into a Scene, it controls the Ray Objects that it casts to collect data from the Scene.
3. Light Sources - Interacts with Ray Objects to Describe shading on Objects.
4. Viewport - a Display for the Window of the Scene - Visualize Image.

*Material Setup:*
~ future planning ~
Will be the foundation of GeomObjs Texturing - will serve as a setup for any future Material Attributes that might be applied.


*Sources*:

How to Write a Ray Tracer Intuitively:
https://blog.scottlogic.com/2020/03/10/raytracer-how-to.html

Exploring Ray Tracing and CGI - How is CGI Made?
https://www.youtube.com/watch?v=iOlehM5kNSk

How do Video Game Graphics Work?
https://www.youtube.com/watch?v=C8YtdC8mxTU
 

