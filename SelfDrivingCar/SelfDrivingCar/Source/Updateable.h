#pragma once

#include "Listed.h"

class Updateable : virtual public Listed
{
public:
	Updateable ();
	virtual ~Updateable ();

	virtual void update (const double &dt) = 0;
	void do_updates (const bool b);

private:
	bool updating = true;
	void update1 (const double &dt) override;
};

