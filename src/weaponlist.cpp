#include "weaponlist.h"

// Non defualt constructor, calls on defualt constructor to deal with weapon aspect
//The rest deals with maintaining the list
Weaponlist::Weaponlist(Weaponlist* last, Vector &position, Vector &velocity)
:Weapons(position, velocity, 0)
{
	//Set m_last to last passed in
	m_last = last;
	//If its not NULL
	if(m_last != NULL)
	{
		//then go to the last and set it member next to this pointer value
		m_last->m_next = this;
	}
	//Set m_next to NULL
	m_next = NULL;
}

//Method to update the list, takes a pass by reference last to return the next member in the list if the newest is deleted
//This recursivally goes down the list. Doing the second bit of the method last working backup the list
void Weaponlist::update_position(int screen_x, int screen_y, Weaponlist* &last)
{
	//Call the base class update
	Weapons::update_position(screen_x, screen_y);
	//then if the next down the list isn't NULL, call its Update
	if(m_last != NULL)
	{
		m_last->update_position(screen_x, screen_y, last);
	}

	//After its recursivally gone down the list, test if it is in-active
	//If its inactive then delete it an tie back the list
	if(!GetActive())
	{
		//If the next isn't NULL
		if(m_next != NULL)
		{
			//Then set this members last to then next member last
			m_next->m_last = m_last;
		}
		else
		{
			//If it is NULL pass back out of the method m_last, the next member in the list
			last = m_last;
		}
		//If the last is not NULL
		if(m_last != NULL)
		{
			//Set the Lasts m_next to this m_next
			m_last->m_next = m_next;
		}
		//After all that delete this object
		delete this;
	}

}

//This method displays the weapon
void Weaponlist::display(SDL_Surface *surf)
{
	//Call the class display method
	Weapons::display(surf);
	//If the next down the list isn't NULL
	if(m_last != NULL)
	{
		//Then call its Display function
		m_last->display(surf);
	}
}