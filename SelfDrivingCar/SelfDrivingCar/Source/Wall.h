#pragma once
#include "Collidable.h"
class Wall : public Collidable
{
public:
	Wall (const Vec2 a, const Vec2 b);
	~Wall ();

	Vec2 &get_start ();
	Vec2 &get_end ();

private:
	Vec2 a, b;
	Line *line;
	Drawing::Rectangle *rec;
};

