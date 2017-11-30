#include <iostream>
#include "player.h"
#include <cmath>

using namespace std;

//Defualt constructor sets the variables to zero.
Player::Player()
{
	m_shields = 0;
	m_restart_shield = 0;
	m_lives = 0;
	m_score = 0;
	m_rate_fire = 0;
	k = 0;
	Game_Over = false;
	m_your_ship = new Sprite;
}

//Constructor sets the player up to work
Player::Player(int x, int y)
{
	//Sets lives to 3 and sets the score to zero, and end game to false
	m_lives = 3;
	m_score = 0;
	Game_Over = false;

	//Set the shields
	m_shields = 3;

	//Set restart shield time
	m_restart_shield = 0;

	//Sets the speed of the playersweapons
	Weapon_Speed = Vector(0, -.75);

	//Controls the firing of weapons to prevent firing to fast
	m_rate_fire = 85;
	k = 0;

	//Sets the base values of the Sprite, loaded image and sets position
	m_your_ship = new Sprite(x, y);

	m_your_ship->SetImage("C:\\Star Trek\\content\\images\\Ship.GIF");
	m_your_ship->SetPosition(x/2, (y - y/10));

	//Loads Images for score, lives, torpedoes and louds the sound
	lives = new SDL_Surface;
	lives = IMG_Load("C:\\Star Trek\\content\\images\\lives.GIF");

	score = new SDL_Surface;	
	score = IMG_Load("C:\\Star Trek\\content\\images\\score.GIF");

	torpedoes_image = new SDL_Surface;
	torpedoes_image = IMG_Load("C:\\Star Trek\\content\\images\\torp1.GIF");

	phaser = Mix_LoadWAV( "C:\\Star Trek\\content\\sounds\\Phaser.wav" ); 
}

//This method updates the sprite. Displays score, lives and stock of torpedoes
//Also tests to see if the game is over
void Player::Update(int x, int y)
{
	//if the player is deactive and has shields
	if(!m_your_ship->GetActive() && m_shields > 0)
	{
		//reduce shields and reactivate him
		m_shields--;
		m_your_ship->SetActive(true);
		m_your_ship->SetExplosion(false);
	}
	//If the ship is deactive and the explosion is over
	if(!m_your_ship->GetActive() && !m_your_ship->GetExplosion() && m_shields == 0)
	{
		//test to see if the player has any lives left
		if(m_lives <= 0)
		{
			//If not game over
			Game_Over = true;
		}
		else
		{	
			//If so reduce lives and re activate the Sprite
			m_lives = m_lives - 1;
			m_your_ship->SetActive(true);
			m_your_ship->SetPosition(x/2, (y - y/10));
			m_restart_shield = 300;
			m_shields = 3;
		}

	}
	//Update the ship
	m_your_ship->Update(x, y);

}

//This displays the score at a point
void Player::Display_Final_Score(SDL_Surface *surface, int x, int y)
{
	//This displays the score. 
	int a[6];
	for(int h = 5; h >= 0; h--)
	{
		//The score is broken down into each digit
		a[h] = static_cast<int>(m_score/pow(10.0,h));
		a[h] = a[h]%10;

		//The image is displayed along the screen depending where it should go
		SDL_Rect loc;
		loc.w = loc.h = 16;
		loc.x = x + (5-h)*16;
		loc.y = y;
	
		//A different part of the image is displayed depending on the number
		//The image is a row of numbers, which part is displayed depends on the number
		SDL_Rect subImage; 
		subImage.x = 0; 
		subImage.y = 16*a[h]; 
		subImage.w = subImage.h = 16; 

		//The image is blitted to the screen
		SDL_BlitSurface(score, &subImage, surface, &loc);
	}
}
//Method to draw shields
void Player::Draw_Shields(int x, int y, int r, int colour, SDL_Surface *surf )
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
				m_your_ship->setPixel(surf, k, j, colour); 
			}
		}
	}
}

//Displays the player, score, lives and shields
void Player::Display(SDL_Surface *surface)
{
	//Go through the number of lives and display an image on the screen for each one
	for(int z = 1; z <= m_lives; z++)
	{
		SDL_Rect loc;
		loc.w = loc.h = 32;
		loc.x = 160 + z*32;
		loc.y = 16;
	
		SDL_BlitSurface(lives, 0, surface, &loc);
	}

	//Display the score
	Display_Final_Score(surface, 32, 24);
	
	//Go through each of the lives and display an image to represent them
	for(int h = 0; h < m_your_ship->m_torpedoes; h++)
	{
		SDL_Rect loc;
		loc.w = loc.h = 16;
		loc.x = 192 + h*16;
		loc.y = 48;
		SDL_BlitSurface(torpedoes_image, 0, surface, &loc);
	}

	//Display the ship or make it blink if the player has a protected restart
	if(m_restart_shield == 0 || m_restart_shield%2)
		m_your_ship->display(surface);

	//Set the colour depending on the number of shields
	int color;
	if(m_shields >= 3)
		color = 0x009900;

	if(m_shields == 2)
		color = 0xbb8800;

	if(m_shields == 1)
		color = 0xff0000;

	//If there are shields display them
	if(m_shields > 0)
		Draw_Shields(static_cast<int>(m_your_ship->GetPosition_x()), static_cast<int>(m_your_ship->GetPosition_y()), 18, color, surface );

	//Count down the shields from restarting till they reach zero
	if(m_restart_shield > 0)
		m_restart_shield--;
}

//Method to recharge teh shields
void Player::rechargeShields()
{
	m_shields = 3;
}

//Method to take in inputs from the player
void Player::Inputs()
{
	//Set sprites Velocity to zero
	m_your_ship->SetVelocity(0,0);

	//This deals with inputs from the key board.
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	//The arrow keys control the velocities
	if(keystate[SDL_SCANCODE_RIGHT])
	{ 
		m_your_ship->SetVelocity((0.5), (m_your_ship->GetVelocity_y()));
	}

	if(keystate[SDL_SCANCODE_LEFT])
	{ 
		m_your_ship->SetVelocity((-0.5), (m_your_ship->GetVelocity_y()));
	}

	if(keystate[SDL_SCANCODE_UP])
	{ 
		m_your_ship->SetVelocity((m_your_ship->GetVelocity_x()), (-0.5));
	}
	
	if(keystate[SDL_SCANCODE_DOWN])
	{ 
		m_your_ship->SetVelocity((m_your_ship->GetVelocity_x()),(0.5));
	}

	//This fires photon torpedoes
	if(keystate[SDL_SCANCODE_RCTRL])
	{ 
		//If the ship is active
		if(m_your_ship->GetActive())
		{
			//Fire photons
			m_your_ship->FirePhotons(Weapon_Speed, 1);
		}
	}
	
	//This is complex, designed to get the sprite to fire evenly and not bunched together
	if(m_your_ship->GetActive())
	{
		if(keystate[SDL_SCANCODE_SPACE])
		{
			//If k%rate_fire = zero fire or if k = zero fire
			if(k%m_rate_fire == 0 || k == 0)
			{
				//fire the weapon, play sound, move i to the next weapon in the array.
				m_your_ship->Fire(Weapon_Speed, 1);
				//Load the image for the lasers
				m_your_ship->lasers->SetImage("C:\\Star Trek\\content\\images\\laser.gif");	
				//Slightly change the starting position
				m_your_ship->lasers->SetPosition( m_your_ship->Position.m_x -8, m_your_ship->lasers->GetPosition_y());
				Mix_PlayChannel( -1, phaser, 0 );		
			}
			//Add to k when key is pressed, this is called a dozen times when the key is pressed so adds up quick
			k++;
		}
		else
			//If the key isn't pressed set k to -15, this means weapons fire even when the key is held down
			//and if the key is tapped it only fires once
			k = -20;
		
	}
}

//Destructor deals with deleting the images and sounds created
Player::~Player()
{
	delete m_your_ship;
	SDL_FreeSurface(lives);
	SDL_FreeSurface(score);
	SDL_FreeSurface(torpedoes_image);
	Mix_FreeChunk(phaser);
}
