#include <iostream>		//Various header files for Classes and functions
#include "vector.h"
#include "weapons.h"
#include <cmath>

using namespace std;

//Default constructor setting everything to false, Vector default constructor will set positions and velocity to zero
Weapons::Weapons()
{
	m_blast_radius = 0;
	m_imageloaded = false;
	m_active = false;
}

//Specfic constructor to set position and velocity, set blast radius (>0 if its a torpedeo), and activate it.
Weapons::Weapons( Vector &position, Vector &velocity, int blast)
{
	m_position = position;
	m_velocity = velocity;

	m_blast_radius = blast;
	m_active = true;
	m_imageloaded = false;
}

//Update the position of the weapon, deactivateing if it goes of the screen. Also set the screen width and height for the set pixel function
void Weapons::update_position(int screen_x, int screen_y)
{
	m_position = m_position + m_velocity;

	if(m_position.m_x +3 > screen_x || m_position.m_x -3< 0)
		m_active = false;

	if(m_position.m_y + 3> screen_y || m_position.m_y -3< 0)
		m_active = false;
}

//Displays active weapons
void Weapons::display(SDL_Surface *surf)
{
	//if active and imageloaded blit to screen or else set pixels to the screen
	if(m_active)
	{
		//If image loaded
		if(m_imageloaded)
		{
			SDL_Rect loc;
			loc.w = loc.h = 16;
			loc.x = static_cast<int>(m_position.m_x);
			loc.y = static_cast<int>(m_position.m_y);
			//Move between different sub images
			SDL_Rect subImage; 
			if(static_cast<int>(m_position.m_y)%50 <= 25)
			{
				subImage.x = 0;
			}
			else
			{
				subImage.x = 16;
			}

			subImage.y =0; 
			subImage.w = subImage.h = 16;
			//Different sized images for lasers and torpedoes
			if(m_blast_radius == 0)
				subImage.h = 32;
			//Blit the image
			SDL_BlitSurface(m_image, &subImage, surf, &loc);
		}
	}
}

//Sets the weapons m_active variable
void Weapons::SetActive(bool active)
{
	m_active = active;
}

//returns the weapons m_active variable
bool Weapons::GetActive()
{
	return m_active;
}

//returns the x position
double Weapons::GetPosition_x()
{
	return m_position.m_x;
}

//returns the y position
double Weapons::GetPosition_y()
{
	return m_position.m_y;
}

//sets the x and y position
void Weapons::SetPosition(double x, double y)
{
	m_position.m_x = x;
	m_position.m_y = y;
}

//sets the x and y velocity
void Weapons::SetVelocity( double x, double y)
{
	m_velocity.m_x = x;
	m_velocity.m_y = y;
}

//set the image of the weapons (when used represents a torpedeo along with setting a blast radius above 0)
void Weapons::SetImage(char *image_name)
{
	if(m_imageloaded)
	{
		SDL_FreeSurface(m_image);
	}

	m_imageloaded = true;
	m_image = IMG_Load(image_name);
}

//Destructor
Weapons::~Weapons()
{
	if(m_imageloaded)
	{
		SDL_FreeSurface(m_image);
	}
}
