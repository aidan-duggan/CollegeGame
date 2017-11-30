#ifndef CLASS_WEAPONS
#define CLASS_WEAPONS

#include "vector.h"						//Class header

#include "SDL//include//SDL.h"						// Needed SDL
#include "SDL//include//SDL_ttf.h"					// 
#include "SDL//include//SDL_mixer.h"				//
#include "SDL//include//SDL_image.h"				//
#pragma comment(lib, "SDL//lib//SDL.lib")			//
#pragma comment(lib, "SDL//lib//SDLmain.lib")		//
#pragma comment(lib, "SDL//lib//SDL_ttf.lib")		//
#pragma comment (lib, "SDL//lib//SDL_mixer.lib")	//
#pragma comment (lib, "SDL//lib//SDL_image.lib")	//
				
//This Class is for lasers and photons.
class Weapons
{
private:

	//Vectors for position and Velocity
	Vector m_position;
	Vector m_velocity;

public:
	//pointer for SDL image and bool for knowing if its loaded
	SDL_Surface *m_image;
	bool m_imageloaded;

	//Bool for knowing if the weapon is active and variable for knowing its blast radius
	bool m_active;
	int m_blast_radius;
	//Defualt constructor
	Weapons();
	//Non Defualt constructor to set values
	Weapons( Vector &position, Vector &velocity, int blast);
	//Method to update weapons
	void update_position(int x, int y);
	//Method to display weapons
	void display(SDL_Surface *Surface);
	//Methods to get and set active state
	void SetActive(bool active);
	bool GetActive();
	//Methods to return position
	double GetPosition_x();
	double GetPosition_y();
	//Methods to set position and velocity
	void SetPosition(double x, double y);
	void SetVelocity(double x, double y);
	//method to set image
	void SetImage(char *image_name);
	//Destructor
	~Weapons();

};

#endif
