#pragma once

#include "stdafx.h"
#include "Drawable.h"

namespace Drawing
{
	class Rectangle : public Drawable
	{
	private:
		int uniformTexture;
		float x, y;
		float pivot_x, pivot_y;
		float height, width;
		float *a, *b, *c, *d;

		Drawable *parent;

		void init ();

	public:
		Rectangle ();
		Rectangle (const float x, const float y, const float width, const float height, const float* rgba);
		Rectangle (const float x, const float y, const float width, const float height, const float* rgba, Drawable *parent);
		~Rectangle ();

		void draw () override;
		
		void set_pivot (const float x, const float y);
	};
}