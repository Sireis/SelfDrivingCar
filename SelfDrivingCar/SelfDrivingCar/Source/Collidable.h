#pragma once
#include "Line.h"

class Collidable
{
public:
	Collidable ();
	virtual ~Collidable ();

	std::list<Line *>* get_line_list ();

	bool collided_with (Collidable *collidable);
private:
	std::list<Drawing::Rectangle *> intersection_points;

protected:
	std::list<Line *>line_list;

	void add (Line *line);
};

