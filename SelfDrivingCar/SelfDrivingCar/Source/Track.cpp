#include "stdafx.h"
#include "Track.h"


Track::Track (Vec2 start)
	:
	last_point(start),
	very_last_point(start)
{
}

Track::~Track ()
{
}

void Track::add (Vec2 point)
{
	if (last_point == very_last_point)
	{
		last_point = point;
		float f = (last_point - very_last_point).angle ();
		this->p = 3.1415926535 / 2.0f + f;
	}
	else
	{
		Drawing::Rectangle *dot;

		float color[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
		float green[4] = { 0.0f,0.8f,0.0f,0.5f };
		float red[4] = { 0.8f,0.0f,0.0f,0.5f };
		float blue[4] = { 0.0f, 0.0f, 0.8f, 0.5f };

		dot = new Drawing::Rectangle (point, Vec2 (0.01, 0.01), color);
		dot->set_level (21);
		dot = new Drawing::Rectangle (last_point, Vec2 (0.01, 0.01), color);
		dot->set_level (21);
		dot = new Drawing::Rectangle (very_last_point, Vec2 (0.01, 0.01), color);
		dot->set_level (21);

		Vec2 l1 = very_last_point + (Vec2(0.0, -1.0).rotate (this->p) * width / 2.0f);
		Vec2 r1 = very_last_point + (Vec2(0.0, +1.0).rotate (this->p) * width / 2.0f);

		Line *line1 = new Line (very_last_point, (point - very_last_point));
		Vec2 d2 = line1->closest_approach (last_point);
		float p1 = (point - very_last_point).angle ();
		float p2 = (d2 - last_point).angle ();
		float f;
		(p2 - p1) > 0 ? f = 1.0f : f = -1.0f;
		if (p2 >= 0)
		{
			if (p1 >= 3.1415926535 / 2 && p1 >= -3.1415926535 / 2)
			{
				f = -1.0;
			}
			else
			{
				f = 1.0;
			}
		}
		else
		{
			if (p1 <= -3.1415926535 / 2 && p1 <= 3.1415926535 / 2)
			{
				f = -1.0;
			}
			else
			{
				f = 1.0;
			}
		}

		Vec2 l2 = last_point - (d2 - last_point).normalize() * (f * width / 2.0f);
		Vec2 r2 = last_point + (d2 - last_point).normalize() * (f * width / 2.0f);

		this->p = (r2 - last_point).angle();

		Vec2 l3 = point + ((point - last_point).normalize ().rotate (-3.1415926535 / 2.0f) * width / 2.0f);
		Vec2 r3 = point + ((last_point - point).normalize ().rotate (-3.1415926535 / 2.0f) * width / 2.0f);
		

		dot = new Drawing::Rectangle (d2, Vec2 (0.03, 0.03), blue);
		dot->set_level (20);
		dot = new Drawing::Rectangle (l1, Vec2 (0.02, 0.02), green);
		dot->set_level (20);
		dot = new Drawing::Rectangle (l2, Vec2 (0.02, 0.02), green);
		dot->set_level (20);
		dot = new Drawing::Rectangle (l3, Vec2 (0.02, 0.02), green);
		dot->set_level (20);
		
		dot = new Drawing::Rectangle (r1, Vec2 (0.02, 0.02), red);
		dot->set_level (20);
		dot = new Drawing::Rectangle (r2, Vec2 (0.02, 0.02), red);
		dot->set_level (20);
		dot = new Drawing::Rectangle (r3, Vec2 (0.02, 0.02), red);
		dot->set_level (20);

		delete_last ();
		delete_last ();

		Wall *last_left = new Wall (l1, l2);
		Wall *last_right = new Wall (r1, r2);

		Wall *left = new Wall (l2, l3);
		Wall *right = new Wall (r2, r3);

		Collidable::add (last_left); Collidable::add (last_right);
		Collidable::add (left); Collidable::add (right);

		very_last_point = last_point;
		last_point = point;
	}
}
