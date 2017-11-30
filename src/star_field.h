#ifndef CLASS_STAR_FIELD
#define CLASS_STAR_FIELD

#include "vector.h"						//Header file for classes used

#include "SDL//include//SDL.h"						// Needed SDL
#include "SDL//include//SDL_ttf.h"					// 
#include "SDL//include//SDL_mixer.h"				//
#include "SDL//include//SDL_image.h"				//
#pragma comment(lib, "SDL//lib//SDL.lib")			//
#pragma comment(lib, "SDL//lib//SDLmain.lib")		//
#pragma comment(lib, "SDL//lib//SDL_ttf.lib")		//
#pragma comment (lib, "SDL//lib//SDL_mixer.lib")	//
#pragma comment (lib, "SDL//lib//SDL_image.lib")	//
				


//Class used to create the background star field
class Star_Field
{
private:

	//star field is made of an array of particles with positions and velocitys
	Vector m_position[500];
	Vector m_velocity[500];

	//size of the array used
	int size;

public:

	Star_Field();
	//Constructor to set inital positions and velocitys with in the screen size
	Star_Field(int x, int y);
	//Method to update star field
	void Update(int x, int y);
	//method to display teh star field
	void Display(SDL_Surface *surface);
	//Method to set pixels
	void setPixel(SDL_Surface *dst, int x, int y, Uint32 color);

};

#endif