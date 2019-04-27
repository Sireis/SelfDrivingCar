#pragma once
#include "Drawable.h"

namespace Drawing
{
	class Circle : public Drawable
	{
	public:
		Circle ();
		Circle (const Vec2 m, const float radius, const float* rgba, Drawable *parent = nullptr);
		~Circle ();

		void set_color (float angle, const float* rgba);

		void draw () override;

	private:
		float radius;

		void init ();
	};
}

