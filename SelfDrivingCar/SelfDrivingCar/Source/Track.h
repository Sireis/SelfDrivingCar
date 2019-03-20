#pragma once
#include "Collidable.h"
#include "Wall.h"

class Track :
	public Collidable
{
public:
	Track (Vec2 start);
	virtual ~Track ();

	void add (Vec2 point);

private:
	std::list<Wall *> wall_list;
	Vec2 last_point;
	const float width = 0.3f;
};

