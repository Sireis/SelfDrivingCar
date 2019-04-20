#pragma once
#include "Line.h"

class Collidable
{
public:
	Collidable ();
	virtual ~Collidable ();

	std::vector<Line *>* get_line_list ();
	std::vector<Collidable *>* get_collidable_list ();

	bool collided_with (Collidable *collidable);
private:
	std::list<Drawing::Rectangle *> intersection_points;

protected:
	std::vector<Line *>line_list;
	std::vector<Collidable *>collidable_list;

	void add (Line *line);
	void add (Collidable *collidable);

	void delete_last ();
};

