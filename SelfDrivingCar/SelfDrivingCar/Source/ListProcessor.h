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

	static std::list<Listed *> list;

	static void insert (std::list<std::list<Listed*>*> *list_list, const int level, Listed *obj);
};

