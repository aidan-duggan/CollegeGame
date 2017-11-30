#ifndef CLASS_SPRITE
#define CLASS_SPRITE

#include "vector.h"						//Header files for classes used
#include "weapons.h"					//
#include "weaponlist.h"

#include "SDL//include//SDL.h"						// Needed SDL
#include "SDL//include//SDL_ttf.h"					// 
#include "SDL//include//SDL_mixer.h"				//
#include "SDL//include//SDL_image.h"				//
#pragma comment(lib, "SDL//lib//SDL.lib")			//
#pragma comment(lib, "SDL//lib//SDLmain.lib")		//
#pragma comment(lib, "SDL//lib//SDL_ttf.lib")		//
#pragma comment (lib, "SDL//lib//SDL_mixer.lib")	//
#pragma comment (lib, "SDL//lib//SDL_image.lib")	//
				


//This is the sprite class, used for positional stats, weapon stats, 
//everything is public to make it easier on the derived classes. 
class Sprite
{
private:
	//variable for screeen size
	int m_screenW;
	int m_screenH;

public:
	//Pointers for images and sounds
	Mix_Chunk *photon;
	SDL_Surface *sprite;
	SDL_Surface *explode;

	//Booleans for images and active sprite and active explosions
	bool m_imageloaded;
	bool m_explode_loaded;
	bool m_active;
	bool m_explosion;
	bool m_soundloaded;

	//Vectors for position and velocity
	Vector Position;
	Vector Velocity;

	//photons for torpedoes and pointer for lasers
	Weapons photons;
	Weaponlist *lasers;

	//Int m_torpedoes to know how many in stock, m_ammo to hold the size of the lasers array
	int m_torpedoes;
	int m_ammo;

	//Counter for the lenght of explosions
	int expl_time;

	//methods
	//Defualt contructor
	Sprite();
	//Non defualt constructor
	Sprite(int x, int y);
	//Method to Update the sprite
	void Update(int x, int y);
	//Method to Display the sprite
	void display(SDL_Surface *surf);
	//Methods to set position and velocity of sprite
	void SetPosition(double x, double y);
	void SetVelocity(double x, double y);
	//Method to set image of sprite
	void SetImage(char *image_name);
	//Methods to set X position and velocity
	double GetPosition_x();
	double GetVelocity_x();
	//Methods to set Y position and velocity
	double GetPosition_y();
	double GetVelocity_y();
	//Methods to set and get active state
	bool GetActive();
	void SetActive(bool Active);
	//Methods to fire lasers and torpedoes
	void Fire( Vector Vel, int direction);
	void FirePhotons( Vector Vel, int direction);
	//Methods to get and set explosion state
	void SetExplosion(bool Active);
	bool GetExplosion();
	//Set pixel function
	void setPixel(SDL_Surface *surf, int k, int j,int colour);
	//Destructor
	~Sprite();

};

#endif
