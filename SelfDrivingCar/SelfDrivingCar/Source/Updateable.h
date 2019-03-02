#pragma once
class Updateable
{
public:
	Updateable ();
	virtual ~Updateable ();

	virtual void update (const double &dt) = 0;
};

