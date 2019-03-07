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

		vertices = new float[vert_SIZE];
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

		unsigned int transformLocation = glGetUniformLocation (Environment::shader.ID, "transform");
		glUniformMatrix4fv (transformLocation, 1, GL_FALSE, rotation);

		//if (texture != nullptr)
		//{
		//	texture->use ();
		//}

		glDrawArrays (GL_QUADS, 0, 4);
	}

	void Rectangle::translate (const float dx, const float dy)
	{
		float v[4];
		
		v[0] = dx; v[1] = dy; v[2] = 0.0f; v[3] = 0.0f;
		MatrixMath::multiply_m4x4_v4 (rotation, v, v);
		
		x += v[0]; y += v[1];

		a[0] += v[0]; b[0] += v[0]; c[0] += v[0]; d[0] += v[0];
		a[1] += v[1]; b[1] += v[1]; c[1] += v[1]; d[1] += v[1];
	}

	void Rectangle::rotate (const float rad)
	{
		rotation[0] = cos (rad);
		rotation[1] = sin (rad);
		rotation[4] = -sin (rad);
		rotation[5] = cos (rad);

		float ta[] = { 0.0f, 0.0f, 0.0f, 0.0f }, tb[] = { 0.0f, 0.0f, 0.0f, 0.0f }, tc[] = { 0.0f, 0.0f, 0.0f, 0.0f }, td[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		
		ta[0] = -0.5f*width + pivot_x; ta[1] = +0.5f*height + pivot_y;
		tb[0] = +0.5f*width + pivot_x; tb[1] = +0.5f*height + pivot_y;
		tc[0] = +0.5f*width + pivot_x; tc[1] = -0.5f*height + pivot_y;
		td[0] = -0.5f*width + pivot_x; td[1] = -0.5f*height + pivot_y;

		MatrixMath::multiply_m4x4_v4 (rotation, ta, ta);
		MatrixMath::multiply_m4x4_v4 (rotation, tb, tb);
		MatrixMath::multiply_m4x4_v4 (rotation, tc, tc);
		MatrixMath::multiply_m4x4_v4 (rotation, td, td);

		a[0] = ta[0] + x; a[1] = ta[1] + y;
		b[0] = tb[0] + x; b[1] = tb[1] + y;
		c[0] = tc[0] + x; c[1] = tc[1] + y;
		d[0] = td[0] + x; d[1] = td[1] + y;
	}
	void Rectangle::set_pivot (const float x, const float y)
	{
		pivot_x = x;
		pivot_y = y;
	}
}