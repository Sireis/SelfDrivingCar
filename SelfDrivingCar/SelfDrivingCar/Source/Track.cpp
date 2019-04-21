#include "stdafx.h"
#include "Track.h"


Track::Track (Vec2 start)
	:
	last_point(start),
	very_last_point(start)
{
	point_list.push_back (start);
}

Track::~Track ()
{
}

void Track::add (Vec2 point)
{
	Drawing::Rectangle *dot;
	dot = new Drawing::Rectangle (point, Vec2 (0.03f, 0.03f), Environment::black);

	std::cout << "x: " << point.x << " \t|\t y: " << point.y << std::endl;
	point_list.push_back (point);

	if (last_point == very_last_point)
	{
		const float *color;
		last_point = point;
		float f = (last_point - very_last_point).angle ();
		this->p = 3.1415926535f / 2.0f + f;

		float l = (width - 0.025f) / 10;
		Drawing::Rectangle *marker = new Drawing::Rectangle (very_last_point, Vec2 (width - 0.025f, l*3), Environment::black);
		marker->rotate ((point - very_last_point).angle ());

		float x, y;
		float b;
		for (int j = 0; j < 3; ++j)
		{
			(j % 2 == 0) ? b = 1 : b = 0;
			for (int i = 0; i < 9; ++i)
			{
				(i % 2 == 0) ? color = Environment::white : color = Environment::black;
				Drawing::Rectangle *rec;
				x = -(width - 0.025f) / 2.0f + 0.5f*l + l*i + l*b;
				y = (width - 0.025f) / 10.0f * 1.5f - 0.5f*l - l*j;
				rec = new Drawing::Rectangle (Vec2 (x, y), Vec2 ((width - 0.025f) / 10, (width - 0.025f) / 10), color, marker);
				rec->set_level (1);
				rec->tag (1);
			}
		}
	}
	else
	{		
		Vec2 l1 = very_last_point + (Vec2(0.0, -1.0).rotate (this->p) * width / 2.0f);
		Vec2 r1 = very_last_point + (Vec2(0.0, +1.0).rotate (this->p) * width / 2.0f);

		Line *line1 = new Line (very_last_point, (point - very_last_point));
		Vec2 d2 = line1->closest_approach (last_point);
		line1->dispose();

		Vec2 l2, r2;
		float s;
		float f = (point - very_last_point).cross_product (d2 - last_point);
		if (abs(f) > 0.00001f)
		{
			f > 0 ? s = 1.0f : s = -1.0f;
			l2 = last_point - (d2 - last_point).normalize () * (s * width / 2.0f);
			r2 = last_point + (d2 - last_point).normalize () * (s * width / 2.0f);
		}
		else
		{
			l2 = last_point + (last_point - very_last_point).normalize ().rotate (-3.1415926535f / 2.0f) * width / 2.0f;
			r2 = last_point + (last_point - very_last_point).normalize ().rotate (3.1415926535f / 2.0f) * width / 2.0f;
		}
		this->p = (r2 - last_point).angle ();

		Vec2 l3 = point + ((point - last_point).normalize ().rotate (-3.1415926535f / 2.0f) * width / 2.0f);
		Vec2 r3 = point + ((last_point - point).normalize ().rotate (-3.1415926535f / 2.0f) * width / 2.0f);
		
		//dot = new Drawing::Rectangle (l2, Vec2 (0.02f, 0.02f), Environment::green);
		//dot->set_level (20);
		//dot = new Drawing::Rectangle (r2, Vec2 (0.02f, 0.02f), Environment::red);
		//dot->set_level (20);

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

int Track::nearest_point (Vec2 p)
{
	float distance = 99, tmp;
	int index;

	for (int i = 0; i < point_list.size (); ++i)
	{
		tmp = (p - point_list[i]).abs ();
		if (tmp < distance)
		{
			distance = tmp;
			index = i;
		}
	}

	return index;
}
