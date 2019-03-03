#pragma once
#include "Listed.h"
#include <list>

class ListProcessor
{
public:
	static void update (double &dt);
	static void add (Listed *l);

private:
	ListProcessor ();
	~ListProcessor ();

	static std::list<Listed *> list;
};

