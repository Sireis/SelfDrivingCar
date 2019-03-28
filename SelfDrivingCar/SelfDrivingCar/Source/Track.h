#pragma once
#include "Collidable.h"
#include "Wall.h"

class Track :
	public Collidable
{
public:
	Track (Vec2 start);
	virtual ~Track ();

	void add (Vec2 p3);

private:
	std::list<Wall *> wall_list;
	Vec2 last_point, very_last_point;
	float p = 3.1415926535f / 2.0f;
	const float width = 0.3f;
};

