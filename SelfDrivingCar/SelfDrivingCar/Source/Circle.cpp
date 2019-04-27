#include "stdafx.h"
#include "Circle.h"
#include "Rectangle.h"

namespace Drawing
{
	void Circle::init ()
	{
		original_vertices[0] = m[0]; original_vertices[1] = m[1];
		original_vertices[2] = 0.0;

		for (int i = 1; i < number_of_points; ++i)
		{
			original_vertices[9 * i + 0] = m[0] + radius * sin (2 * 3.1415926535*(i - 1) / (number_of_points - 2));
			original_vertices[9 * i + 1] = m[1] + radius * cos (2 * 3.1415926535*(i - 1) / (number_of_points - 2));
			original_vertices[9 * i + 2] = 0.0;
		}
	}

	Circle::Circle ()
		:
		Drawable(10,Vec2(0,0),Vec2(0,1))
	{
	}

	Circle::Circle (const Vec2 m, const float radius, const float * rgba, Drawable * parent)
		:
		Drawable(((int)(2*3.1415926535*radius/0.005)),m,Vec2(0,1)),
		radius(radius)
	{
		this->parent = parent;
		init ();
		
		for (int i = 0; i < number_of_points; ++i)
		{
			original_vertices[9 * i + 3] = rgba[0];
			original_vertices[9 * i + 4] = rgba[1];
			original_vertices[9 * i + 5] = rgba[2];
			original_vertices[9 * i + 6] = rgba[3];
		}
	}


	Circle::~Circle ()
	{
	}

	void Circle::set_color (float angle, const float * rgba)
	{
		int index = angle / (2* 3.1415926535) * (number_of_points - 1) + 1;
		int count = (number_of_points - 1) / 12;
		
		int n = 0;
		for (int i = 0; i < count; ++i)
		{
			n = (index - (count / 2) + i) % (number_of_points - 1) ;
			if (n <= 0)
			{
				n = (number_of_points - n - 1);
			}
			vertices[9 * n + 3] = model_vertices[9 * n + 3] = original_vertices[9 * n + 3] = rgba[0];
			vertices[9 * n + 4] = model_vertices[9 * n + 4] = original_vertices[9 * n + 4] = rgba[1];
			vertices[9 * n + 5] = model_vertices[9 * n + 5] = original_vertices[9 * n + 5] = rgba[2];
			vertices[9 * n + 6] = model_vertices[9 * n + 6] = original_vertices[9 * n + 6] = rgba[3];
		}
	}

	void Circle::draw ()
	{
		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		glBufferSubData (GL_ARRAY_BUFFER, 0, number_of_points * Environment::shader.vertex_buffer_line_length * sizeof (float), vertices);
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, Environment::shader.vertex_buffer_line_length * sizeof (float), (void*)0);
		glEnableVertexAttribArray (0);
		glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, Environment::shader.vertex_buffer_line_length * sizeof (float), (void*)(3 * sizeof (float)));
		glEnableVertexAttribArray (1);
		glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, Environment::shader.vertex_buffer_line_length * sizeof (float), (void*)(7 * sizeof (float)));
		glEnableVertexAttribArray (2);

		//if (texture != nullptr)
		//{
		//	texture->use ();
		//}
		glDrawArrays (GL_TRIANGLE_FAN, 0, number_of_points);
	}
}