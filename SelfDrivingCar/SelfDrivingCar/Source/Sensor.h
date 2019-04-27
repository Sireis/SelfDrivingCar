#pragma once
#include "Line.h"
#include "Collidable.h"

class Sensor
{
public:
	Sensor (Drawable *parent = nullptr);
	~Sensor ();

	void get_distances (Collidable *track, float * distances_will_be_here);

	void set_position (const Vec2 &p);
	void rotate (const float &phi);

private:
	float angles[5] = { -3.1415926f / 2, -3.1415926f / 4, 0, 3.1415926f / 4, 3.1415926f / 2 };
	static const int number_of_lines = 5;
	Line *line[Sensor::number_of_lines];
	Drawing::Rectangle *anchor = nullptr;
};

