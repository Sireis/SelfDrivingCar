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
		float height, width;
		float *a, *b, *c, *d;

		void init ();

		float rotation[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		float translation[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	public:
		Rectangle ();
		Rectangle (const float x, const float y, const float width, const float height, const float* rgba);
		~Rectangle ();

		void draw () override;

		void translate (const float dx, const float dy);
		void rotate (const float rad);
	};
}