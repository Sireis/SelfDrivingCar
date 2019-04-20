#include "stdafx.h"
#include "Pilot.h"


Pilot::Pilot ()
{
}


Pilot::Pilot (Track *track, Car * car)
	:
	track(track),
	car(car)
{
}

Pilot::~Pilot ()
{
}

void Pilot::update (const double & dt)
{
	distances[0] = car->get_distance (track, 0);
	distances[1] = car->get_distance (track, 1);
	distances[2] = car->get_distance (track, 2);
	distances[3] = car->get_distance (track, 3);
	distances[4] = car->get_distance (track, 4);

	if (determine_left ())
	{
		car->left ();
	}

	if (determine_right ())
	{
		car->right ();
	}

	if (determine_accelerate ())
	{
		car->accelerate ();
	}
	else
	{
		car->brake ();
	}

	//if (determine_brake ())
	//{
	//	car->brake ();
	//}

	if (car->collided_with (track))
	{
		car->stop ();
	}
}

bool Pilot::determine_left ()
{
	int a_state = glfwGetKey (Environment::window, GLFW_KEY_A);
	int left_state = glfwGetKey (Environment::window, GLFW_KEY_LEFT);

	if (a_state  == GLFW_PRESS || left_state == GLFW_PRESS)
	{
		return true;
	}

	return false;
}

bool Pilot::determine_right ()
{
	int d_state = glfwGetKey (Environment::window, GLFW_KEY_D);
	int right_state = glfwGetKey (Environment::window, GLFW_KEY_RIGHT);

	if (d_state == GLFW_PRESS || right_state == GLFW_PRESS)
	{
		return true;
	}

	return false;
}

bool Pilot::determine_accelerate ()
{
	int w_state = glfwGetKey (Environment::window, GLFW_KEY_W);
	int up_state = glfwGetKey (Environment::window, GLFW_KEY_UP);

	if (w_state == GLFW_PRESS || up_state == GLFW_PRESS)
	{
		return true;
	}

	return false;
}

bool Pilot::determine_brake ()
{
	int s_state = glfwGetKey (Environment::window, GLFW_KEY_S);
	int down_state = glfwGetKey (Environment::window, GLFW_KEY_DOWN);

	if (s_state == GLFW_PRESS || down_state == GLFW_PRESS)
	{
		return true;
	}

	return false;
}
