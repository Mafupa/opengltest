#ifndef VECTOR_2
#define VECTOR_2

class Vector2 {
public:
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f);

	Vector2 normalize() const;

	float dot(const Vector2 other) const;

	float cross(const Vector2 other) const;

	Vector2 operator*(float scalar) const;
};

#endif
