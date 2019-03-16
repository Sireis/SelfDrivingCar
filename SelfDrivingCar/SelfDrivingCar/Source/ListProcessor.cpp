#include "stdafx.h"
#include "ListProcessor.h"

std::list<Listed*> ListProcessor::list;

void ListProcessor::update (double & dt)
{
	//std::cout << "(glfw) INFO: dt = " << dt << std::endl;

	if (dt > 0.020)
	{
		std::cout << "(application) WARNING: Frametime is longer than expected. (" << dt << "s)" << std::endl;
	}

	std::list<std::list<Listed *> *> *list_list = new std::list<std::list<Listed *> *> ();

	for (std::list<Listed*>::iterator i = list.begin (); i != list.end ();)
	{
		if ((*i) != nullptr)
		{
			if (!(*i)->to_be_disposed ())
			{
				(*i)->update1 (dt);
				insert(list_list,(*i)->get_level (), (*i));

				i++;
			}
			else
			{
				delete (*i);
				i = list.erase (i);
			}
		}
	}

	for (std::list<std::list<Listed *> *>::iterator o = list_list->begin (); o != list_list->end (); o++)
	{
		for (std::list<Listed *>::iterator i = (*o)->begin(); i != (*o)->end(); i++)
		{
			(*i)->update2 ();
		}
	}

	list_list->clear ();
	delete list_list;
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

void ListProcessor::insert (std::list<std::list<Listed*> *> *list_list, const int level, Listed* obj)
{
	static int min = 0;
	static int max = 0;

	if (list_list->empty ())
	{
		min = level;
		max = level;

		std::list<Listed *> *list = new std::list<Listed *> ();
		list->push_back (obj);
		list_list->push_back (list);
	}
	else if (level < min)
	{
		min = level;

		std::list<Listed *> *list = new std::list<Listed *> ();
		list->push_back (obj);
		list_list->push_front (list);
	}
	else if(level > max)
	{
		max = level;

		std::list<Listed *> *list = new std::list<Listed *> ();
		list->push_back (obj);
		list_list->push_back (list);
	}
	else	
	{
		std::list<std::list<Listed *> *>::iterator i;

		for (i = list_list->begin (); i != list_list->end (); i++)
		{
			if ((*i)->front ()->get_level () == level)
			{
				(*i)->push_back (obj);				
				break;
			}
			else if ((*i)->front ()->get_level () > level)
			{
				std::list<Listed *> *list = new std::list<Listed *> ();
				list->push_back (obj);
				list_list->insert (i, list);
				break;
			}
		}
	}
}
