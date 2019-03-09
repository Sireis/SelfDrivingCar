#pragma once
#include "Updateable.h"
#include "Rectangle.h"

class Car : public Updateable
{
public:
	Car ();
	Car (const float x, const float y, const float *rgba);
	~Car ();

	void accelerate ();
	void brake ();
	void left ();
	void right ();

	void update (const double &dt) override;

private: 
	const float width = 0.044f, height = 0.075f;
	float m;
	float pos_a = 0.250f, neg_a = 0.60f;
	float v = 0.0f, v_max = 0.6f;
	float p = 0.0f, dp = 3.0f;
	
	float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	std::list<Drawing::Rectangle *> parts;

	Drawing::Rectangle *tire[4];
	Drawing::Rectangle *body;


	struct Flag
	{
		bool accelerate = false;
		bool brake = false;
		bool left = false;
		bool right = false;
	} flag;
};

