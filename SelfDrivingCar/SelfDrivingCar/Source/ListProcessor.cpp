#include "ListProcessor.h"

std::list<Listed*> ListProcessor::list;

void ListProcessor::update (double & dt)
{
	for (std::list<Listed *>::iterator i = list.begin (); i != list.end ();)
	{
		if ((*i) != nullptr)
		{
			if (!(*i)->to_be_disposed ())
			{
				(*i)->update1 (dt);
				i++;
			}
			else
			{
				delete (*i);
				i = list.erase (i);
			}
		}
	}

	for (std::list<Listed *>::iterator i = list.begin (); i != list.end (); i++)
	{
		if ((*i) != nullptr)
		{
			(*i)->update2 ();
		}
	}
}

void ListProcessor::add (Listed *l)
{
	list.push_back (l);
}

ListProcessor::ListProcessor ()
{
}


ListProcessor::~ListProcessor ()
{
}
