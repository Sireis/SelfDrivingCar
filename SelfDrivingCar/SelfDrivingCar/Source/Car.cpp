#include "stdafx.h"
#include "Car.h"

Car::Car ()
{
}

Car::Car (const float x, const float y, const float *rgba)
{
	body = new Drawing::Rectangle (x, y, width, height, rgba);
	tire[0] = new Drawing::Rectangle (x - (width / 2), y + (height / 3), 0.008f, 0.012f, black);
	tire[1] = new Drawing::Rectangle (x + (width / 2), y + (height / 3), 0.008f, 0.012f, black);
	tire[2] = new Drawing::Rectangle (x - (width / 2), y - (height / 3), 0.008f, 0.012f, black);
	tire[3] = new Drawing::Rectangle (x + (width / 2), y - (height / 3), 0.008f, 0.012f, black);

	tire[0]->set_pivot (+(width / 2), - (height / 3));
	tire[1]->set_pivot (-(width / 2), - (height / 3));
	tire[2]->set_pivot (+(width / 2), + (height / 3));
	tire[3]->set_pivot (-(width / 2), + (height / 3));

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

		v -= dt * neg_a;

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
		(*i)->translate (0, v*dt);
	}
}
