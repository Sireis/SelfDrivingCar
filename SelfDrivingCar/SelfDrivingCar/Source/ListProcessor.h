#pragma once
#include "Listed.h"

class ListProcessor
{
public:
	static void update (double &dt);
	static void add (Listed *l);

private:
	ListProcessor ();
	~ListProcessor ();

	static std::vector<Listed *> list;		
};

