#ifndef CLASS_ATTACK_WAVE_III
#define CLASS_ATTACK_WAVE_III

#include "attack_wave.h"
//This is a derived class of Attack_Wave which adds extra diffcultly to the enemies
class Attack_Wave_III: public Attack_Wave
{
public:
	//Only how the image is diplayed needs to be changed
	void Display( SDL_Surface *surface);
	//Defualt constructor
	Attack_Wave_III();
	//Non Defualt constructor
	Attack_Wave_III(int x, int y, int number);
};

#endif