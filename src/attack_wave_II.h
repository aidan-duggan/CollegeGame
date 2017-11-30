#ifndef CLASS_ATTACK_WAVE_II
#define CLASS_ATTACK_WAVE_II

#include "attack_wave.h"
//This is a derived class of Attack_Wave which adds extra diffcultly to the enemies
class Attack_Wave_II: public Attack_Wave
{
public:
	//Given an unknown size of ship this holds the number of ships in each ship
	int *shields;
	//To hold the image of teh shields
	SDL_Surface *m_shields_image;

	//Most of the methods need to be edited, and draw shields to display the shields
	Attack_Wave_II();
	//Constructor method like base class
	Attack_Wave_II(int x, int y, int number);
	//Update method like base class
	void Update_Attack(int x, int y, double enemy_x, double enemy_y);
	//Display method like base class
	void Display(SDL_Surface *surf);
	//Destructor
	~Attack_Wave_II();
};

#endif