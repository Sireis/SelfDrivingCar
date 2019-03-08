#include "stdafx.h"
#include "Rectangle.h"
#include <cmath>

const int vert_SIZE = 36;

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
		original_vertices = new float[vert_SIZE];
		vertices = new float[vert_SIZE];
		number_of_points = vert_SIZE / 9;
		a = &(vertices[0]);
		b = &(vertices[9]);
		c = &(vertices[18]);
		d = &(vertices[27]);

		a[0] = -0.5f*width + x; a[1] = +0.5f*height + y;
		b[0] = +0.5f*width + x; b[1] = +0.5f*height + y;
		c[0] = +0.5f*width + x; c[1] = -0.5f*height + y;
		d[0] = -0.5f*width + x; d[1] = -0.5f*height + y;

		vertices[2] = vertices[11] = vertices[20] = vertices[29] = 0.0;
		vertices[7] = 0.0; vertices[8] = 1.0;
		vertices[16] = 0.0; vertices[17] = 0.0;
		vertices[25] = 1.0; vertices[26] = 0.0;
		vertices[34] = 1.0; vertices[35] = 1.0;
	}

	void Rectangle::fill_originals ()
	{
		for (int i = 0; i < vert_SIZE; i++)
		{
			original_vertices[i] = vertices[i];
		}
	}

	Rectangle::Rectangle ()
	{
	}

	Rectangle::Rectangle (const float x, const float y, const float width, const float height, const float * rgba)
		:
		x (x), y (y), width (width), height (height), pivot_x(x), pivot_y(y)
	{
		init ();

		vertices[3] = vertices[12] = vertices[21] = vertices[30] = rgba[0];
		vertices[4] = vertices[13] = vertices[22] = vertices[31] = rgba[1];
		vertices[5] = vertices[14] = vertices[23] = vertices[32] = rgba[2];
		vertices[6] = vertices[15] = vertices[24] = vertices[33] = rgba[3];

		glGenBuffers (1, &VBO);
		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		glBufferData (GL_ARRAY_BUFFER, vert_SIZE * sizeof (float), vertices, GL_STATIC_DRAW);

		//texture = nullptr;
		fill_originals ();
	}

	Rectangle::Rectangle (const float x, const float y, const float width, const float height, const float * rgba, Drawable * parent)
	{
	}


	Rectangle::~Rectangle ()
	{
	}

	void Rectangle::draw ()
	{
		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		glBufferSubData (GL_ARRAY_BUFFER, 0, vert_SIZE * sizeof (float), vertices);
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof (float), (void*)0);
		glEnableVertexAttribArray (0);
		glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof (float), (void*)(3 * sizeof (float)));
		glEnableVertexAttribArray (1);
		glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof (float), (void*)(7 * sizeof (float)));
		glEnableVertexAttribArray (2);

		//if (texture != nullptr)
		//{
		//	texture->use ();
		//}

		glDrawArrays (GL_QUADS, 0, 4);
	}
	
	void Rectangle::set_pivot (const float x, const float y)
	{
		pivot_x = x;
		pivot_y = y;
	}
}