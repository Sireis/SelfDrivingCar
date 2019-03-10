#pragma once
#include "stdafx.h"

class Environment
{
public:

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
} Vec2;