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
	}
	else
	{
		float p1 = (point - last_point).angle ();
		float p2 = (very_last_point - last_point).angle ();
		float p_ = (p2 - p1) / 2.0f;

		float color[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
		float green[4] = { 0.0f,0.8f,0.0f,0.5f };
		float red[4] = { 0.8f,0.0f,0.0f,0.5f };

		new Drawing::Rectangle (point, Vec2 (0.01, 0.01), color);
		new Drawing::Rectangle (last_point, Vec2 (0.01, 0.01), color);
		new Drawing::Rectangle (very_last_point, Vec2 (0.01, 0.01), color);

		Vec2 l1 = very_last_point + ((very_last_point - last_point).normalize ().rotate (this->p) * width / 2.0f);
		new Line(very_last_point, (very_last_point - last_point).normalize ().rotate (this->p) * width / 2.0f);
		Vec2 l2 = last_point + ((last_point - point).normalize ().rotate (p_) * width / 2.0f);
		new Line(last_point, (last_point - point).normalize ().rotate (p_) * width / 2.0f);
		Vec2 l3 = point + ((point - last_point).normalize ().rotate (-3.1415926535 / 2.0f) * width / 2.0f);
		new Line(point, (point - last_point).normalize ().rotate (-3.1415926535 / 2.0f) * width / 2.0f);

		Vec2 r1 = very_last_point + ((last_point - very_last_point).normalize ().rotate (this->p) * width / 2.0f);
		new Line (very_last_point, (last_point - very_last_point).normalize ().rotate (this->p) * width / 2.0f);
		Vec2 r2 = last_point + ((point - last_point).normalize ().rotate (p_) * width / 2.0f);
		new Line (last_point, (point - last_point).normalize ().rotate (p_) * width / 2.0f);
		Vec2 r3 = point + ((last_point - point).normalize ().rotate (-3.1415926535 / 2.0f) * width / 2.0f);
		new Line (point, (last_point - point).normalize ().rotate (-3.1415926535 / 2.0f) * width / 2.0f);

		Drawing::Rectangle *dot;
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

		this->p = p_;
		very_last_point = last_point;
		last_point = point;
	}
}
