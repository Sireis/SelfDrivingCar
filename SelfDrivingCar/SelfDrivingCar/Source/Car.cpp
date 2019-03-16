#include "stdafx.h"
#include "Car.h"

Car::Car ()
{
}

Car::Car (const float x, const float y, const float *rgba)
{
	body = new Drawing::Rectangle (x, y, width, height, rgba);

	tire[0] = new Drawing::Rectangle (- (width / 2),+ (height / 3), 0.009f, 0.015f, black);
	tire[1] = new Drawing::Rectangle (+ (width / 2),+ (height / 3), 0.009f, 0.015f, black);
	tire[2] = new Drawing::Rectangle (- (width / 2),- (height / 3), 0.009f, 0.015f, black);
	tire[3] = new Drawing::Rectangle (+ (width / 2),- (height / 3), 0.009f, 0.015f, black);

	bounds[0] = new Line (Vec2 (- (width / 2), - (height / 2)), Vec2 (0, 1), Vec2 (0.0, height), body);
	bounds[1] = new Line (Vec2 (- (width / 2), - (height / 2)), Vec2 (1, 0), Vec2 (0.0, width), body);
	bounds[2] = new Line (Vec2 (+ (width / 2), + (height / 2)), Vec2 (0, -1), Vec2 (0.0, height), body);
	bounds[3] = new Line (Vec2 (+ (width / 2), + (height / 2)), Vec2 (-1, 0), Vec2 (0.0, height), body);



	for (int i = 0; i < 4; i++)
	{
		tire[i]->set_parent (body);
		tire[i]->set_level (-1);

		add (bounds[i]);
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

void Car::update (const double & dt)
{
	if (flag.accelerate)
	{
		v += dt * pos_a;

		if (v > v_max)
		{
			v = v_max;
		}
	}

	if (flag.brake)
	{
		v -= dt * neg_a;

		if (v < 0.0f)
		{
			v = 0.0f;
		}

	}

	if (flag.left)
	{
		if (v != 0.0f)
		{
			p -= dt * dp;
		}

		tire[0]->rotate (-3.141592653589793238462644832379 / 6);
		tire[1]->rotate (-3.141592653589793238462644832379 / 6);
	}

	if (flag.right)
	{
		if (v != 0.0f)
		{
			p += dt * dp;
		}

		tire[0]->rotate (3.141592653589793238462644832379 / 6);
		tire[1]->rotate (3.141592653589793238462644832379 / 6);
	}

	if (flag.left == flag.right)
	{
		tire[0]->rotate (0.0f);
		tire[1]->rotate (0.0f);
	}

	reset_flags ();

	body->rotate (p);
	body->translate (0, v*dt);

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
