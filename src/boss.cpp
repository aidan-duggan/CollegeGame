#include "boss.h"
#include <cmath>
#include <iostream>

using namespace std;

//Similiar to Attack Wave, sets variables to 0
Boss::Boss()
{	
	counter = 0;
	m_rate_fire = 0;
	shields = 0;
	//Creates a defualt cruiser effectively inactive
	boss_ship = new Cruiser;
}

//Non defualt constructor sets the Boss to attack
Boss::Boss(int x, int y)
{
	//Creates a Cruiser
	boss_ship = new Cruiser(x, y);
	//If no previous image loaded, load one
	if(!boss_ship->m_imageloaded)
	{
		boss_ship->SetImage("C:\\Star Trek\\content\\images\\cruiser.GIF");
	}
	//set the Velocity
	boss_ship->SetVelocity(0, 0.5);
	
	//Set the position randomly along the top with z variable to better avoid overlapping
	int z = rand()%16;
	x = rand()%(x-200)+ 100;
	boss_ship->SetPosition(x, z);

	//Sets the rate of fire and sets the number of shields the ship has.
	m_rate_fire = 253;
	counter = 0;
	shields = 2;

}

//Works like attack wave, takes the players position and returns a vector towards the player
Vector Boss::Direct_Fire(double x, double y)
{
	double length, length_x, length_y, vel_x, vel_y;
	Vector Vel;

	length_x = x - boss_ship->GetPosition_x();
	length_y = y - boss_ship->GetPosition_y();

	length = sqrt((length_x*length_x)+(length_y*length_y));

	vel_x =length_x/length;
	vel_y =length_y/length;

	Vel = Vector(vel_x, vel_y);

	return Vel;
}

//Updates the Cruiser, and fires
void Boss::Update_Attack(int x, int y, double enemy_x, double enemy_y)
{

	//If the ship isn't active
	if(!boss_ship->GetActive())
	{
		//See if it has any shields left
		if(shields > 0)
		{
			//If so stop the exlposion reduce the shields and reactivate the cruiser
			boss_ship->SetExplosion(false);
			shields--;
			boss_ship->SetActive(true);
			boss_ship->SetVelocity(0, 0.5);
		}
	}

	//Calculate the Vector towards the player
	Vector Vel;
	Vel = Direct_Fire(enemy_x, enemy_y);

	//Moves the cruiser towards the players sprite, at half the velocity of weapons
	boss_ship->SetVelocity(Vel.m_x/2, Vel.m_y/2);

	//Update cruiser
	boss_ship->Update(x, y);
	
	//After a certain time fire
	if(counter == m_rate_fire && boss_ship->GetActive())
	{
		boss_ship->Fire( Vel, -1);
		boss_ship->lasers->SetImage("c:\\Star Trek\\images\\laser2.gif");
		counter = 0;
	}
	//Update counter for firing
	counter++;		
	
}

//Similiar to MyCircle function except it doesn't fill the circle in
void Boss::Draw_Shields(int x, int y, int r, int colour, SDL_Surface *surf )
{
	
	// Determine the corners of the box that the circle fits into
	int x1 = (x-r);
	int x2 = (x+r);
	int y1 = (y-r);
	int y2 = (y+r);

	// Convert all value to doubles
	double dx = static_cast<double>(x);
	double dy = static_cast<double>(y);
	double dr2 = static_cast<double>(r*r);

	// Step through all pixels on the screen and determine if they
	// are inside or outside the circle.
	double di, dj, dist;
	for(int j=y1; j<y2; j++)
	{
		dj = static_cast<double>(j);
		for(int k=x1; k<x2; k++)
		{
			di = static_cast<double>(k);
			dist = (di-dx)*(di-dx) + (dj-dy)*(dj-dy);
			//Set a pixel if its on the screen inside the circle and outside a slightly smaller circle
			if(k >= 0 && j >= 0 && dist < dr2 && dist > (r-2)*(r-2))
			{
				//Just using the set pixel method from weapons nothing really to do with weapons
				boss_ship->setPixel(surf, k, j, colour); 
			}
		}
	}
}
//Thie method displays the boss
void Boss::Display( SDL_Surface *surface)
{
	int color;
	//display the ship
	boss_ship->display(surface);

	//Set the colour depending on the number of shields
	if(shields == 2)
		color = 0x00ff00;

	if(shields == 1)
		color = 0xff0000;

	//If there are shields display them
	if(shields > 0)
		Draw_Shields(static_cast<int>(boss_ship->GetPosition_x()), static_cast<int>(boss_ship->GetPosition_y()), 46, color, surface );
}
//Destructor deletes the Cruiser
Boss::~Boss()
{
	delete boss_ship;
}