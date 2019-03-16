#pragma once
#include "Collidable.h"
class Wall : public Collidable
{
public:
	Wall (const Vec2 a, const Vec2 b);
	~Wall ();

private:
	Line *line;
	Drawing::Rectangle *rec;
};

