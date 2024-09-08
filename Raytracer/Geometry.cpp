

// Geometry.cpp
#include <iostream>

#include "Geometry.h"
#include "Vectors.h"

// --~-- Implement Triangle --~--

	// Constructor
	Triangle::Triangle(std::array<Point3d, 3> vertices, Material material ):
		vertices(vertices),
		material(material),
		min_ext(vertices[0]),
		max_ext(vertices[0]),
		normal(Vec3d(0,0,0)),
		k(0)

	{

		// Get Plane Params
		setPlaneParams();

		// Set minmax extents 
		setExtents();
 	}

	// Methods
	bool Triangle::isIntersecting(const Point3d& pt)
	{	
		return true;
	}
	void Triangle::setExtents()
	{

		for (Point3d vertex : vertices)
		{

			// Min ext
			if (vertex.x < min_ext.x)
			{
				min_ext.x = vertex.x;
			}
			if (vertex.y < min_ext.y)
			{
				min_ext.y = vertex.y;
			}
			if (vertex.z < min_ext.z)
			{
				min_ext.z = vertex.z;
			}

			// Max ext
			if (vertex.x > max_ext.x)
			{
				max_ext.x = vertex.x;
			}
			if (vertex.y > max_ext.y)
			{
				max_ext.y = vertex.y;
			}
			if (vertex.z > max_ext.z)
			{
				max_ext.z = vertex.z;
			}

		}
	}
	bool Triangle::isInside(const Point3d& pt)
	{
		//
		//       pt2
		//       / \
		//    A /   \ B
		//     /     \ 
		//    /_______\
		//  pt0   C   pt1
		//
		
		// Per Side
		bool sideA = sameSide(pt, 0);
		bool sideB = sameSide(pt, 1);
		bool sideC = sameSide(pt, 2);
		return (sideA && sideB && sideC);
	}
	void Triangle::setPlaneParams()
	{
		normal = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
		k = -(normal * vertices[0]);
	}

	// Helpers
	bool Triangle::sameSide(const Point3d& pt, int vertex_ind)
	{
		int vec_start = (vertex_ind + 1) % 3;
		int vec_end   = (vertex_ind + 2) % 3;

		Vec3d v = vertices[vec_start] - vertices[vec_end];
		Vec3d a = v.cross(Vec3d(pt - vertices[vec_end]));
		Vec3d b = v.cross(Vec3d(vertices[vertex_ind] - vertices[vec_end]));
		float c = a * b;

		return c >= 0 ;
	}

// --~-- Implement GeomObj --~--

	// Constructor
	GeomObj::GeomObj(std::vector<Triangle> members) :
		members(members),
		rotation(Rotator3d(0, 0, 0)),
		origin(members[0].vertices[0])
	{
	
	}

	// Expand GeomObj
	bool GeomObj::Expand(const std::vector<Triangle>& new_members)
	{

		members.insert(members.end(), new_members.begin(), new_members.end());
		return true;
	}
	void GeomObj::setRotation(const Rotator3d& new_rotation)
	{
		Rotator3d rotator = new_rotation; // Omit this code in the future
		std::cout << "Rotated: " << rotator.roll << " " << rotator.pitch << " " << rotator.yaw << std::endl;

		// Every Triangle
		for (Triangle t : members)
		{

			// Every Vertex
			for (Point3d v : t.vertices)
			{

				// Rotate and set
				Vec3d p = v.rotate(Point3d(0, 0, 0), Rotator3d(90,90,90).toRad());
				std::cout << "v: " << v.x << " " << v.y << " " << v.z << std::endl;
				std::cout << "p: " << p.x << " " << p.y << " " << p.z << std::endl;
				std::cout << "--------------------------------------" << std::endl;
				v = p;

			}

			// Set New Plane Params
			t.setPlaneParams();

			// Set New Plane Extents
			t.setExtents();

		}

		rotation.roll = new_rotation.roll;
		rotation.pitch = new_rotation.pitch;
		rotation.yaw = new_rotation.yaw;

	}
