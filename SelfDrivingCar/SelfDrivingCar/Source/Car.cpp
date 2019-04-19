#include "stdafx.h"
#include "Car.h"

Car::Car ()
{
}

Car::Car (const float x, const float y, const float *rgba)
{
	body = new Drawing::Rectangle (x, y, width, height, rgba);
	body->set_level (10);

	tire[0] = new Drawing::Rectangle (-(width / 2), +(height / 3), 0.009f, 0.015f, black);
	tire[1] = new Drawing::Rectangle (+(width / 2), +(height / 3), 0.009f, 0.015f, black);
	tire[2] = new Drawing::Rectangle (-(width / 2), -(height / 3), 0.009f, 0.015f, black);
	tire[3] = new Drawing::Rectangle (+(width / 2), -(height / 3), 0.009f, 0.015f, black);

	bounds[0] = new Line (Vec2 (-(width / 2), -(height / 2)), Vec2 (0, 1), Vec2 (height, 0.0f), body);
	bounds[1] = new Line (Vec2 (- (width / 2), - (height / 2)), Vec2 (1, 0), Vec2 (width, 0.0f), body);
	bounds[2] = new Line (Vec2 (+ (width / 2), + (height / 2)), Vec2 (0, -1), Vec2 (height, 0.0f), body);
	bounds[3] = new Line (Vec2 (+ (width / 2), + (height / 2)), Vec2 (-1, 0), Vec2 (width, 0.0f), body);

	sensors[0] = new Line (Vec2 (0, 0), -3.1415926535f / 2.0f, Vec2 (0, 0), body);
	sensors[1] = new Line (Vec2 (0, 0), -3.1415926535f / 4.0f, Vec2 (0, 0), body);
	sensors[2] = new Line (Vec2 (0, 0), 0.0f, Vec2 (0, 0), body);
	sensors[3] = new Line (Vec2 (0, 0), 3.1415926535f / 4.0f, Vec2 (0, 0), body);
	sensors[4] = new Line (Vec2 (0, 0), 3.1415926535f / 2.0f, Vec2 (0, 0), body);
	
	//add (bounds[0]);

	for (int i = 0; i < 4; i++)
	{
		tire[i]->set_parent (body);
		tire[i]->set_level (9);

		add (bounds[i]);
		bounds[i]->visible (false);
	}
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

float Car::get_distance (Track *track, int sensor)
{
	static Drawing::Rectangle *dot[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };

	if (dot[sensor] != nullptr)
	{
		dot[sensor]->dispose ();
		dot[sensor] = nullptr;
	}


	std::list<Collidable *> *list = track->get_collidable_list ();
	std::list<Line *> *inner;

	float tmp, f = std::numeric_limits<float>::infinity ();
	bool b1, b2;
	const float *color = nullptr;

	for (std::list<Collidable *>::iterator i = list->begin (); i != list->end (); i++)
	{
		inner = (*i)->get_line_list ();
		if (inner->size () == 1)
		{
			std::list<Line *>::iterator only_line = inner->begin ();
			if ((*only_line)->collision (sensors[sensor]))
			{
				tmp = (*only_line)->distance (sensors[sensor]).y;
				if (tmp > 0)
				{
					tmp < f ? f = tmp : f = f;
				}
			}
		}
		else
		{
			for (std::list<Line *>::iterator j = inner->begin (); j != inner->end (); j++)
			{
				if ((*j)->collision (sensors[sensor]))
				{
					tmp = (*j)->distance (sensors[sensor]).y;
					if (tmp > 0)
					{
						tmp < f ? f = tmp : f = f;
					}
				}
			}
		}
	}

	float middle[2], dv[2];
	sensors[sensor]->get_a (middle);
	sensors[sensor]->get_dv (dv);
	Vec2 p = Vec2 (middle[0], middle[1]) + Vec2 (dv[0], dv[1])*f;
	dot[sensor] = new Drawing::Rectangle (p, Vec2 (0.02, 0.02), Environment::green);
	dot[sensor]->set_level (50);

	return f;
}

void Car::stop ()
{
	v = 0.0f;
}

void Car::update (const double & dt)
{
	if (flag.accelerate)
	{
		v += (float) (dt * pos_a);

		if (v > v_max)
		{
			v = v_max;
		}
	}

	if (flag.brake)
	{
		v -= (float) (dt * neg_a);

		if (v < 0.0f)
		{
			v = 0.0f;
		}

	}

	if (flag.left)
	{
		if (v != 0.0f)
		{
			p -= (float) (dt * dp);
		}

		tire[0]->rotate (-3.141592653589793238462644832379f / 6);
		tire[1]->rotate (-3.141592653589793238462644832379f / 6);
	}

	if (flag.right)
	{
		if (v != 0.0f)
		{
			p += (float) (dt * dp);
		}

		tire[0]->rotate (3.141592653589793238462644832379f / 6);
		tire[1]->rotate (3.141592653589793238462644832379f / 6);
	}

	if (flag.left == flag.right)
	{
		tire[0]->rotate (0.0f);
		tire[1]->rotate (0.0f);
	}

	reset_flags ();

	body->rotate (p);
	body->translate (0.0f, (float) (v*dt));

	//for (std::list<Drawing::Rectangle *>::iterator i = parts.begin (); i != parts.end (); i++)
	//{
	//	(*i)->rotate (p);
	//	(*i)->translate (0, v*dt);
	//}
}

void Car::reset_flags ()
{
	flag.accelerate = false;
	flag.brake = false;
	flag.left = false;
	flag.right = false;
}
