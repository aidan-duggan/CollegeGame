#ifndef CLASS_BOSS
#define CLASS_BOSS

#include "cruiser.h"

//Boss controls the Cruiser, which is the Boss sprite. Much like Attack_Wave controls the Sprites
class Boss
{
private:
	//Same variables as attack_wave except includes shields
	int m_rate_fire, counter, shields;

public:
	//Pointer to a Cruiser instead of a Sprite ship
	Cruiser *boss_ship;
	//Defualt constructor
	Boss();
	//Method set the variables when the boss it activated
	Boss(int x, int y);
	//Method to update boss
	void Update_Attack(int x, int y, double enemy_x, double enemy_y);
	//Method to display boss
	void Display( SDL_Surface *surface);
	//Method to return direction boss should fire at
	Vector Direct_Fire(double x, double y);
	//Method to draw shields
	void Draw_Shields(int x, int y, int r, int colour, SDL_Surface *surf );
	//Destructor
	~Boss();

};

#endif