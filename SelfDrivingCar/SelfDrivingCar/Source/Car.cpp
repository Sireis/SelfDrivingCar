#include "stdafx.h"
#include "Car.h"

Car::Car ()
{
}

Car::Car (Vec2 position, const float *rgba)
{
	curve = new Curve (position, 0.005);
	body = new Drawing::Rectangle (position, Vec2(width, height), rgba);
	body->set_level (10);

	tire[0] = new Drawing::Rectangle (-(width / 2), +(height / 3), 0.009f, 0.015f, Environment::black);
	tire[1] = new Drawing::Rectangle (+(width / 2), +(height / 3), 0.009f, 0.015f, Environment::black);
	tire[2] = new Drawing::Rectangle (-(width / 2), -(height / 3), 0.009f, 0.015f, Environment::black);
	tire[3] = new Drawing::Rectangle (+(width / 2), -(height / 3), 0.009f, 0.015f, Environment::black);

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

	for (int i = 0; i < 4; ++i)
	{
		tire[i]->set_parent (body);
		tire[i]->set_level (9);

		add (bounds[i]);
		bounds[i]->visible (false);
		sensors[i]->visible (false);
	}
	sensors[4]->visible (false);
}


Car::~Car ()
{
	body->dispose ();
	for (int i = 0; i < 4; ++i)
	{
		tire[i]->dispose ();
		bounds[i]->dispose ();
	}

	for (int i = 0; i < 5; ++i)
	{
		sensors[i]->dispose ();
	}
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

float Car::get_distance (Collidable *track, int sensor)
{
	std::vector<Collidable *> *list = track->get_collidable_list ();
	std::vector<Line *> *inner;

	float tmp, f = std::numeric_limits<float>::infinity ();
	bool b1, b2;
	const float *color = nullptr;

	for (std::vector<Collidable *>::iterator i = list->begin (); i != list->end (); ++i)
	{
		inner = (*i)->get_line_list ();
		if (inner->size () == 1)
		{
			Line *line = inner->front ();
			
			if (line->collision (sensors[sensor]))
			{
				tmp = line->distance (sensors[sensor]).y;
				if (tmp > 0)
				{
					tmp < f ? f = tmp : f = f;
				}
			}
		}
		else
		{
			for (std::vector<Line *>::iterator j = inner->begin (); j != inner->end (); ++j)
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

	return f;
}

Vec2 Car::get_position ()
{
	float tmp[2];
	body->get_middle (tmp);
	return Vec2 (tmp[0], tmp[1]);
}

void Car::set_position (const Vec2 & position)
{
	body->set_position (position);
	v = 0.0f;
	p = 0.0f;
	flag.brake = true;
	update (0);
}

float Car::get_velocity ()
{
	return v;
}

void Car::stop ()
{
	v = 0.0f;
	flag.stop = true;
}

void Car::update (const double & dt)
{
	if (!flag.stop)
	{
		if (flag.accelerate)
		{
			v += (float)(dt * pos_a);

			if (v > v_max)
			{
				v = v_max;
			}
		}

		if (flag.brake)
		{
			v -= (float)(dt * neg_a);

			if (v < 0.0f)
			{
				v = 0.0f;
			}

			for (int i = 0; i < 4; ++i)
			{
				tire[i]->set_color (Environment::red);
			}
			tires_are_black = false;
		}
		else
		{
			if (!tires_are_black)
			{
				for (int i = 0; i < 4; ++i)
				{
					tire[i]->set_color (Environment::black);
				}
				tires_are_black = true;
			}
		}

		if (flag.left)
		{
			if (v != 0.0f)
			{
				p -= (float)(dt * dp);
			}

			tire[0]->rotate (-3.141592653589793238462644832379f / 6);
			tire[1]->rotate (-3.141592653589793238462644832379f / 6);
		}

		if (flag.right)
		{
			if (v != 0.0f)
			{
				p += (float)(dt * dp);
			}

			tire[0]->rotate (3.141592653589793238462644832379f / 6);
			tire[1]->rotate (3.141592653589793238462644832379f / 6);
		}

		if (flag.left == flag.right)
		{
			tire[0]->rotate (0.0f);
			tire[1]->rotate (0.0f);
		}
		
		float position[2];
		body->rotate (p);
		body->translate (0.0f, (float)(v*dt));
		body->get_middle (position);
		//curve->add (Vec2(position[0], position[1]));
	}

	reset_flags ();
}

void Car::reset_flags ()
{
	flag.accelerate = false;
	flag.brake = false;
	flag.left = false;
	flag.right = false;
	flag.stop = false;
}

void Car::set_level (const char z)
{
	body->set_level (z);
}
