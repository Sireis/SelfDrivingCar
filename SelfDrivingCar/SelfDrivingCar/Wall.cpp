#include "stdafx.h"
#include "Wall.h"


Wall::Wall (const Vec2 a, const Vec2 b)
{
	float color[4] = {1.0f, 1.0f, 1.0f, 0.5f};
	line = new Line (a, b - a, Vec2 ((b - a).abs (), 0));
	line->visible (false);
	rec = new Drawing::Rectangle ((a + b)/2,Vec2((b-a).x, 0.025f), color);
}


Wall::~Wall ()
{
}