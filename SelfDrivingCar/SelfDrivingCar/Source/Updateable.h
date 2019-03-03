#pragma once

#include "Listed.h"

class Updateable : virtual public Listed
{
public:
	Updateable ();
	virtual ~Updateable ();

	virtual void update (const double &dt) = 0;

private:
	void update1 (const double &dt) override;
};

