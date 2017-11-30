#include "cruiser.h"	//Header files needed
#include <iostream>		//

using namespace std;

//The only change need is the size of the image used
void Cruiser::display(SDL_Surface *surf)
{
	//If there are lasers display them
	if(lasers != NULL)
	{
		lasers->display(surf);
	}
	//Display photons
	photons.display(surf);

	//If the ship is exploding and the time hasn't run out
	if( m_explosion && expl_time <= 150)
	{
		expl_time++;

		//If time is high enough the explosion is over and the clock reset
		if(expl_time > 150)
		{
			m_explosion = false;
			expl_time = 0;
		}

		//This sets the velocitys when its exploding, 
		//which moves around the image so that the explosion looks right
		if(expl_time < 150)
			SetVelocity( .5, 0);
		if(expl_time < 125)
			SetVelocity(0, 0);
		if(expl_time < 100)
			SetVelocity(-.5, 0);
		if(expl_time < 75)
			SetVelocity(.5, -.5);
		if(expl_time < 50)
			SetVelocity(0, -.5);
		if(expl_time < 25)
			SetVelocity(-.5, -.5);
	}

	//If active display the larger image
	if(m_active)
	{
		 SDL_Rect loc;
		 loc.w = loc.h = 64;
		 loc.x = static_cast<int>(Position.m_x-loc.w/2);
		 loc.y = static_cast<int>(Position.m_y-loc.h/2);
		 SDL_BlitSurface(sprite, 0, surf, &loc);
	}

	//If exploding load the normal explosion image
	if(m_explosion)
	{
		SDL_Rect loc;
		loc.w = loc.h = 32;
		loc.x = static_cast<int>(Position.m_x-16);
		loc.y = static_cast<int>(Position.m_y-16);
		SDL_Rect subImage; 
		subImage.x = static_cast<int>(32 + 64*Velocity.m_x); 
		subImage.y = static_cast<int>(32 + 64*Velocity.m_y); 
		subImage.w = subImage.h = 32; 
		SDL_BlitSurface(explode, &subImage, surf, &loc);
	}

}
//Constructor simply calls the base
Cruiser::Cruiser()
:Sprite()
{
}
//Constructor simply calls the base
Cruiser::Cruiser(int x, int y)
:Sprite(x, y)
{
}
