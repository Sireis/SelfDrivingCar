#include "stdafx.h"
#include "Line.h"


Line::Line (const Vec2 a, const Vec2 dv, const Vec2 limit)
{
	this->a[0] = a.x;
	this->a[1] = a.y;

	float s = sqrt (dv.x*dv.x + dv.y*dv.y);
	this->dv[0] = dv.x / s;
	this->dv[1] = dv.y / s;

	this->pos_limit = limit.x;
	this->neg_limit = limit.y;

	p = acos (this->dv[1]/(sqrt(this->dv[0]* this->dv[0] + this->dv[1]* this->dv[1])));

	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	rectangle = new Drawing::Rectangle (this->a[0], this->a[1], 0.002f, 10.0f, color);
	rectangle->rotate (p);
}

Line::Line (const Vec2 a, const float p, const Vec2 limit)
{
	this->a[0] = a.x;
	this->a[1] = a.y;

	this->dv[0] = 0.0f;
	this->dv[1] = 1.0f;

	this->pos_limit = limit.x;
	this->neg_limit = limit.y;

	this->p = p;

	rotation[0] = cos (p);
	rotation[1] = sin (p);
	rotation[2] = -sin (p);
	rotation[3] = cos (p);

	MatrixMath::multiply_m2x2_v2 (rotation, this->dv, this->dv);

	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	rectangle = new Drawing::Rectangle (this->a[0], this->a[1], 0.002f, 10.0f, color);
	rectangle->rotate (p);
}

Line::~Line ()
{
}

void Line::get_a (float * a)
{
	a[0] = this->a[0];
	a[1] = this->a[1];
}

void Line::get_dv (float * dv)
{
	dv[0] = this->dv[0];
	dv[1] = this->dv[1];
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

