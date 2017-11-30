#include <iostream>
#include "star_field.h"

//Default constructor sets the size to zero so that further loops won't do anything
Star_Field::Star_Field()
{
	size = 0;
}

//Standard constructor takes the screen sizes to randomly place the particles, with random velocitys
//it also sets the size variable to the size of the arrays
Star_Field::Star_Field(int x, int y)
{
	size = 500;

	for(int k = 0; k < size; k++)
	{
		m_position[k] = Vector(rand()%x, rand()%y);
		//Only y velocity is set since they are all moving down the screen
		m_velocity[k] = Vector(0,(rand()%5 +1));
	}
}

//Updates the positions of the particles and tests to see if the go outside the screen
void Star_Field::Update(int x, int y)
{
	for(int k = 0; k < size; k++)
	{
		m_position[k] = m_position[k] +	m_velocity[k];

		if(m_position[k].m_x  > x || m_position[k].m_x < 0)
		{
			m_position[k] = Vector(rand()%x, 0);
			m_velocity[k] = Vector(0,(rand()%5)+1);		
		}

		if(m_position[k].m_y + 3> y || m_position[k].m_y < 0)
		{
			m_position[k] = Vector(rand()%x, 0);
			m_velocity[k] = Vector(0,(rand()%5)+1);		
		}

	}
}

//Simply sets a pixel at the position of each particle
void Star_Field::Display(SDL_Surface *surface)
{
	for(int k = 0; k < size; k++)
	{
		setPixel(surface, static_cast<int>(m_position[k].m_x), static_cast<int>(m_position[k].m_y), 0xffffff);
	}
}

//Basic set pixel function
void Star_Field::setPixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	// This is a little complicated: we need to determine where in the memory
	// allocated for the screen we need to set the colour corresponding to the
	// pixel (x,y).  We'll explain this calculation later in the course.
	Uint8 *p = static_cast<Uint8*>(surface->pixels) + y*surface->pitch + x*4;

	// Store the colour value in the pixel location
	*reinterpret_cast<Uint32*>(p) = color;
}
