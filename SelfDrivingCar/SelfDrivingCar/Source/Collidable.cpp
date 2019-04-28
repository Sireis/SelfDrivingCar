#include "stdafx.h"
#include "Collidable.h"


Collidable::Collidable ()
{
}


Collidable::~Collidable ()
{
}

std::vector<Line*>* Collidable::get_line_list ()
{
	return &line_list;
}

std::vector<Collidable*>* Collidable::get_collidable_list ()
{
	return &collidable_list;
}

void Collidable::add (Line * line)
{
	line_list.push_back (line);
}

void Collidable::add (Collidable * collidable)
{
	collidable_list.push_back (collidable);
}

void Collidable::delete_last ()
{
	if (!collidable_list.empty())
	{
		delete (collidable_list.back ());
		collidable_list.pop_back ();
	}
}

bool Collidable::collided_with (Collidable * collidable, int hint)
{
	std::vector<Line *> *other_list = collidable->get_line_list ();
	std::vector<Collidable *> *other_collidables = collidable->get_collidable_list ();
	bool collision = false;

#ifdef DEBUG
	static unsigned long cycle = 0;
	bool b1, b2;
	float temp[2];
	float *color = nullptr;
#endif

//#define WITHOUT_HINT
#ifdef WITHOUT_HINT
	for (std::vector<Collidable *>::iterator i = other_collidables->begin (); i != other_collidables->end (); ++i)
	{
		collision |= this->collided_with (*i);
		for (std::vector<Collidable *>::iterator j = collidable_list.begin (); j != collidable_list.end (); ++j)
		{
			collision |= (*j)->collided_with (*i);
		}
	}
#else
	int start_index =  2*(hint-1);
	int stop_index = 2*(hint-1) + 3;

	if (start_index < 0 || stop_index >= other_collidables->size())
	{
		start_index = 0; stop_index = other_collidables->size () - 1;
	}	

	for (int i = start_index; i < stop_index + 1; ++i)
	{
		collision |= this->collided_with ((*other_collidables)[i]);
		if (collision)
		{
			return true;
		}
		for (int j = 0; j < collidable_list.size (); ++j)
		{
			collision |= collidable_list[j]->collided_with ((*other_collidables)[i]);
			if (collision)
			{
				return true;
			}
		}
	}
#endif

#ifdef DEBUG
	if (cycle != Environment::number_update_cycle)
	{
		cycle = Environment::number_update_cycle;

		std::list<Drawing::Rectangle *>::iterator i = intersection_points.begin ();
		for (; i != intersection_points.end (); ++i)
		{
			(*i)->dispose ();
		}
		intersection_points.clear ();
	}
#endif
	for (std::vector<Line*>::iterator i = line_list.begin (); i != line_list.end (); ++i)
	{
		for (std::vector<Line*>::iterator j = other_list->begin (); j != other_list->end (); ++j)
		{
#ifdef DEBUG
			b1 = (*i)->collision (*j);
			b2 = (*j)->collision (*i);

			if (b1 && b2)
			{
				//color = red;
				collision = true;
			}
			else if (b1)
			{
				//color = blue;
			}
			else if (b2)
			{
				//color = green;
			}
			else
			{
				//color = black;
			}

			if (color != nullptr)
			{
				(*i)->intersection_point (*j, temp);
				Drawing::Rectangle *dot = new Drawing::Rectangle (temp[0], temp[1], 0.01f, 0.01f, color);
				intersection_points.push_back (dot);
			}
#else
			if ((*i)->collision (*j))
			{
				collision |= (*j)->collision (*i);
				if (collision)
				{
					return true;
				}
			}
#endif
		}
	}

	return collision;
}
