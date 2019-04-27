#pragma once
#include "Rectangle.h"

class Curve
{
public:
	Curve (Vec2 start, float width);
	~Curve ();

	void add (Vec2 point);

private:
	Vec2 last_point;
	float width;
};

