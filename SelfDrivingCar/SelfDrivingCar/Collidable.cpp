#include "stdafx.h"
#include "Collidable.h"


Collidable::Collidable ()
{
}


Collidable::~Collidable ()
{
}

std::list<Line*>* Collidable::get_line_list ()
{
	return &line_list;
}

void Collidable::add (Line * line)
{
	line_list.push_back (line);
}

bool Collidable::collided_with (Collidable * collidable)
{
	std::list<Line *> *other_list = collidable->get_line_list();
	bool collision = false;

	for (std::list<Line*>::iterator i = line_list.begin (); i != line_list.end (); i++)
	{
		for (std::list<Line*>::iterator j = other_list->begin (); j != other_list->end (); j++)
		{
			collision = (*i)->collision (*j);
		}
	}

	return collision;
}
