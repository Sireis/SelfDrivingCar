#include "stdafx.h"
#include "Line.h"


Line::Line (const Vec2 a, const Vec2 dv, const Vec2 limit, Drawable *parent)
	:
	Drawing::Rectangle (a.x, a.y, 0.002f, 7.0f, color, parent),
	pos_limit(limit.x),	neg_limit(limit.y)
{
	this->p = acos (dv.y / (sqrt (dv.x * dv.x + dv.y * dv.y)));
	(dv.x < 0) ? p = -p : p = p;	
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
	a[0] = m[0];
	a[1] = m[1];
}

void Line::get_dv (float * dv)
{
	dv[0] = direction[0];
	dv[1] = direction[1];
}

float Line::distance (Line * line)
{
	float l[2];
	float b[2], dw[2];
	line->get_a (b);
	line->get_dv (dw);

	l[0] = (dw[1] * (m[0] - b[0]) - dw[0] * (m[1] - b[1])) / (dw[0] * direction[1] - dw[1] * direction[0]);
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

	point[0] = m[0] + l * direction[0];
	point[1] = m[1] + l * direction[1];
}

