#include "stdafx.h"
#include "Updateable.h"
#include "Listed.h"


Updateable::Updateable ()
{
}


Updateable::~Updateable ()
{
}

void Updateable::do_updates (const bool b)
{
	updating = b;
}


void Updateable::update1 (const double &dt)
{
	if (updating)
	{
		update (dt);
	}
}
