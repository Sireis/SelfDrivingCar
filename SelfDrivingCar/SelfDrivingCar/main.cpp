#include "Source/OpenGL/glew.h"
#include "Source/OpenGL/glfw3.h"
#include <iostream>

void glfw_error_callback (int error, const char* description)
{
	std::cout << "(glfw) ERROR: " << description << std::endl;
}

int main ()
{
	if (!glfwInit ())
	{
		std::cout << "(glfw) ERROR: glfwInit failed for some reason." << std::endl;
	}

	glfwSetErrorCallback (glfw_error_callback);

	GLFWwindow* window = glfwCreateWindow (1536, 864, "Back on Track", NULL, NULL);
	if (!window)
	{
		std::cout << "(glfw) ERROR: glfwCreateWindow failed for some reason." << std::endl;
	}

	while (1)
	{

	}
}
