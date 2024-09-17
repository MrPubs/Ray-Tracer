

// Vectors.cpp

#include "Vectors.h"
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

// Equate
bool Vec3d::operator==(const Vec3d& other) const
{
	
	return (
		x == other.x &&
		y == other.y &&
		z == other.z
		);
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
Vec3d Vec3d::rotate(const Point3d origin, const Rotator3d& rotator) const
{
	/*
	Requires Radians!
	*/

	float roll = rotator.roll;
	float pitch = rotator.pitch;
	float yaw = rotator.yaw;

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
	Vec3d translatedVector = *this - origin;
	std::array<std::array<float, 3>, 3> rotationMatrix = multiplyMatrices(rollMatrix, multiplyMatrices(pitchMatrix, yawMatrix));

	// Rotate the vector
	float newX = rotationMatrix[0][0] * translatedVector.x + rotationMatrix[0][1] * translatedVector.y + rotationMatrix[0][2] * translatedVector.z;
	float newY = rotationMatrix[1][0] * translatedVector.x + rotationMatrix[1][1] * translatedVector.y + rotationMatrix[1][2] * translatedVector.z;
	float newZ = rotationMatrix[2][0] * translatedVector.x + rotationMatrix[2][1] * translatedVector.y + rotationMatrix[2][2] * translatedVector.z;

	Vec3d rotatedVector = Vec3d(newX, newY, newZ) + origin;

	return rotatedVector;

}

// Euclidean Distance
float Vec3d::distanceTo(const Vec3d& other) const
{

	return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
	//return std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2);
}

// Normalize
Vec3d Vec3d::normalize() const
{

	float length = std::sqrt(x * x + y * y + z * z);
	return Vec3d(x / length, y / length, z / length);
}

// --~-- Implement Point3d --~-- Deprecated Currently!
// 
//	// Constructor
//Point3d::Point3d(float x, float y, float z) : Vec3d::Vec3d(x, y, z) {}
//
//
//// Equal Operator
//Point3d Point3d::operator=(const Vec3d& vec)
//{
//
//	this->x = vec.x;
//	this->y = vec.y;
//	this->z = vec.z;
//
//	return *this;
//}


// --~-- Implement Rotator3d --~--

	// Constructor
Rotator3d::Rotator3d(float roll, float pitch, float yaw) :
	roll(roll),
	pitch(pitch),
	yaw(yaw),
	Vec3d::Vec3d(roll, pitch, yaw)
{
}

// Methods
Rotator3d Rotator3d::toRad() const
{

	return Rotator3d(roll * PI / 180.0f, pitch * PI / 180.0f, yaw * PI / 180.0f);
}
Rotator3d Rotator3d::toDeg() const
{

	return Rotator3d(roll * 180 / PI, pitch * 180 / PI, yaw * 180 / PI);
}

// Helpers
// Helper function for matrix mul - 3x3 matrices only
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

