#include "stdafx.h"
#include "Line.h"


Line::Line (const float x, const float y, const float dx, const float dy)
{
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

void Line::intersection_point (Line * line, float * point)
{
	float l[2];
	float b[2], dw[2];
	line->get_a (b);
	line->get_dv (dw);

	l[0] = (dw[2] * (a[1] - b[1]) - dw[1] * (a[2] - b[2])) / (dw[1] * dv[2] - dw[2] * dv[2]);
	//l[1] = (dv[2] * (a[1] - b[1]) - dv[1] * (a[2] - b[2])) / (dw[1] * dv[2] - dw[2] * dv[2]);

	point[0] = a[0] + l[0] * dv[0];
	point[1] = a[1] + l[0] * dv[1];
}
