#include "stdafx.h"
#include "Drawable.h"
#include "Listed.h"


Drawable::Drawable (const unsigned int number_of_points)
	:
	number_of_points(number_of_points)
{

	vertices = new float[number_of_points * Environment::shader.vertex_buffer_line_length];
	original_vertices = new float[number_of_points * Environment::shader.vertex_buffer_line_length];
	model_vertices = new float[number_of_points * Environment::shader.vertex_buffer_line_length];
}


Drawable::~Drawable ()
{
}

void Drawable::translate (const float dx, const float dy)
{
	setup ();

	float dv[2];
	dv[0] = dx; dv[1] = dy;

	MatrixMath::multiply_m2x2_v2 (rotation, dv, dv);

	model_offset[0] += dv[0];
	model_offset[1] += dv[1];
}

void Drawable::rotate (const float rad)
{
	setup ();

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

		model_vertices[i * 9] = t[i * 2] + middle[0];
		model_vertices[i * 9 + 1] = t[i * 2 + 1] + middle[1];
	}

	delete[] t;
}

void Drawable::update2 ()
{
	setup ();

	if (parent != nullptr)
	{
		float rotation[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float offset[] = { 0.0f, 0.0f };
		parent->get_rotation (rotation);
		parent->get_middle (offset);

		float *t = new float[2 * number_of_points];

		for (int i = 0; i < number_of_points; i++)
		{
			t[i * 2] = model_vertices[i * 9];
			t[i * 2 + 1] = model_vertices[i * 9 + 1];

			MatrixMath::multiply_m2x2_v2 (rotation, &(t[i * 2]), &(t[i * 2]));

			vertices[i * 9] = t[i * 2] + offset[0] + model_offset[0];
			vertices[i * 9 + 1] = t[i * 2 + 1] + offset[1] + model_offset[1];
		}

		delete[] t;
	}
	else
	{
		for (int i = 0; i < number_of_points; i++)
		{
			vertices[i * 9] = model_vertices[i * 9] + model_offset[0];
			vertices[i * 9 + 1] = model_vertices[i * 9 + 1] + model_offset[1];
		}
	}

	draw ();
}


void Drawable::set_parent (Drawable * parent)
{
	this->parent = parent;
}

void Drawable::get_middle (float * middle_x_y)
{
	for (int i = 0; i < number_of_points; i++)
	{
		middle_x_y[0] += vertices[i * 9];
		middle_x_y[1] += vertices[i * 9 + 1];
	}
	middle_x_y[0] /= number_of_points; middle_x_y[1] /= number_of_points;
}

void Drawable::get_rotation (float * rotation_matrix)
{
	for (int i = 0; i < 4; i++)
	{
		rotation_matrix[i] = rotation[i];
	}
}

void Drawable::setup ()
{
	if (first_iteration)
	{
		first_iteration = false;

		for (int i = 0; i < number_of_points * Environment::shader.vertex_buffer_line_length; i++)
		{
			vertices[i] = model_vertices[i] = original_vertices[i];
		}
	}
}