#include <iostream>
#include "sprite.h"


#include "SDL//include//SDL.h"						// Needed SDL
#pragma comment(lib, "SDL//lib//SDL.lib")			//

//This Class controls the Players Sprite
class Player
{
private:
	//Pointers for live, score and torpedoes images and pointer for music
	SDL_Surface *lives;
	SDL_Surface *score;
	SDL_Surface *torpedoes_image;
	Mix_Chunk *phaser;

	//Vector to control the speed of the lasers
	Vector Weapon_Speed;

	//variable for shields
	int m_shields;

public:
	//The Sprite the player controls
	Sprite *m_your_ship;
	//Variables to hold, score, lives, etc.
	int m_score;
	int m_lives;
	int m_rate_fire;
	int k;
	//Boolean to hold if the game is over yet
	bool Game_Over;
	//Variable to deal with protection when you re appear after dying
	int m_restart_shield;
	//Defualt constructor
	Player();
	//Non Defualt Constructor
	Player(int x, int y);
	//Method to update the player
	void Update(int x, int y);
	//Method to check for key presses
	void Inputs();
	//Method to display player, returns bool to sperate it from display final score
	void Display(SDL_Surface *surface);
	//Method to draw shiels
	void Player::Draw_Shields(int x, int y, int r, int colour, SDL_Surface *surf );
	//Method to display the score on the end screen
	void Display_Final_Score(SDL_Surface *surface, int x, int y);
	//Method to recharge player shields
	void rechargeShields();
	//Destructor
	~Player();


};