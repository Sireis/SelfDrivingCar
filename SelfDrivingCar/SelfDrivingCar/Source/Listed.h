#pragma once
class Listed
{
public:
	Listed ();
	virtual ~Listed ();

	virtual void update1 (const double &dt);
	virtual void update2 ();

	bool to_be_disposed ();
	void dispose ();

	void tag (int t);
	
private:
	bool dispose_on_next_update = false;
	int t = 0;

protected:
};

