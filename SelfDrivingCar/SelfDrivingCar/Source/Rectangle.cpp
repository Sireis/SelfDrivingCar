#include "stdafx.h"
#include "Rectangle.h"

namespace Drawing
{
	void Rectangle::init ()
	{
		/*

		   a(x,y)     b(x,y)
				+-----+
				|  .  |
				+-----+
		   d(x,y)     c(x,y)

		*/
		a = &(original_vertices[0]);
		b = &(original_vertices[9]);
		d = &(original_vertices[18]);
		c = &(original_vertices[27]);

		a[0] = -0.5f*width + m[0]; a[1] = +0.5f*height + m[1];
		b[0] = +0.5f*width + m[0]; b[1] = +0.5f*height + m[1];
		c[0] = +0.5f*width + m[0]; c[1] = -0.5f*height + m[1];
		d[0] = -0.5f*width + m[0]; d[1] = -0.5f*height + m[1];

		original_vertices[2] = original_vertices[11] = original_vertices[20] = original_vertices[29] = 0.0;
		original_vertices[7] = 0.0; original_vertices[8] = 1.0;
		original_vertices[16] = 0.0; original_vertices[17] = 0.0;
		original_vertices[25] = 1.0; original_vertices[26] = 0.0;
		original_vertices[34] = 1.0; original_vertices[35] = 1.0;
	}
	
	Rectangle::Rectangle ()
		:
		Drawable(4, Vec2(0,0), Vec2(0,0))
	{
	}

	Rectangle::Rectangle (const float x, const float y, const float width, const float height, const float * rgba, Drawable *parent)
		:
		Drawable(4, Vec2(x,y), Vec2(0,1)),
		width (width), height (height)
	{
		this->parent = parent;
		init ();

		original_vertices[3] = original_vertices[12] = original_vertices[21] = original_vertices[30] = rgba[0];
		original_vertices[4] = original_vertices[13] = original_vertices[22] = original_vertices[31] = rgba[1];
		original_vertices[5] = original_vertices[14] = original_vertices[23] = original_vertices[32] = rgba[2];
		original_vertices[6] = original_vertices[15] = original_vertices[24] = original_vertices[33] = rgba[3];

		//texture = nullptr;
	}

	Rectangle::Rectangle (const Vec2 m, const Vec2 size, const float * rgba, Drawable * parent)
		:
		Drawable (4, m, Vec2 (0, 1)),
		width (size.x), height (size.y)
	{
		this->parent = parent;

		init ();

		original_vertices[3] = original_vertices[12] = original_vertices[21] = original_vertices[30] = rgba[0];
		original_vertices[4] = original_vertices[13] = original_vertices[22] = original_vertices[31] = rgba[1];
		original_vertices[5] = original_vertices[14] = original_vertices[23] = original_vertices[32] = rgba[2];
		original_vertices[6] = original_vertices[15] = original_vertices[24] = original_vertices[33] = rgba[3];

		glGenBuffers (1, &VBO);
		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		glBufferData (GL_ARRAY_BUFFER, number_of_points * Environment::shader.vertex_buffer_line_length * sizeof (float), vertices, GL_STATIC_DRAW);

	}


	Rectangle::~Rectangle ()
	{
	}

	void Rectangle::draw ()
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
		glDrawArrays (GL_TRIANGLE_STRIP, 0, number_of_points);
	
	}
}