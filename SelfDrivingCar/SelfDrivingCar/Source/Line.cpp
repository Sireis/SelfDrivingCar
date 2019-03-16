#include "stdafx.h"
#include "Line.h"


Line::Line (const Vec2 a, const Vec2 dv, const Vec2 limit, Drawable *parent)
	:
	Drawing::Rectangle (a.x, a.y, 0.002f, 7.0f, color, parent),
	pos_limit(limit.x),	neg_limit(limit.y)
{
	this->p = acos (dv.y / (sqrt (dv.x * dv.x + dv.y * dv.y)));
	this->rotate (p);
}

Line::Line (const Vec2 a, const float p, const Vec2 limit, Drawable *parent)
	:
	Drawing::Rectangle (a.x, a.y, 0.002f, 7.0f, color, parent),
	pos_limit (limit.x), neg_limit (limit.y),
	p(p)
{
	this->rotate (p);
}

Line::~Line ()
{
}

void Line::get_a (float * a)
{
	a[0] = original_m[0];
	a[1] = original_m[1];
}

void Line::get_dv (float * dv)
{
	dv[0] = original_direction[0];
	dv[1] = original_direction[1];
}

float Line::distance (Line * line)
{
	float l[2];
	float b[2], dw[2];
	line->get_a (b);
	line->get_dv (dw);

	l[0] = (dw[2] * (a[1] - b[1]) - dw[1] * (a[2] - b[2])) / (dw[1] * dv[2] - dw[2] * dv[2]);
	//l[1] = (dv[2] * (a[1] - b[1]) - dv[1] * (a[2] - b[2])) / (dw[1] * dv[2] - dw[2] * dv[2]);

	return l[0];
}

bool Line::collision (Line * line)
{
	float l = distance (line);
	return l < pos_limit && l > neg_limit;
}

void Line::intersection_point (Line * line, float * point)
{
	float l = distance (line);

	point[0] = a[0] + l * dv[0];
	point[1] = a[1] + l * dv[1];
}

