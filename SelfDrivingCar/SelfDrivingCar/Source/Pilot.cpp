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
	if (car != nullptr)
	{
		car->dispose ();
	}
}

void Pilot::update (const double & dt)
{
	if (driving)
	{
		distances[0] = car->get_distance (track, 0);
		distances[1] = car->get_distance (track, 1);
		distances[2] = car->get_distance (track, 2);
		distances[3] = car->get_distance (track, 3);
		distances[4] = car->get_distance (track, 4);
		distances[5] = car->get_velocity ();

		T += dt;

		index_now = track->nearest_point (car->get_position ());

		if (index_now > (index_before + 60))
		{
			going_forward = false;
		}

		if (index_now == 0 && index_before > 20)
		{
			lap_counter++;
				lap_time = T;
				T = 0;
			if (callee != nullptr && lap_finished_callout != nullptr)
			{
				lap_finished_callout (callee, *this, lap_counter);
			}
		}

		index_before = index_now;

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

		if (car->collided_with (track, index_now))
		{
			car->stop ();
			if( callee != nullptr && crashed_callout != nullptr)
			{
				crashed_callout (callee, *this);
			}
		}
	}
}

void Pilot::give_new_car (Car * car)
{
	//this->car->dispose ();
	this->car = car;
}

bool Pilot::wrong_direction ()
{
	return !going_forward;
}

float Pilot::get_laptime ()
{
	return lap_time;
}

void Pilot::do_drive (bool yes_no)
{
	driving = yes_no;
}

void Pilot::register_lap_finished (lap_finished_callback ptr, void *obj)
{
	lap_finished_callout = ptr;
	callee = obj;
}

void Pilot::register_crashed (crashed_callback ptr, void * obj)
{
	crashed_callout = ptr;
	callee = obj;
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
