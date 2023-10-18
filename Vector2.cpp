#include "Vector2.h"
#include <cmath>


Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}

Vector2 Vector2::normalize() const {
	float length = std::sqrt(x * x + y * y);
	if (length != 0.0f)
		return Vector2(x / length, y / length);
	else
		return Vector2(0, 0);
}

float Vector2::dot(const Vector2 other) const {
	return x * other.x + y * other.y;
}

float Vector2::cross(const Vector2 other) const {
	return x * other.y - y * other.x;
}

Vector2 Vector2::operator*(float scalar) const {
	return Vector2(x * scalar, y * scalar);
}
