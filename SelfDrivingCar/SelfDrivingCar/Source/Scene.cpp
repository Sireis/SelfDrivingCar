#include "stdafx.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Car.h"


Scene::Scene ()
{
	//wall[0] = new Wall (Vec2 (-0.5f, +0.5f), Vec2 (+0.5f, +0.5f));
	//wall[1] = new Wall (Vec2 (+0.5f, +0.5f), Vec2 (+0.5f, -0.5f));
	//wall[2] = new Wall (Vec2 (+0.5f, -0.5f), Vec2 (-0.5f, -0.5f));
	//wall[3] = new Wall (Vec2 (-0.5f, -0.5f), Vec2 (-0.5f, +0.5f));
	track = new Track (Vec2 (-0.75f, -0.7f));
	track->add (Vec2 (-0.75f, -0.6f));
	track->add (Vec2 (-0.75f, -0.5f));
	track->add (Vec2 (-0.75f, -0.4f));
	track->add (Vec2 (-0.75f, -0.3f));
	track->add (Vec2 (-0.75f, -0.2f));
	track->add (Vec2 (-0.75f, -0.1f));
	track->add (Vec2 (-0.75f, -0.0f));
	track->add (Vec2 (-0.75f, +0.1f));
	track->add (Vec2 (-0.75f, +0.2f));
	track->add (Vec2 (-0.75f, +0.3f));
	track->add (Vec2 (-0.75f, +0.4f));
	track->add (Vec2 (-0.75f, +0.5f));
	track->add (Vec2 (-0.75f, +0.6f));
	track->add (Vec2 (-0.75f, +0.7f));
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
