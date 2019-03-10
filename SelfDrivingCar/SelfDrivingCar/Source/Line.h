#pragma once
class Line
{
public:
	Line (const float x, const float y, const float dx, const float dy);
	~Line ();

	void get_a (float *a);
	void get_dv (float *dv);

	void intersection_point (Line *line, float *point);

private:
	float a[2];
	float dv[2];
};

