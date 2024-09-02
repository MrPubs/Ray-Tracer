
// Geometry.cpp
#include "Geometry.h"
#include <cmath>

// Forward Declarations
std::array<std::array<float, 3>, 3> multiplyMatrices(const std::array<std::array<float, 3>, 3>& a, const std::array<std::array<float, 3>, 3>& b);

// --~-- Implement Vec3d --~--

	// Constructor
	Vec3d::Vec3d(float x, float y, float z) : x(x), y(y), z(z) {}

	// Addition Operator
	Vec3d Vec3d::operator+(const Vec3d& other) const
	{
		return Vec3d(x + other.x, y + other.y, z + other.z);
	}

	// Subtraction Operator
	Vec3d Vec3d::operator-(const Vec3d& other) const
	{
		return Vec3d(x - other.x, y - other.y, z - other.z);
	}

	// Dot Product Operator
	float Vec3d::operator*(const Vec3d& other) const 
	{
		return (
			x * other.x + // x Component
			y * other.y + // y Component
			z * other.z  // z Component
			);
	}

	// Multiply By Factor Operator
	Vec3d Vec3d::operator*(float factor) const
	{
		return Vec3d(x * factor, y * factor, z * factor);
	}

	// Cross Product
	Vec3d Vec3d::cross(const Vec3d& other) const
	{

		return Vec3d(
			y * other.z - z * other.y, // x Component
			z * other.x - x * other.z, // y Component
			x * other.y - y * other.x  // z Component
		);
	}

	// Rotate
	Vec3d Vec3d::rotate(const Rotator3d& rotator) const
	{
		/*
		Requires Radians!
		*/

		float roll = rotator.x;
		float pitch = rotator.y;
		float yaw = rotator.z;

		// Precompute sine and cosine of angles
		float cosRoll = std::cos(roll);
		float sinRoll = std::sin(roll);
		float cosPitch = std::cos(pitch);
		float sinPitch = std::sin(pitch);
		float cosYaw = std::cos(yaw);
		float sinYaw = std::sin(yaw);

		// Rotation matrices for roll, pitch, and yaw
		std::array<std::array<float, 3>, 3> rollMatrix = { {
			{1,       0,        0},
			{0, cosRoll, -sinRoll},
			{0, sinRoll,  cosRoll}
		} };

		std::array<std::array<float, 3>, 3> pitchMatrix = { {
			{cosPitch,  0, sinPitch},
			{0,         1,        0},
			{-sinPitch ,0, cosPitch}
		} };

		std::array<std::array<float, 3>, 3> yawMatrix = { {
			{cosYaw, -sinYaw, 0},
			{sinYaw,  cosYaw, 0},
			{     0,       0, 1}
		} };

		// Combined rotation matrix
		std::array<std::array<float, 3>, 3> tempMatrix = multiplyMatrices(pitchMatrix, rollMatrix);
		std::array<std::array<float, 3>, 3> combinedMatrix = multiplyMatrices(yawMatrix, tempMatrix);

		// Rotate the vector
		float newX = combinedMatrix[0][0] * x + combinedMatrix[0][1] * y + combinedMatrix[0][2] * z;
		float newY = combinedMatrix[1][0] * x + combinedMatrix[1][1] * y + combinedMatrix[1][2] * z;
		float newZ = combinedMatrix[2][0] * x + combinedMatrix[2][1] * y + combinedMatrix[2][2] * z;

		return Vec3d(newX, newY, newZ);

	}

	// Euclidean Distance
	float Vec3d::distanceTo(const Vec3d& other) const
	{

		return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
	}

// --~-- Implement Point3d --~--
	
	// Constructor
	Point3d::Point3d(float x, float y, float z) : Vec3d::Vec3d(x, y, z) {}


	// Equal Operator
	Point3d Point3d::operator=(const Vec3d& vec)
	{

		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;

		return *this;
	}


// --~-- Implement Rotator3d --~--

	// Constructor
	Rotator3d::Rotator3d(float roll, float pitch, float yaw) : Vec3d::Vec3d(roll, pitch, yaw) {}

	// Methods
	Rotator3d Rotator3d::toRad() 
	{	

		return Rotator3d(x * PI / 180.0f, y * PI / 180.0f, z * PI / 180.0f);
	}
	Rotator3d Rotator3d::toDeg()
	{

		return Rotator3d(x * 180 / PI, y * 180 / PI, z * 180 / PI);
	}

	// Helpers
	// Helper function for matrix multiplication
	std::array<std::array<float, 3>, 3> multiplyMatrices(const std::array<std::array<float, 3>, 3>& a, const std::array<std::array<float, 3>, 3>& b) {
		std::array<std::array<float, 3>, 3> result = {};
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				result[i][j] = 0;
				for (int k = 0; k < 3; ++k) {
					result[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return result;
	}


// --~-- Implement Triangle --~--

	// Constructor
	Triangle::Triangle(std::array<Point3d, 3> vertices):
		vertices(vertices),
		min_ext(vertices[0]),
		max_ext(vertices[0]),
		normal((vertices[1] - vertices[0]).cross(vertices[2] - vertices[0])),
		k(-(normal*vertices[0]))
	{
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
	GeomObj::GeomObj(std::vector<Triangle> members, Vec3d color): 
		members(members),
		color(color)
	{
	}

	// Expand GeomObj
	bool GeomObj::Expand(const std::vector<Triangle>& new_members)
	{

		members.insert(members.end(), new_members.begin(), new_members.end());
		return true;
	}

