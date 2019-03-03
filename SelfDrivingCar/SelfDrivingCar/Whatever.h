#pragma once

#include "Source\Drawable.h"
#include "Source\Updateable.h"

class Whatever : public Drawable, public Updateable
{
public:
	Whatever ();
	~Whatever ();

	void update (const double &dt) override;
	void draw () override;

};

