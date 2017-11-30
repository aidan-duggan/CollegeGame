#ifndef CLASS_WEAPONSLIST
#define CLASS_WEAPONSLIST

#include "weapons.h"

//This a list derived from Weapons. Weapons was orginally written to work with static arrays,
//but I thought to expand it to a list by adding pointers to previous and next objects,
//and methods to handle the new way of working with them. 
//Only lasers use this class photons work fine using the base class
class Weaponlist : public Weapons
{
public:
	//Pointers to next and last Weaponlist
	Weaponlist* m_next;
	Weaponlist* m_last;
	//Constructor, No non defualt constructor
	Weaponlist(Weaponlist* last, Vector &position, Vector &velocity);
	//New method for updateing
	void update_position(int screen_x, int screen_y, Weaponlist* &last);
	//New method for displaying
	void display(SDL_Surface *surf);
};

#endif