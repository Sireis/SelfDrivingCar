#include "stdafx.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Car.h"


Scene::Scene ()
{
}


Scene::~Scene ()
{
}

void Scene::update (const double & dt)
{
	int w_state = glfwGetKey (Environment::window, GLFW_KEY_W);
	int a_state = glfwGetKey (Environment::window, GLFW_KEY_A);
	int s_state = glfwGetKey (Environment::window, GLFW_KEY_S);
	int d_state = glfwGetKey (Environment::window, GLFW_KEY_D);

	if (n == 0)
	{
		float color1[] = { 0.0f, 1.0f, 0.0f, 0.5f };
		float color2[] = { 1.0f, 0.0f, 0.0f, 0.5f };
		car = new Car (0.0f, 0.0f, color2);
		car->accelerate ();
	}

	if ( w_state == GLFW_PRESS)
	{
		car->accelerate ();
	}
	if (s_state == GLFW_PRESS)
	{
		car->brake ();
	}
	if (a_state == GLFW_PRESS)
	{
		car->left ();
	}
	if (d_state == GLFW_PRESS)
	{
		car->right ();
	}
	
	n++;
	T += dt;
}
