#pragma once
#include "Updateable.h"
#include "Rectangle.h"
#include "Line.h"
#include "Collidable.h"
#include "Track.h"

class Car : public Updateable, public Collidable
{
public:
	Car ();
	Car (const float x, const float y, const float *rgba);
	~Car ();

	void accelerate ();
	void brake ();
	void left ();
	void right ();

	float get_distance (Track *track, int sensor);
	Vec2 get_position ();
	void set_position (const Vec2 &position);

	void stop ();

	void update (const double &dt) override;

	void set_level (const char z);

private: 
	const float width = 0.044f, height = 0.075f;
	float m;
	float pos_a = 0.250f, neg_a = 1.60f;
	float v = 0.0f, v_max = 2.4f;
	float p = 0.0f, dp = 3.0f;
		
	Drawing::Rectangle *tire[4];
	Drawing::Rectangle *body;
	Line *bounds[4];
	Line *sensors[5];

	struct Flag
	{
		bool accelerate = false;
		bool brake = false;
		bool left = false;
		bool right = false;
		bool stop = false;
	} flag;

	void reset_flags ();
};

