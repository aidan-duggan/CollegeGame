#ifndef CLASS_CRUISER
#define CLASS_CRUISER

#include "sprite.h"

//Cruiser is a derived class of sprite, used for Boses
class Cruiser : public Sprite
{
public:
	//The only difference between sprite is that the image is larger, so only display needs to be changed
	void display(SDL_Surface *surf);
	//Constructor
	Cruiser();
	//Nondefualt Constructor
	Cruiser(int x, int y);

};

#endif