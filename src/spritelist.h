#ifndef CLASS_SPRITELIST
#define CLASS_SPRITELIST

#include "sprite.h"

//This a list derived from Sprite. Sprite orginally worked with static arrays,
//but I thought to expand it like weaponlist 
//Only attack waves use this, class player and boss work fine using the base class
class Spritelist : public Sprite
{
public:
	//Pointers to next and last Spritelist
	Spritelist* m_next;
	Spritelist* m_last;
	//Constructor, No non defualt constructor
	Spritelist(Spritelist* last, int x, int y);
	//New method for updateing
	void Update(int screen_x, int screen_y, Spritelist* &last);
	//New method for displaying
	void display(SDL_Surface *surf);
};

#endif