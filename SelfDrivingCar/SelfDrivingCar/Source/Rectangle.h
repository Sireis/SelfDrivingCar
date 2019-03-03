#pragma once

#include "stdafx.h"
#include "Drawable.h"

class Rectangle :	public Drawable
{
private:
	int uniformTexture;
	float x, y;
	float height, width;

	void init (const float x, const float y, const float width, const float height, const float* rgba);

public:
	Rectangle ();
	Rectangle (const float x, const float y, const float width, const float height, const float* rgba);
	~Rectangle ();

	void draw () override;

	void translate (const float dx, const float dy);
	void rotate (const float rad);
};

