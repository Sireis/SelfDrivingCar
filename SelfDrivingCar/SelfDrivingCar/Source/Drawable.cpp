#include "stdafx.h"
#include "Drawable.h"
#include "Listed.h"


Drawable::Drawable ()
{
}


Drawable::~Drawable ()
{
}

void Drawable::rotate (const float rad)
{
	rotation[0] = cos (rad);
	rotation[1] = sin (rad);
	rotation[2] = -sin (rad);
	rotation[3] = cos (rad);


	//finding the middle of all points
	float middle[] = { 0.0f, 0.0f };
	for (int i = 0; i < number_of_points; i++)
	{
		middle[0] += original_vertices[i * 9];
		middle[1] += original_vertices[i * 9 + 1];
	}
	middle[0] /= number_of_points; middle[1] /= number_of_points;

	float *t = new float[2*number_of_points];// (2 * number_of_points * sizeof (float));

	for (int i = 0; i < number_of_points; i++)
	{
		t[i * 2] = original_vertices[i * 9] - middle[0];
		t[i * 2 + 1] = original_vertices[i * 9 + 1] - middle[1];

		MatrixMath::multiply_m2x2_v2 (rotation, &(t[i * 2]), &(t[i * 2]));

		vertices[i * 9] = t[i * 2] + middle[0];
		vertices[i * 9 + 1] = t[i * 2 + 1] + middle[1];
	}

	delete[] t;
}

void Drawable::translate (const float dx, const float dy)
{
	float dv[2];
	dv[0] = dx; dv[1] = dy;

	MatrixMath::multiply_m2x2_v2 (rotation, dv, dv);

	for (int i = 0; i < number_of_points; i++)
	{
		vertices[i * 9 + 0] += dv[0];
		vertices[i * 9 + 1] += dv[1];

		original_vertices[i * 9 + 0] += dv[0];
		original_vertices[i * 9 + 1] += dv[1];		
	}
}


void Drawable::update2 ()
{
	draw ();
}
