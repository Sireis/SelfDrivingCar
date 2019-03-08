#pragma once

#include "Listed.h"

class Drawable : virtual public Listed
{
public:
	Drawable ();
	virtual ~Drawable ();

	virtual void draw () = 0;

	void rotate (const float rad);
	void translate (const float dx, const float dy);
	
private:
	void update2 () override;

	float rotation[4] = {1.0f, 0.0f, 0.0f, 1.0f};

protected:
	GLuint VBO;
	float *vertices = nullptr;
	float *original_vertices = nullptr;
	unsigned int number_of_points = 0;

};

