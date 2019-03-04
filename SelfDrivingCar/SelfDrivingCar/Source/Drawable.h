#pragma once

#include "Listed.h"

class Drawable : virtual public Listed
{
public:
	Drawable ();
	virtual ~Drawable ();

	virtual void draw () = 0;
	
private:
	void update2 () override;

protected:
	GLuint VBO;
	float *vertices = nullptr;
};

