#include "stdafx.h"
#include "Environment.h"
#include "Line.h"


Environment::ShaderInfo Environment::shader;
GLFWwindow *Environment::window;
std::list<Line *> Environment::line_list;