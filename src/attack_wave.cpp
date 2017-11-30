#include <iostream>			//Header files needed
#include <cmath>			//
#include "attack_wave.h"	//

using namespace std;

//The defualt constructor sets m_number_ships to zero to prevent array over running
//variables set to zero
Attack_Wave::Attack_Wave()
{
	m_rate_fire = 0;
	counter = 0;
	m_number_ships = 0;
	enemies = NULL;
}

//Non defualt constructor is called when attack_wave get ready to attack
Attack_Wave::Attack_Wave(int x, int y, int number)
{
	//Set the sprite pointer to NULL
	enemies = NULL;
	//Sets the passed in number to the number of sprite to be created
	m_number_ships = number;
	//create a temp to go through creating the list
	Spritelist *temp;
	//Goes through the number of ships 
	for(int i = 0; i < m_number_ships; i ++)
	{
		//Set the temp equal to the last enemies pointer
		temp = enemies;
		//and create a new sprite
		enemies = new Spritelist(temp, x, y);
		//and load the sprites image
		enemies->SetImage("C:\\Star Trek\\content\\images\\enemy.GIF");
		//Set the ships velocity
		enemies->SetVelocity(0, 0.5);
	}
	//This sets the wave position, taking the screen sizes.
	Set_Wave_Position(x, y);

	//This variables are used to time the sprites firing
	m_rate_fire = 513;
	counter = 0;

}

//This method updates the position of the sprites and has the sprites fire after a fixed time
void Attack_Wave::Update_Attack(int x, int y, double enemy_x, double enemy_y)
{
	Vector Vel;
	//If there are sprite do what follows, otherwise do nothing
	if(enemies != NULL)
	{
		//Update there position
		enemies->Update(x, y, enemies);
		//Create a temp pointer to go through the list
		Spritelist *temp;
		temp = enemies;
		//While the temp still points to something
		while(temp != NULL)
		{
			//If the counter has reached the rate of fire and the sprite is active Fire
			if(counter == m_rate_fire && temp->GetActive())
			{
				//This takes the position of the player to aim the weapons at the player
				Vel = Direct_Fire(enemy_x, enemy_y, temp);
				//Call fire
				temp->Fire( Vel, -1);
				//Load the lasers image
				temp->lasers->SetImage("C:\\Star Trek\\content\\images\\laser2.gif");
			}
			//Move to the next sprite in the list
			temp = temp->m_last;
		}	
		//If the counter gets to high reduce it
		if(counter == m_rate_fire)
		{
			counter = 0;
		}
		//add to counter
		counter++;
	}
}

//This method is used to see if any of the atack wave sprites are still active
bool Attack_Wave::test_active()
{
	//If the enemies pointer is NULL there are no ships
	if(enemies == NULL)
	{
		return true;
	}

	return false;
}

//This method takes the screen sizes and sets the sprites position in a random pattern 
//randomly along the top with z as a variable up and down to better avoid overlapping.
void Attack_Wave::Set_Wave_Position(int x, int y)
{
	//Create the z variable to change the y
	int z = rand()%16;
	//Set i to half the number of ship, un-importnat if it isn't even
	int i = m_number_ships/2;
	//Calculate the random position x, using i to keep it within the screen
	x = rand()%(x-i*100);
	//create the temp to go through the list of ships
	Spritelist *temp;
	temp = enemies;
	//Make i negative to create the v pattern
	i = -1*i;
	//Go through the list setting the positions
	while( temp != NULL)
	{
		temp->SetPosition((x - 50*i), 30 + i*i + z);
		temp = temp->m_last;
		i++;
	}
}

//This method takes the player sprite position and the attack wave sprite thats firing
//Then it calculates the direction the sprite should fire and returns it as a Vector
Vector Attack_Wave::Direct_Fire(double x, double y, Spritelist *temp)
{
	double lenght, lenght_x, lenght_y, vel_x, vel_y;
	Vector Vel;

	lenght_x = x - temp->GetPosition_x();
	lenght_y = y - temp->GetPosition_y();

	lenght = sqrt((lenght_x*lenght_x)+(lenght_y*lenght_y));

	vel_x =lenght_x/lenght;
	vel_y =lenght_y/lenght;

	Vel = Vector(vel_x, vel_y);

	return Vel;
}

//This returns the x position of the centre Sprite
double Attack_Wave::Wave_Positionx()
{
	//Provided there are sprites
	if(enemies != NULL)
	{
		//Provided there are sprites
		Spritelist *temp;
		temp = enemies;
		//Go through the list till you get ot the last sprite (when it point back to NULL
		while(temp->m_last != NULL)
		{
			temp = temp->m_last;
		}
		//return the mid distance between the first and last sprite
		return (enemies->GetPosition_x() + temp->GetPosition_x())/2;
	}
	//otherwize return zero
	return 0;
}

//This returns the y position of the centre Sprite
double Attack_Wave::Wave_Positiony()
{
	//Provided there are sprites
	if(enemies != NULL)
	{
		//Provided there are sprites
		Spritelist *temp;
		temp = enemies;
		//Go through the list till you get ot the last sprite (when it point back to NULL
		while(temp->m_last != NULL)
		{
			temp = temp->m_last;
		}
		//return the mid distance between the first and last sprite
		return (enemies->GetPosition_y() + temp->GetPosition_y())/2;
	}
	//otherwize return zero
	return 0;
}

//this displays the sprites
void Attack_Wave::Display(SDL_Surface *surf)
{
	//if there are sprites display them
	if(enemies != NULL)
	{
		enemies->display(surf);
	}
}
//Destructor Deletes the spirtes
Attack_Wave::~Attack_Wave()
{
	delete enemies;
}

