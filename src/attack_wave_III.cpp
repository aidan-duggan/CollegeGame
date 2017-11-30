#include "attack_wave_III.h"

//To represent the enemies de-cloaking the display method is edited
void Attack_Wave_III::Display(SDL_Surface *surface)
{
	//Create a temp pointer to spritelist
	Spritelist *temp;
	temp = enemies;
	//go through the list
	while(temp != NULL)
	{
		//Create the variable to hold the transparancy, 0 clear 255 opaque
		int x = static_cast<int>(temp->GetPosition_y()) - 200;
		if(x < 0)
		{
			x = 0;
		}

		if(x > 255)
		{
			x = 255;
		}
		//Set that value as a unit8
		const Uint8 cloak = (Uint8)(x);
		//Load the alpha setting
		
 		int result = SDL_SetSurfaceAlphaMod(temp->sprite, cloak);
		//Move along the list
		temp = temp->m_last;
	}
	//Call the base display method
	Attack_Wave::Display(surface);
}
//Non defualt constructor does nothing beyond calling the base class constructor
Attack_Wave_III::Attack_Wave_III(int x, int y, int  number)
:Attack_Wave(x, y, number)
{
}
//The defualt constructor simiply calls the base class
Attack_Wave_III::Attack_Wave_III()
:Attack_Wave()
{
}

