#pragma once
#include "Line.h"

class Collidable
{
public:
	Collidable ();
	virtual ~Collidable ();

	std::list<Line *>* get_line_list ();
	std::list<Collidable *>* get_collidable_list ();

	bool collided_with (Collidable *collidable);
private:
	std::list<Drawing::Rectangle *> intersection_points;

protected:
	std::list<Line *>line_list;
	std::list<Collidable *>collidable_list;

	void add (Line *line);
	void add (Collidable *collidable);
};

