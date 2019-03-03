#include "stdafx.h"
#include <iostream>

#include "Drawable.h"
#include "Updateable.h"
#include "Listed.h"
#include "ListProcessor.h"
#include "Scene.h"
#include "..\Whatever.h"

int load_shader_from_file (const char * path_to_file, GLenum shader_type, GLuint *shader_object_will_be_here);

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
	
	if (glewInit () != GLEW_OK)
	{
		std::cout << "(glew) ERROR: glewInit() failed, guess we die." << std::endl;
	}

	GLuint vertexShader, fragmentShader;
	load_shader_from_file ("Source\\OpenGL\\vertexShader.glsl", GL_VERTEX_SHADER, &vertexShader);
	load_shader_from_file ("Source\\OpenGL\\fragmentShader.glsl", GL_FRAGMENT_SHADER, &fragmentShader);
	GLuint shaderProgram = glCreateProgram ();
	glAttachShader (shaderProgram, vertexShader);
	glAttachShader (shaderProgram, fragmentShader);
	glLinkProgram (shaderProgram);

	int success = 0;
	char info[512];
	glGetProgramiv (shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog (shaderProgram, 512, nullptr, info);
		std::cout << "(OpenGL) ERROR: linking shaders failed:\n" << info << std::endl;
	}

	glUseProgram (shaderProgram);
	glDeleteShader (vertexShader);
	glDeleteShader (fragmentShader);

	GLuint VAO, VBO;
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);

	glClearColor (0.0, 0.0, 0.5, 0.5);

	Scene *scene = new Scene();

	double t_ = glfwGetTime ();
	double t;
	double dt = 0.0;

	int width, height;

	while (!glfwWindowShouldClose(window))
	{
		t = glfwGetTime ();
		dt = t - t_;
		t_ = t;

		ListProcessor::update (dt);

		glfwGetFramebufferSize (window, &width, &height);
		glViewport (0, 0, width, height);

		glClear (GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwDestroyWindow (window);
	glfwTerminate ();
	exit (EXIT_SUCCESS);
}


int load_shader_from_file (const char * path_to_file, GLenum shader_type, GLuint *shader_object_will_be_here)
{
	std::ifstream file (path_to_file);
	if (file.fail ())
	{
		return GetLastError ();
	}

	file.seekg (0, file.end);
	int length = file.tellg ();
	file.seekg (0, file.beg);

	char* buffer = new char[length + 1];
	buffer[length] = '\0';
	file.read (buffer, length);
	file.close ();

	for (int i = length; buffer[i] < 'A' || buffer[i] > '}'; i--)
	{
		buffer[i] = '\0';
	}

	*shader_object_will_be_here = glCreateShader (shader_type);
	glShaderSource (*shader_object_will_be_here, 1, &buffer, nullptr);
	glCompileShader (*shader_object_will_be_here);
	int success = 0;
	char info[512];
	glGetShaderiv (*shader_object_will_be_here, GL_COMPILE_STATUS, &success);


	if (!success)
	{
		glGetShaderInfoLog (*shader_object_will_be_here, 512, nullptr, info);
		std::cout << "ERROR while compiling shader:\n" << buffer << "\n-------------\n" << info << std::endl;
		return -1;
	}

	delete[] buffer;

	return 0;
}