#pragma once
#include "Updateable.h"

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
	float m;
	float pos_a = 0.005f, neg_a = 0.01f;
	float v = 0.0f, v_max = 0.1f;
	float p = 0.0f, dp = 0.001f;

	float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	std::list<Drawing::Rectangle *> parts;

	Drawing::Rectangle tire[4];
	Drawing::Rectangle body;

	struct Flag
	{
		bool accelerate = false;
		bool brake = false;
		bool left = false;
		bool right = false;
	} flag;

};

