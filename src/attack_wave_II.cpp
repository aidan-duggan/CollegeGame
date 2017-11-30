#include "attack_wave_II.h"
#include <iostream>

//Default constructor calls the base one and sets the shields to NULL
//Also set screen sizes to zero
Attack_Wave_II::Attack_Wave_II()
:Attack_Wave()
{
	shields = NULL;
	m_shields_image = NULL;
}

//This constructor calls the base class constructor and creats an int shields for each enemy sprite
//Sets the screen sizes
Attack_Wave_II::Attack_Wave_II(int x, int y, int number)
:Attack_Wave(x, y, number)
{
	//Set the image and shields pointer to NULL
	shields = NULL;
	m_shields_image = NULL;
	
	//create new shields
	shields = new int[m_number_ships];
	//GO through each ship and set it shields
	for(int i = 0; i < m_number_ships; i++)
	{
		shields[i] = 1;
	}
	//Load the image for shields
	m_shields_image = new SDL_Surface;
	m_shields_image = IMG_Load("C:\\Star Trek\\content\\images\\shieldfull.GIF");
}

//This test if a ship was destroyed if it has shields then re activate it and depletes the shields
void Attack_Wave_II::Update_Attack(int x, int y, double enemy_x, double enemy_y)
{
	//Create a temp pointer to spritelist
	Spritelist *temp;
	temp = enemies;
	//and a variable for the shields
	int i = 0;
	//go through the list
	while(temp != NULL)
	{
		//If the ship isn't active
		if(!temp->GetActive())
		{
			//See if it has any shields left
			if(shields[i] > 0)
			{
				//If so stop the exlposion reduce the shields and reactivate the cruiser
				temp->SetExplosion(false);
				shields[i]--;
				temp->SetActive(true);
				temp->SetVelocity(0, 0.5);
			}
		}
		//Move along the list and the shields
		temp = temp->m_last;
		i++;
	}

	//call base class Update method
	Attack_Wave::Update_Attack(x, y, enemy_x, enemy_y);


}
//Destructor just deletes the shields
Attack_Wave_II::~Attack_Wave_II()
{
	delete[] shields;
	delete m_shields_image;
}

//This displays the wave
void Attack_Wave_II::Display(SDL_Surface *surf)
{
	//Create a temp pointer to spritelist
	Spritelist *temp;
	temp = enemies;
	//and a variable for the shields
	int i = 0;
	//go through the list
	while(temp != NULL)
	{
		//if it has shields and is active draw them
		if(shields != NULL && shields[i] > 0 && temp->GetActive() && m_shields_image != NULL)
		{
			SDL_Rect loc;
			loc.w = loc.h = 32;
			loc.x = static_cast<int>(temp->Position.m_x-loc.w/2);
			loc.y = static_cast<int>(temp->Position.m_y-loc.h/2);
			SDL_BlitSurface(m_shields_image, 0, surf, &loc);
		}
		//Move along the list and shields
		temp = temp->m_last;
		i++;
	}
	//Call base class display method
	Attack_Wave::Display(surf);
}


