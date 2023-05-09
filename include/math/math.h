#pragma once
#include <stdexcept>
#include <cmath>
#include <limits>

#include "rotation_matrix.h"

constexpr auto M_PI = 3.14159265358979323846f;
constexpr auto M_RADPI = 57.295779513082f;
#define M_PI_F		((float)(M_PI))
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI_F / 180.f) )

struct Matrix3x3
{
	constexpr float* operator[](int index) noexcept
	{
		return data[index];
	}

	constexpr const float* operator[](int index) const noexcept
	{
		return data[index];
	}

	float data[3][3] = { };
};

struct ViewMatrix
{
	constexpr float* operator[](int index) noexcept
	{
		return data[index];
	}

	constexpr const float* operator[](int index) const noexcept
	{
		return data[index];
	}

	float data[4][4] = { };
};

struct Vector3
{
	constexpr Vector3(const float x = 0.f, const float y = 0.f, const float z = 0.f) noexcept :
		x(x), y(y), z(z) { }


	constexpr Vector3 operator+(const Vector3& other) const noexcept
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	constexpr Vector3 operator-(const Vector3& other) const noexcept
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	constexpr Vector3 operator*(const Vector3& other) const noexcept
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	
	constexpr Vector3 operator+=(const Vector3& other) 
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	
	constexpr Vector3 operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	constexpr Vector3 operator*(const float scale) const noexcept
	{
		return Vector3(x * scale, y * scale, z * scale);
	}

	constexpr Vector3 operator/(const float scale) const noexcept
	{
		return Vector3(x / scale, y / scale, z / scale);
	}

	constexpr float operator[](const size_t index) const
	{
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		throw std::out_of_range("Index out of range for Vector3");
	}

	float Distance(const Vector3& other) const noexcept
	{
		return std::sqrtf((x - other.x) * (x - other.x) +
			(y - other.y) * (y - other.y) +
			(z - other.z) * (z - other.z));
	}

	bool IsEqual(const Vector3& other, const float margin = std::numeric_limits<float>::epsilon()) const noexcept
	{
		return (std::fabsf(x - other.x) < margin &&
			std::fabsf(y - other.y) < margin &&
			std::fabsf(z - other.z) < margin);
	}

	constexpr Vector3 Scale(const float scale) const noexcept
	{
		return Vector3{ x * scale, y * scale, z * scale };
	}

	float Length() const noexcept
	{
		return std::sqrtf(x * x + y * y + z * z) ;
	}

	float Dot(const Vector3& Other) const {
		return x * Other.x + y * Other.y + z * Other.z;
	}
	float x, y, z;

	
};

struct Vector2
{
public:
	float x, y;

	Vector2() { x = y = 0; }
	Vector2(const float x, const float y) : x(x), y(y) {}
	Vector2 operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2 operator / (const float& rhs) const { return Vector2(x / rhs, y / rhs); }
	Vector2& operator += (const Vector2& rhs) { return *this = *this + rhs; }
	Vector2& operator -= (const Vector2& rhs) { return *this = *this - rhs; }
	Vector2& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector2& operator /= (const float& rhs) { return *this = *this / rhs; }
	
	float operator[](int i) const {
		return ((float*)this)[i];
	}

	float& operator[](int i);
	float dot() const { return x * x + y * y; }
	float length() const { return sqrtf(dot()); }
};

