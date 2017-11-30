#include <iostream>	
#include "Sprite.h"

using namespace std;

//Defualt constructor sets all booleans to false and all variables to zero 
Sprite::Sprite()
{
	m_screenW = 0;
	m_screenH = 0;
	m_active = false;
	m_imageloaded = false;
	m_explosion = false;
	m_explode_loaded = false;
	m_soundloaded = false;
	expl_time = 0;
	m_ammo = 0;
	m_torpedoes = 0;
	lasers = NULL;
}

//Constructor set the sprite up to be used by other classes
Sprite::Sprite(int x, int y)
{
	//set the start laser to NULL
	lasers = NULL;

	//Set the screen sizes
	m_screenW = x;
	m_screenH = y;

	//sets sprite active and explosion deactive
	m_active = true;
	m_explosion = false;
	m_imageloaded = false;
	m_explode_loaded = false;
	
	//sets variables for number of torpedoes and size of laser array. expl_time for the lenght of explosion
	expl_time = 1;
	m_torpedoes = 3;
	m_ammo = 25;

	//Set positions to zero, to be set later. Load the sound for the torpedoes
	Position.m_x = Position.m_y = Velocity.m_x = Velocity.m_y = 0;

	photon = Mix_LoadWAV( "C:\\Star Trek\\content\\sounds\\Photon.wav" );
	m_soundloaded = true;
	
}

//This method displays the sprite, and its lasers and photons
void Sprite::display(SDL_Surface *surf)
{
	//Display lasers, only if there are any
	if(lasers != NULL)
	{
		lasers->display(surf);
	}

	//Display Photons
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

	//This sets up the image for blitting, its based on the velocity 
	//so the image changes depending on which direction its moving.
 	SDL_Rect loc;
	loc.w = loc.h = 32;
	loc.x = static_cast<int>(Position.m_x-loc.w/2);
	loc.y = static_cast<int>(Position.m_y-loc.h/2);
	SDL_Rect subImage; 
	subImage.x = static_cast<int>(32 + 64*Velocity.m_x); 
	subImage.y = static_cast<int>(32 + 64*Velocity.m_y); 
	subImage.w = subImage.h = 32; 

	//If the sprite is active use the sprite image, 
	if(m_active)
	{
		SDL_BlitSurface(sprite, &subImage, surf, &loc);
	}

	//if its exploding use the explosion image.
	if(m_explosion)
	{
		SDL_BlitSurface(explode, &subImage, surf, &loc);
	}

}

//Set the sprites x-y position
void Sprite::SetPosition(double x, double y)
{
	Position.m_x = x;
	Position.m_y = y;
}

//Set the sprites x-y Velocity
void Sprite::SetVelocity( double x, double y)
{
	Velocity.m_x = x;
	Velocity.m_y = y;
}

//Update the Sprite and its weapons
void Sprite::Update(int x, int y)
{
	//If the sprite is active update its position
	if(m_active)
	{
		Position = Position + Velocity;
	}

	//Update all the sprites lasers if it has any
	if(lasers != NULL)
	{
		lasers->update_position(x, y, lasers);
	}
	//Update the sprites photons
	photons.update_position(x, y);

	//Test if the sprite has gone off the screen
	if(Position.m_x > x+16 || Position.m_x < 0 || Position.m_y > y+16 || Position.m_y < 0)
	{
		m_active = false;
	}
}

//This sets a given image for the sprite and loads the explosion image
void Sprite::SetImage(char *image_name)
{
	//If a previous image has been loaded, delete it
	if(m_imageloaded)
	{
		SDL_FreeSurface(sprite);
	}

	//Set imageloaded to true and load the image
	m_imageloaded = true; 
	sprite = IMG_Load(image_name);
	
	//If a previous explosion has been loaded delete it
	if(m_explode_loaded)
	{
		SDL_FreeSurface(explode);
	}

	//Set explosion loaded to true and load the explosion image
	m_explode_loaded = true;
	explode = IMG_Load("C:\\Star Trek\\content\\images\\explosion.GIF");
}

//Returns the x position
double Sprite::GetPosition_x()
{
	return Position.m_x;
}

//Returns the x velocity
double Sprite::GetVelocity_x()
{
	return Velocity.m_x;
}

//Returns the y position
double Sprite::GetPosition_y()
{
	return Position.m_y;
}

//Returns the y velocity
double Sprite::GetVelocity_y()
{
	return Velocity.m_y;
}

//Returns the sprites active state
bool Sprite::GetActive()
{
	return m_active;
}

//Sets the sprites active state
void Sprite::SetActive(bool Active)
{
	m_active = Active;
}

//Sets the sprites explosion state
void Sprite::SetExplosion(bool Active)
{
	m_explosion = Active;
}

//Returns the sprites explosion state
bool Sprite::GetExplosion()
{
	return m_explosion;
}

//This fires lasers at a given velocity in a given direction
void Sprite::Fire( Vector Vel, int direction)
{
	//create a temp and let it equal to the address of lasers
	Weaponlist *temp;
  	temp = lasers;
	//Fire lasers but creating a new laser and passing in the address of the old one
	lasers = new Weaponlist(temp, Position, Vel);
}

//This fires photons.
void Sprite::FirePhotons( Vector Vel, int direction)
{
	//Only one can be active at one time so it tests if the sprite photon is active 
	if(!photons.m_active)
	{
		////and if not, it test if the sprite has any more ammo left.
		if(m_torpedoes > 0)
		{
			//If it does it sets the position and velocity, loads the image, plays the sound and reduces the sprites ammo.
			photons = Weapons(Position, Vel, 150);
			photons.SetPosition( Position.m_x, (Position.m_y - direction*16));
			photons.SetImage("C:\\Star Trek\\content\\images\\torp.GIF");
			m_torpedoes--;
			Mix_PlayChannel( -1, photon, 0 );
		}
	}
}
//This set pixel is used by player and enemys so is placed in sprite for easy use
void Sprite::setPixel(SDL_Surface *surf,int k,int j,int  colour)
{
	//Don't let pixels be set outside the screen
	if( k > 0 && k < m_screenW)
	{
		if( j > 0 && j < m_screenH)
		{
			SDL_LockSurface(surf);
			// This is a little complicated: we need to determine where in the memory
			// allocated for the screen we need to set the colour corresponding to the
			// pixel (x,y).  We'll explain this calculation later in the course.
			Uint8 *p = static_cast<Uint8*>(surf->pixels) + j*surf->pitch + k* 4;

			// Store the colour value in the pixel location
			*reinterpret_cast<Uint32*>(p) = colour;
			SDL_UnlockSurface(surf);
		}
	}
}

//The Destructor frees the images and sounds of the sprite
Sprite::~Sprite()
{
	if(m_imageloaded)
	{
		SDL_FreeSurface(sprite);
	}
		
	if(m_explode_loaded)
	{
		SDL_FreeSurface(explode);
	}

	if(m_soundloaded)
	{
		Mix_FreeChunk(photon);
	}
}
