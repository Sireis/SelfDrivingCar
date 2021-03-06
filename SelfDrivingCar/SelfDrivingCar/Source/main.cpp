#include "stdafx.h"
#include <iostream>

#include "Drawable.h"
#include "Updateable.h"
#include "Listed.h"
#include "ListProcessor.h"
#include "Scene.h"

int load_shader_from_file (const char * path_to_file, GLenum shader_type, GLuint *shader_object_will_be_here);
void print_gl_errors ();

void glfw_error_callback (int error, const char* description)
{
	std::cout << "(glfw) ERROR: " << description << std::endl;
}

static void resize_callback (GLFWwindow* window, int width, int height)
{
	float ratio = (float) height / (float) width;
	Environment::aspect_ratio = ratio;
	Environment::screen_height = height;
	Environment::screen_width = width;

	glViewport (0, 0, width, height);

	unsigned int uniform_location = glGetUniformLocation (Environment::shader.ID, "aspect_ratio");
	glUniform1f (uniform_location, ratio);
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

	glfwWindowHint (GLFW_SAMPLES, 16);
	GLFWwindow* window = glfwCreateWindow (1536, 864, "Back on Track", NULL, NULL);
	Environment::window = window;
	glfwSetKeyCallback (window, glfw_key_callback);
	glfwSetWindowSizeCallback (window, resize_callback);
	
	if (!window)
	{
		std::cout << "(glfw) ERROR: glfwCreateWindow() failed for some reason." << std::endl;
	}

	glfwMakeContextCurrent (window);
	glEnable (GL_MULTISAMPLE);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval (1);
	
	if (glewInit () != GLEW_OK)
	{
		std::cout << "(glew) ERROR: glewInit() failed, guess we die." << std::endl;
	}

	GLuint vertexShader, fragmentShader;
	load_shader_from_file ("..\\Source\\OpenGL\\vertexShader.glsl", GL_VERTEX_SHADER, &vertexShader);
	load_shader_from_file ("..\\Source\\OpenGL\\fragmentShader.glsl", GL_FRAGMENT_SHADER, &fragmentShader);
	GLuint shaderProgram = glCreateProgram ();
	Environment::shader.ID = shaderProgram;
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

	GLuint VAO;
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);

	glClearColor (0.7f, 0.7f, 0.7f, 0.5f);

	Scene *scene = new Scene();

	double t_ = glfwGetTime ();
	double t;
	double dt = 0.0;

	int width, height;
	resize_callback (window, 1536, 864);

	srand (time (NULL));

	while (!glfwWindowShouldClose(window))
	{
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		t = glfwGetTime ();
		dt = t - t_;
		t_ = t;
		
		if (dt > 0.030)
		{
			std::cout << "(application) WARNING: Frametime is longer than expected. (" << dt << "s)" << std::endl;
		}	

		dt = 0.016;

		ListProcessor::update (dt);

		glfwGetFramebufferSize (window, &width, &height);
		glViewport (0, 0, width, height);

		print_gl_errors ();

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
	int length = (int) file.tellg ();
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

void print_gl_errors ()
{
	GLenum err;

	while ((err = glGetError ()) != GL_NO_ERROR)
	{
		std::cout << "(OpenGL) ERROR Queue: " << err << std::endl;
	}
}