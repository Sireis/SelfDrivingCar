#pragma once

#include "stdafx.h"
#include "Drawable.h"

namespace Drawing
{
	class Rectangle : public Drawable
	{
	private:
		int uniformTexture;
		float height, width;
		float *a, *b, *c, *d;
		bool is_visible = true;

		//Drawable *parent;

		void init ();
		
	public:
		Rectangle ();
		Rectangle (const float x, const float y, const float width, const float height, const float* rgba, Drawable *parent = nullptr);
		~Rectangle ();

		void draw () override;
		void visible (bool visibility);
	};
}