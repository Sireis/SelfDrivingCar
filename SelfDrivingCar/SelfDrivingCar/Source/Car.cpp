#include "stdafx.h"
#include "Car.h"


Car::Car ()
{
}

Car::Car (const float x, const float y, const float *rgba)
	:
	body (x, y, 0.01f, 0.25f, rgba),
	tire{ Drawing::Rectangle (x,y, 0.001f, 0.002f, black),
		  Drawing::Rectangle (x,y, 0.001f, 0.002f, black),
		  Drawing::Rectangle (x,y, 0.001f, 0.002f, black),
		  Drawing::Rectangle (x,y, 0.001f, 0.002f, black) }
{
	parts.push_back (tire[0]);
	parts.push_back (tire[1]);
	parts.push_back (tire[2]);
	parts.push_back (tire[3]);
	parts.push_back (body);
}


Car::~Car ()
{
}

void Car::accelerate ()
{
	flag.accelerate = true;
}

void Car::brake ()
{
	flag.brake = true;
}

void Car::left ()
{
	flag.left = true;
}

void Car::right ()
{
	flag.right = true;
}

void Car::update (const double & dt)
{
	if (flag.accelerate)
	{
		flag.accelerate = false;

		v += dt * pos_a;

		if (v > v_max)
		{
			v = v_max;
		}
	}

	if (flag.brake)
	{
		flag.brake = false;

		v += dt * neg_a;

		if (v < 0.0f)
		{
			v = 0.0f;
		}

	}

	if (flag.left)
	{
		flag.left = false;

		p -= dt * dp;
	}

	if (flag.right)
	{
		flag.right = false;

		p += dt * dp;
	}


	for (std::list<Drawing::Rectangle *>::iterator i = parts.begin (); i != parts.end (); i++)
	{
		(*i)->rotate (p);
		(*i)->translate (v*dt);
	}
}
