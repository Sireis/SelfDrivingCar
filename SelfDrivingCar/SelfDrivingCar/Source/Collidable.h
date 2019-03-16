#pragma once
#include "Line.h"

class Collidable
{
public:
	Collidable ();
	virtual ~Collidable ();

	std::list<Line *>* get_line_list ();

protected:
	std::list<Line *>line_list;

	void add (Line *line);
	bool collided_with (Collidable *collidable);
};

