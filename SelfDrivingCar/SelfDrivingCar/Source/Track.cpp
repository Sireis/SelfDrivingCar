#include "stdafx.h"
#include "Track.h"


Track::Track (Vec2 start)
	:
	last_point(start)
{
}

Track::~Track ()
{
}

void Track::add (Vec2 point)
{
	Wall *wall = new Wall (last_point, point);
	Collidable::add (wall);
	wall_list.push_back (wall);
	last_point = point;
}
