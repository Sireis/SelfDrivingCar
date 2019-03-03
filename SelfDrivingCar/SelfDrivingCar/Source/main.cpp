#include "OpenGL/glew.h"
#include "OpenGL/glfw3.h"
#include <iostream>

#include "Drawable.h"
#include "Updateable.h"
#include "Listed.h"
#include "ListProcessor.h"
#include "Scene.h"
#include "..\Whatever.h"

void glfw_error_callback (int error, const char* description)
{
	std::cout << "(glfw) ERROR: " << description << std::endl;
}

/*! GLFW_key: number of key pressed as GLFW recognizes it
 *	SYSTEM_key: number of key as GLFW might not recognize it
 *	action: GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
 *	modifier: number of modifier key pressed, alt, ctrl, etc.
 */
void glfw_key_callback (GLFWwindow* window, int GLFW_key, int SYSTEM_key, int action, int modifier)
{
	if (GLFW_key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		glfwSetWindowShouldClose (window, true);
	}
}

int main ()
{
	std::cout << "stdio is working" << std::endl;

	if (!glfwInit ())
	{
		std::cout << "(glfw) ERROR: glfwInit() failed for some reason." << std::endl;
	}

	glfwSetErrorCallback (glfw_error_callback);

	GLFWwindow* window = glfwCreateWindow (1536, 864, "Back on Track", NULL, NULL);
	glfwSetKeyCallback (window, glfw_key_callback);
	
	if (!window)
	{
		std::cout << "(glfw) ERROR: glfwCreateWindow() failed for some reason." << std::endl;
	}

	glfwMakeContextCurrent (window);
	glfwSwapInterval (1);
	
	Scene *scene = new Scene();

	double t_ = glfwGetTime ();
	double t;
	double dt = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		t = glfwGetTime ();
		dt = t - t_;
		t_ = t;

		ListProcessor::update (dt);

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwDestroyWindow (window);
}
