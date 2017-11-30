#include <iostream>
#include "resources.h"

//Defualt constructor sets everything to false and zero
Resources::Resources()
{
	m_active = false;
	m_screenW = m_screenH = 0;
	m_type = false;
	m_imageLoaded = false;
}

//Constructor set up the resources to appear on screen
Resources::Resources(int x, int y)
{
	//Activate
	m_active = true;

	//Set position randomly along the top, set velocity
	m_position.m_x = rand()%x;
	m_position.m_y = 0;

	m_velocity.m_x = 0;
	m_velocity.m_y = 0.5;

	//Sets the screen size for the update function
	m_screenW = x;
	m_screenH = y;
	
	//randomly sets the type
	m_type = rand()%2;

	//Depending on the type load an image
	if(m_type)
	{
		//if true load the image for Lives
		m_image = new SDL_Surface;	
		m_image = IMG_Load("C:\\Star Trek\\content\\images\\life.GIF");
		m_imageLoaded = true;
	}

	if(!m_type)
	{
		//if false load the image for torpedoes
		m_image = new SDL_Surface;	
		m_image = IMG_Load("C:\\Star Trek\\content\\images\\ammo.GIF");
		m_imageLoaded = true;
	}
}


//This method updates the position and test if its gone of the screen
void Resources::Update()
{
	//If active update position and test if off screen
	if(m_active)
	{
		m_position = m_position + m_velocity;

		if(m_position.m_x > m_screenW || m_position.m_x < 0)
			m_active = false;

		if(m_position.m_y > m_screenH || m_position.m_y < 0)
			m_active = false;
	}
}

//This method displays the image, if active
void Resources::Display(SDL_Surface *surface)
{
	if(m_active)
	{
		SDL_Rect loc;
		loc.w = loc.h = 16;
		loc.x = static_cast<int>(m_position.m_x - loc.w/2);
		loc.y = static_cast<int>(m_position.m_y - loc.h/2);
		SDL_BlitSurface(m_image, 0, surface, &loc);
	}
}

//Returns the x position
double Resources::GetPosition_x()
{
	return m_position.m_x;
}

//Returns the y position
double Resources::GetPosition_y()
{
	return m_position.m_y;
}

//Returns Active stat
bool Resources::GetActive()
{
	return m_active;
}

//Sets active stat
void Resources::SetActive(bool active)
{
	m_active = active;
}

//Return the type
bool Resources::GetType()
{
	return m_type;
}

//Defualt constructor deletes loaded images
Resources::~Resources()
{
	if(m_imageLoaded)
	{
		SDL_FreeSurface(m_image);
	}
}