#ifndef CLASS_ATTACK_WAVE
#define CLASS_ATTACK_WAVE

#include "vector.h"						//Header files for classes used
#include "weapons.h"					//
#include "spritelist.h"						//

#include "SDL//include//SDL.h"						// Needed SDL
#include "SDL//include//SDL_ttf.h"					// 
#include "SDL//include//SDL_mixer.h"				//
#include "SDL//include//SDL_image.h"				//
#pragma comment(lib, "SDL//lib//SDL.lib")			//
#pragma comment(lib, "SDL//lib//SDLmain.lib")		//
#pragma comment(lib, "SDL//lib//SDL_ttf.lib")		//
#pragma comment (lib, "SDL//lib//SDL_mixer.lib")	//
#pragma comment (lib, "SDL//lib//SDL_image.lib")	//
				
//Attack Wave controls the enemy sprites, much like player class controls the player sprite.
class Attack_Wave
{
public:
	//Variables for counting and controlling
	int m_rate_fire, counter;
	//Each attack wave is made of a list of sprites, number_ships will hold the size of the array to be allocated
	Spritelist *enemies;
	int m_number_ships;
	//Defualt constructor
	Attack_Wave();
	//Virtual method to allow derived classes, deals with activating attacks
	Attack_Wave(int x, int y, int number);
	//Virtual method to allow derived classes, deals with updateing attacks
	virtual void Update_Attack(int x, int y, double enemy_x, double enemy_y);
	//Virtual method to allow derived classes, deals with displaying attacks
	virtual void Display(SDL_Surface *surf);
	//Return is all of a wave is deactive
	bool test_active();
	//Sets the position of a wave
	void Set_Wave_Position(int x, int y);
	//Return the direction at which waves should fire
	Vector Direct_Fire(double x, double y, Spritelist *temp);
	//returns centre positions of a wave
	double Wave_Positionx();
	double Wave_Positiony();
	//Destructor
	~Attack_Wave();


};

#endif