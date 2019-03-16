#pragma once
#include "Environment.h"
#include "Rectangle.h"

class Line : public Drawing::Rectangle
{
public:
	Line (const Vec2 a, const Vec2 dv, const Vec2 limit, Drawable *parent = nullptr);
	Line (const Vec2 a, const float p, const Vec2 limit, Drawable *parent = nullptr);
	~Line ();

	void get_a (float *a);
	void get_dv (float *dv);

	void intersection_point (Line *line, float *point);
	Vec2 distance (Line *line);
	bool collision (Line *line);

	float get_pos_limit ();
	float get_neg_limit ();

private:
	float p;
	float pos_limit;
	float neg_limit;

	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
};

