#pragma once

#include "stdafx.h"
#include "Drawable.h"

namespace Drawing
{
	class Rectangle : public Drawable
	{
	public:
		Rectangle ();
		Rectangle (const float x, const float y, const float width, const float height, const float* rgba, Drawable *parent = nullptr);
		Rectangle (const Vec2 m, const Vec2 size, const float* rgba, Drawable *parent = nullptr);
		~Rectangle ();

		void draw () override;

		Vec2 get_size ();
		void set_size (Vec2 s);

	private:
		int uniformTexture;
		float height, width;
		float *a, *b, *c, *d;

		void init ();		
	};
}