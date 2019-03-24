#include "stdafx.h"
#include "Wall.h"


Wall::Wall (const Vec2 a, const Vec2 b)
	:
	Collidable()
{
	float color[4] = { 1.0f, 1.0f, 1.0f, 0.5f };
	float red[4] = { 1.0f, 0.0f, 0.0f, 0.5f };
	line = new Line (a, b - a, Vec2 ((b - a).abs (), 0.0f));
	add (line);
	line->visible (false);
	rec = new Drawing::Rectangle ((a + b) / 2, Vec2 (0.025f, (b - a).abs ()), color);
	rec->rotate ((b-a).angle());
}


Wall::~Wall ()
{
	line->dispose ();
	rec->dispose ();
}
