#include "stdafx.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Car.h"


Scene::Scene ()
{
	track = new Track (Vec2 (-1.00f, -0.30f));

	track->add (Vec2 (-1.00f, -0.20f));
	track->add (Vec2 (-1.00f, -0.10f));
	track->add (Vec2 (-1.00f, -0.00f));
	track->add (Vec2 (-1.05f, +0.10f));
	track->add (Vec2 (-1.15f, +0.20f));
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
	Drawing::Rectangle *test;
	test = new Drawing::Rectangle (Vec2 (0.5f, 0.0f), Vec2 (0.3f, 0.3f), Environment::blue);
	test->set_level (5);
	test = new Drawing::Rectangle (Vec2 (0.6f, 0.1f), Vec2 (0.3f, 0.3f), Environment::red);
	test->set_level (0);
}

Scene::~Scene ()
{
}

void Scene::update (const double & dt)
{
	static int lmb = 0;
	int w_state = glfwGetKey (Environment::window, GLFW_KEY_W) || glfwGetKey (Environment::window, GLFW_KEY_UP);
	int a_state = glfwGetKey (Environment::window, GLFW_KEY_A) || glfwGetKey (Environment::window, GLFW_KEY_LEFT);
	int s_state = glfwGetKey (Environment::window, GLFW_KEY_S) || glfwGetKey (Environment::window, GLFW_KEY_DOWN);
	int d_state = glfwGetKey (Environment::window, GLFW_KEY_D) || glfwGetKey (Environment::window, GLFW_KEY_RIGHT);
	int left_button_state = glfwGetMouseButton (Environment::window, GLFW_MOUSE_BUTTON_LEFT);
	
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

	if (left_button_state == GLFW_PRESS && lmb == 0)
	{
		double xpos, ypos;
		glfwGetCursorPos (Environment::window, &xpos, &ypos);
		xpos = (xpos - Environment::screen_width /2) / (Environment::screen_width / 2);
		ypos = -(ypos - Environment::screen_height /2) / (Environment::screen_height / 2);
		xpos /= Environment::aspect_ratio;
		track->add (Vec2 ((float) xpos, (float) ypos));
		lmb = 1;
	}

	if (left_button_state == GLFW_RELEASE)
	{
		lmb = 0;
	}
	
	n++;
	T += dt;
}
