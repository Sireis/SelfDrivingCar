#include "stdafx.h"
#include "Sensor.h"


Sensor::Sensor (Drawable *parent)
{
	for (int i = 0; i < Sensor::number_of_lines; ++i)
	{
		line[i] = new Line (Vec2 (0, 0), angles[i], Vec2 (0, 0), parent);
	}
}


Sensor::~Sensor ()
{
}

void Sensor::get_distances (Collidable * track, float * distances_will_be_here)
{

	std::vector<Collidable *> *list = track->get_collidable_list ();
	std::vector<Line *> *inner;

	float tmp[Sensor::number_of_lines], f[Sensor::number_of_lines] 
		= { std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity (),std::numeric_limits<float>::infinity (),std::numeric_limits<float>::infinity () };
	bool b1, b2;
	const float *color = nullptr;

	for (std::vector<Collidable *>::iterator i = list->begin (); i != list->end (); ++i)
	{
		inner = (*i)->get_line_list ();
		if (inner->size () == 1)
		{
			Line *wall = inner->front ();

			for (int i = 0; i < Sensor::number_of_lines; ++i)
			{
				if (wall->collision (line[i]))
				{
					tmp[i] = wall->distance (line[i]).y;
					if (tmp[i] > 0)
					{
						tmp[i] < f[i] ? f[i] = tmp[i] : f[i] = f[i];
					}
				}
			}
		}
		else
		{
			for (std::vector<Line *>::iterator j = inner->begin (); j != inner->end (); ++j)
			{
				for (int i = 0; i < Sensor::number_of_lines; ++i)
				{
					if ((*j)->collision (line[i]))
					{
						tmp[i] = (*j)->distance (line[i]).y;
						if (tmp[i] > 0)
						{
							tmp[i] < f[i] ? f[i] = tmp[i] : f[i] = f[i];
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < Sensor::number_of_lines; ++i)
	{
		distances_will_be_here[i] = f[i];
	}
}

void Sensor::set_position (const Vec2 & p)
{
	for (int i = 0; i < Sensor::number_of_lines; ++i)
	{
		line[i]->set_position (p);
	}
}

void Sensor::rotate (const float & phi)
{
	for (int i = 0; i < Sensor::number_of_lines; ++i)
	{
		line[i]->rotate (phi + angles[i]);
	}
}
