#include "stdafx.h"
#include "ListProcessor.h"

std::vector<Listed*> ListProcessor::list;

void ListProcessor::update (double & dt)
{
	Environment::number_update_cycle++;
	//std::cout << "(glfw) INFO: dt = " << dt << std::endl;

	if (dt > 0.020)
	{
		std::cout << "(application) WARNING: Frametime is longer than expected. (" << dt << "s)" << std::endl;
	}

	for (std::vector<Listed*>::iterator i = list.begin (); i != list.end ();)
	{
		if ((*i) != nullptr)
		{
			if (!(*i)->to_be_disposed ())
			{
				(*i)->update1 (dt);
				++i;
			}
			else
			{
				delete (*i);
				i = list.erase (i);
			}
		}
	}

	for (std::vector<Listed*>::iterator i = list.begin (); i != list.end (); ++i)
	{
		(*i)->update2 ();
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
