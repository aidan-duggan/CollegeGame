#ifndef CLASS_RESOURCES
#define CLASS_RESOURCES

#include "vector.h"

#include "SDL//include//SDL.h"						// Needed SDL
#include "SDL//include//SDL_ttf.h"					// 
#include "SDL//include//SDL_mixer.h"				//
#include "SDL//include//SDL_image.h"				//
#pragma comment(lib, "SDL//lib//SDL.lib")			//
#pragma comment(lib, "SDL//lib//SDLmain.lib")		//
#pragma comment(lib, "SDL//lib//SDL_ttf.lib")		//
#pragma comment (lib, "SDL//lib//SDL_mixer.lib")	//
#pragma comment (lib, "SDL//lib//SDL_image.lib")	//
//This Class deals bonuses in the game, gaining life or extra torpedoes
class Resources
{
private:
	//Vectors for holding position and velocity
	Vector m_position;
	Vector m_velocity;

	//Booleans for images, active and types
	bool m_type;
	bool m_imageLoaded;
	bool m_active;

	//Screen sizes and pointer to surfaces
	int m_screenW, m_screenH;
	SDL_Surface *m_image;

public:
	//Constructor
	Resources();
	//Non DEfualt Constructor
	Resources(int x, int y);
	//Method to Update the resources
	void Update();
	//Method to Display the resources
	void Display(SDL_Surface *surface);
	//Returns the position of the resources
	double GetPosition_x();
	double GetPosition_y();
	//Returns and sets teh state of teh resources
	bool GetActive();
	void SetActive(bool active);
	//Returns the type of resources
	bool GetType();
	//Destructor
	~Resources();
};

#endif