#include "stdafx.h"
#include "Drawable.h"
#include "Listed.h"


Drawable::Drawable (const unsigned int number_of_points, const Vec2 m, const Vec2 direction)
	:
	number_of_points(number_of_points),
	m{m.x,m.y}, original_m{m.x, m.y}, model_m{m.x,m.y},
	direction{ direction.x,direction.y },
	original_direction{ direction.x, direction.y },
	model_direction{ direction.x, direction.y }
{
	vertices = new float[number_of_points * Environment::shader.vertex_buffer_line_length];
	original_vertices = new float[number_of_points * Environment::shader.vertex_buffer_line_length];
	model_vertices = new float[number_of_points * Environment::shader.vertex_buffer_line_length];
}


Drawable::~Drawable ()
{
	delete[] vertices;
	delete[] original_vertices;
	delete[] model_vertices;
}

void Drawable::translate (const float dx, const float dy)
{
	setup ();

	float dv[2];
	dv[0] = dx; dv[1] = dy;

	MatrixMath::multiply_m2x2_v2 (rotation, dv, dv);

	model_offset[0] += dv[0];
	model_offset[1] += dv[1];

	model_m[0] += dv[0];
	model_m[1] += dv[1];

	if (parent == nullptr)
	{
		m[0] = model_m[0];
		m[1] = model_m[1];
	}
}

void Drawable::rotate (const float rad)
{
	setup ();

	rotation[0] = cos (rad);
	rotation[1] = sin (rad);
	rotation[2] = -sin (rad);
	rotation[3] = cos (rad);
	
	float *t = new float[2*number_of_points];// (2 * number_of_points * sizeof (float));

	for (unsigned int i = 0; i < number_of_points; i++)
	{
		t[i * 2] = original_vertices[i * 9] - original_m[0];
		t[i * 2 + 1] = original_vertices[i * 9 + 1] - original_m[1];

		MatrixMath::multiply_m2x2_v2 (rotation, &(t[i * 2]), &(t[i * 2]));

		model_vertices[i * 9] = t[i * 2] + original_m[0];
		model_vertices[i * 9 + 1] = t[i * 2 + 1] + original_m[1];
	}

	MatrixMath::multiply_m2x2_v2 (rotation, model_direction, model_direction);

	delete[] t;
	
	if (parent == nullptr)
	{
		direction[0] = model_direction[0];
		direction[1] = model_direction[1];
	}
}

void Drawable::update (const double & dt)
{
	setup ();

	if (parent != nullptr)
	{
		float rotation[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float offset[] = { 0.0f, 0.0f };
		parent->get_rotation (rotation);
		parent->get_middle (offset);

		float *f1 = new float[2 * number_of_points];

		for (unsigned int i = 0; i < number_of_points; i++)
		{
			MatrixMath::multiply_m2x2_v2 (rotation, &(model_vertices[i*9]), &(f1[i * 2]));

			vertices[i * 9] = f1[i * 2] + offset[0] + model_offset[0];
			vertices[i * 9 + 1] = f1[i * 2 + 1] + offset[1] + model_offset[1];
		}

		float f2[2];
		float f3[2];

		MatrixMath::multiply_m2x2_v2 (rotation, model_direction, f2);
		MatrixMath::multiply_m2x2_v2 (rotation, model_m, f3);

		direction[0] = f2[0];
		direction[1] = f2[1];
		
		m[0] = offset[0] + f3[0];
		m[1] = offset[1] + f3[1];
				
		delete[] f1;
	}
	else
	{
		for (unsigned int i = 0; i < number_of_points; i++)
		{
			vertices[i * 9] = model_vertices[i * 9] + model_offset[0];
			vertices[i * 9 + 1] = model_vertices[i * 9 + 1] + model_offset[1];
		}

		m[0] = model_m[0];
		m[1] = model_m[1];

		direction[0] = model_direction[0];
		direction[1] = model_direction[1];
	}
}

void Drawable::update2 ()
{

	draw ();
}


void Drawable::set_parent (Drawable * parent)
{
	this->parent = parent;
}

void Drawable::get_middle (float * middle_x_y)
{
	for (unsigned int i = 0; i < number_of_points; i++)
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

void Drawable::set_level (const int level)
{
	vertices[2] = vertices[11] = vertices[20] = vertices[29] = (float) -level;
}

int Drawable::get_level ()
{
	return (int) vertices[2];
}

void Drawable::setup ()
{
	if (first_iteration)
	{
		first_iteration = false;

		for (unsigned int i = 0; i < number_of_points * Environment::shader.vertex_buffer_line_length; i++)
		{
			vertices[i] = model_vertices[i] = original_vertices[i];
		}
	}
}