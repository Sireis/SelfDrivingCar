#include "stdafx.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Car.h"


Scene::Scene ()
{
	track = new Track (Vec2 (-0.50f, -0.70f));

	//track->add (Vec2 (-0.70f, -0.6f));
	//track->add (Vec2 (-0.85f, -0.3f));
	//track->add (Vec2 (-0.85f, +0.3f));
	//track->add (Vec2 (-0.70f, +0.6f));
	//track->add (Vec2 (-0.50f, +0.70f));

	//track = new Track (Vec2 (0.4f, 0.4f));
	//track->add (Vec2 (0.5f, 0.5f));
	//track->add (Vec2 (0.6f, 0.6f));
	//track->add (Vec2 (0.7f, 0.7f));
	//track->add (Vec2 (0.8f, 0.8f));
	//track->add (Vec2 (0.9f, 0.9f));
}

Scene::~Scene ()
{
}

void Scene::update (const double & dt)
{
	int w_state = glfwGetKey (Environment::window, GLFW_KEY_W) || glfwGetKey (Environment::window, GLFW_KEY_UP);
	int a_state = glfwGetKey (Environment::window, GLFW_KEY_A) || glfwGetKey (Environment::window, GLFW_KEY_LEFT);
	int s_state = glfwGetKey (Environment::window, GLFW_KEY_S) || glfwGetKey (Environment::window, GLFW_KEY_DOWN);
	int d_state = glfwGetKey (Environment::window, GLFW_KEY_D) || glfwGetKey (Environment::window, GLFW_KEY_RIGHT);

	if (n == 0)
	{
		float color1[] = { 0.0f, 1.0f, 0.0f, 0.5f };
		float color2[] = { 0.5f, 0.1f, 0.0f, 0.5f };
		
		car = new Car (0.25f, 0.25f, color2);

	track->add (Vec2 (-0.70f, -0.6f));
	}

	if (n == 1)
	{
		track->add (Vec2 (-0.85f, -0.3f));
	}
 	else if (n == 2)
	{
		track->add (Vec2 (-0.85f, +0.3f));
	}
	else if (n == 3)
	{
		track->add (Vec2 (-0.70f, +0.6f));
	}
	else if (n == 4)
	{
		track->add (Vec2 (-0.50f, +0.70f));
	}
	else if (n == 5)
	{
		track->add (Vec2 (+0.5, 0.5));
	}
	else if (n == 6)
	{
		track->add (Vec2 (0.5, -0.5));
	}
	else if (n == 7)
	{
		track->add (Vec2 (0.6, -0.6));
	}
	else if (n == 8)
	{
		track->add (Vec2 (0.8, -0.7));
	}
	else if (n == 9)
	{
		track->add (Vec2 (1.0, -0.5));
	}
	else if (n == 10)
	{
		track->add (Vec2 (1.2, -0.3));
	}
	   
		if (car->collided_with (track))
		{
			car->stop ();
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
