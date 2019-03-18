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
	static unsigned long cycle = 0;
	std::list<Line *> *other_list = collidable->get_line_list();
	bool collision = false, b1, b2;

	float temp[2];

	float *color;
	float green[4] = { 0.0f, 1.0f, 0.0f, 0.5f };
	float red[4] = { 1.0f, 0.0f, 0.0f, 0.5f };
	float blue[4] = { 0.0f, 0.0f, 1.0f, 0.5f };
	float black[4] = { 0.0f, 0.0f, 0.0f, 0.5f };

	if (cycle != Environment::number_update_cycle)
	{
		cycle = Environment::number_update_cycle;

		std::list<Drawing::Rectangle *>::iterator i = intersection_points.begin ();
		for (; i != intersection_points.end (); i++)
		{
			(*i)->dispose ();
		}
		intersection_points.clear ();
	}

	for (std::list<Line*>::iterator i = line_list.begin (); i != line_list.end (); i++)
	{
		for (std::list<Line*>::iterator j = other_list->begin (); j != other_list->end (); j++)
		{
			b1 = (*i)->collision (*j);
			b2 = (*j)->collision (*i);

			if (b1 && b2)
			{
				color = red;
			}
			else if (b1)
			{
				color = blue;
			}
			else if (b2)
			{
				color = green;
			}
			else
			{
				color = black;
			}

			(*i)->intersection_point (*j, temp);
			Drawing::Rectangle *dot = new Drawing::Rectangle (temp[0], temp[1], 0.01f, 0.01f, color);
			intersection_points.push_back (dot);
		}
	}

	return collision;
}
