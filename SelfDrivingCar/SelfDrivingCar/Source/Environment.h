#pragma once
#include "stdafx.h"

class Environment
{
public:

	struct ShaderInfo {
		GLuint ID;
	};

	static ShaderInfo shader;

	static GLFWwindow *window;
};
