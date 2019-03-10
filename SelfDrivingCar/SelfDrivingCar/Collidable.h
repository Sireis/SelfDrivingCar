#pragma once
#include "Line.h"
class Collidable
{
public:
	Collidable ();
	virtual ~Collidable ();

protected:
	std::list<Line *>line_list;

	void add (Line *line);
	bool collided_with (Collidable *collidable);
};

