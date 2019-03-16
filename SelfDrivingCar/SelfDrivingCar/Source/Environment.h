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
};

typedef struct Vec2 {
	float x;
	float y;
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

	float abs ()
	{
		return sqrt (x*x + y*y);
	}

	float angle ()
	{
		return acos (y / (sqrt (x * x + y * y)));
	}
} Vec2;