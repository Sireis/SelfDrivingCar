#pragma once
#include "stdafx.h"

class Environment
{
public:
	static unsigned long number_update_cycle;

	struct ShaderInfo {
		GLuint ID;
		const unsigned int vertex_buffer_line_length = 9;
	};

	static ShaderInfo shader;

	static GLFWwindow *window;

	static const float black[];
	static const float red[];
	static const float dark_red[];
	static const float green[];
	static const float dark_green[];
	static const float blue[];
	static const float dark_blue[];
	static const float white[];
	static const float transparent[];

	static float aspect_ratio;
	static int screen_width;
	static int screen_height;
};

typedef struct Vec2 {
	float x;
	float y;
	Vec2()
	{}
	Vec2 (float x, float y) : x(x), y(y)
	{}

	Vec2 operator+(const Vec2 &v2) const
	{
		return Vec2 (x + v2.x, y + v2.y);
	}

	Vec2 operator-(const Vec2 &v2) const
	{
		return Vec2 (x - v2.x, y - v2.y);
	}

	Vec2 operator/(const float d) const
	{
		return Vec2 (x / d, y / d);
	}

	Vec2 operator*(const float f) const
	{
		return Vec2 (x * f, y * f);
	}

	bool operator==(const Vec2 &v2) const
	{
		return this->x == v2.x && this->y == v2.y;
	}

	/*! Since cross product of 2D-Vector only gives
		z-component that is non zero this method 
		gives only a float */
	float cross_product (const Vec2 &v2) const
	{
		return v2.x * this->y - v2.y * this->x;
	}

	float abs () const
	{
		return sqrt (x*x + y*y);
	}

	float angle () const
	{
		float f = acos (y / (sqrt (x * x + y * y)));
		(x < 0) ? f = -f : f = f;
		return f;
	}

	float angle (const Vec2 &v2) const
	{
		float f = acos (x * v2.x + y * v2.y / (sqrt (x * x + y * y) * sqrt (v2.x * v2.x + v2.y * v2.y)));
		(x < 0) ? f = -f : f = f;
		return f;
	}

	Vec2 normalize () const
	{
		float f = sqrt (x*x + y*y);
		return Vec2 (x / f, y / f);
	}

	Vec2 rotate (const float rad) const
	{
		float r[4] = { 1.0, 0.0, 1.0, 0.0 };

		r[0] = cos (rad);
		r[1] = sin (rad);
		r[2] = -sin (rad);
		r[3] = cos (rad);

		float f[2] = { 0.0, 0.0 };
		f[0] = x; f[1] = y;

		MatrixMath::multiply_m2x2_v2 (r, f, f);

		return Vec2 (f[0], f[1]);
	}

} Vec2;