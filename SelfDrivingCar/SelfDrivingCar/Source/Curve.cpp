#include "stdafx.h"
#include "Curve.h"


Curve::Curve (Vec2 start, float width)
	:
	last_point (start),
	width(width)
{
	
}


Curve::~Curve ()
{
}

void Curve::add (Vec2 point)
{
	Drawing::Rectangle *line = new Drawing::Rectangle (point + (point - last_point) / 2, Vec2 (width, (point - last_point).abs ()), Environment::black);
	line->rotate ((point- last_point).angle());
	last_point = point;
}
