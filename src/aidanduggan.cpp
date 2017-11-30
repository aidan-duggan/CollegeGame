#include <iostream>			//Needed for cin, cout, cerr, endl
#include <string>			//For taking in text
#include "weapons.h"		//The various header files for the classes I've created
#include "vector.h"			//
#include "sprite.h"			//
#include "player.h"			//
#include "attack_wave.h"	//
#include "star_field.h"		//
#include "cruiser.h"		//
#include "Boss.h"			//
#include "resources.h"		//
#include "attack_wave_II.h"	//
#include "attack_wave_III.h"//

#include "SDL//include//SDL.h"						// Needed SDL
#include "SDL//include//SDL_ttf.h"					// 
#include "SDL//include//SDL_mixer.h"				//
#include "SDL//include//SDL_image.h"				//
#pragma comment(lib, "SDL//lib//SDL.lib")			//
#pragma comment(lib, "SDL//lib//SDLmain.lib")		//
#pragma comment(lib, "SDL//lib//SDL_ttf.lib")		//
#pragma comment (lib, "SDL//lib//SDL_mixer.lib")	//
#pragma comment (lib, "SDL//lib//SDL_image.lib")	//

using namespace std;

// Function prototypes
void freeFont(TTF_Font *&font);                         //This is the only one un-edited
void render(SDL_Surface *surf, TTF_Font *font);
void collision(Player &person, Sprite &enemy, int size);
bool over_lap_test( Attack_Wave &aWave, Attack_Wave &bWave);
bool test_collision(double x, double y, double r, double px , double py);
void blast_radius(double pos_x, double pos_y, int radius);
void test_supplies();
void cheats();
void renew_attack();
bool test_all_waves();
void leveltiming();
void Screen_Order();
void start_screen(SDL_Rect rect);
void end_screen(SDL_Rect rect);
void winning_screen(SDL_Rect rect);

// Define some constants for screen dimension to be used throughout the program
const int screenWidth = 800;
const int screenHeight = 700;

// Define the global surface, font and sound to use in the program.
SDL_Surface *surf;
TTF_Font *font;
Mix_Chunk *blast; 
Mix_Music *music;

// Define various variables as counters for timing events
int attack_delay = 500;
int frame = 0;
int m_size = 3;
const int max_size = 5;
bool attack = true;
int counter = 1;
bool game_Won = false;

//Define a variable to control the speed of the game
int speed;

//To enter players name
string name;
char *capt;

//Define the Classes that make up the game, background, enemys, bosses, player and supplies
//Kligons is an array of pointers because it will be dynamically allocated and derived,
//C++ doesn't allow a pointer to an array of base classes to be pointed to derive classes
//therefore an array of pointers is declared which CAN be re-pointed to derived classes
Star_Field background;
Attack_Wave* Klingons[max_size];
Boss *Badguy = new Boss;
Player *Defiant;
Resources *supplies = new Resources;




//This function controls the aboved defined classes which make up the game
void render()
{
	//Updates and collision are grouped together for easy control of how fast they are called
	if(frame%speed ==0)
	{
		//Go through each of the enemy ships Update date stats and display, 
		for(int i= 0; i< m_size; i++)
		{
			Klingons[i]->Update_Attack(screenWidth, screenHeight, Defiant->m_your_ship->GetPosition_x(), Defiant->m_your_ship->GetPosition_y());
			//create a temp pointer to spritelist
			Spritelist *temp = Klingons[i]->enemies;
			//Go down the list
			while(temp != NULL)
			{
				//and test for collisions with the player
				collision((*Defiant), (*temp), 16);
				//move along the list
				temp = temp->m_last;
			}
		}

		//This deals with bonuses/supplies in the game. updating and testing if the player has hit it
		test_supplies();
		supplies->Update();
		//Update and display the Boss, test for collisions with the player 
		Badguy->Update_Attack(screenWidth, screenHeight, Defiant->m_your_ship->GetPosition_x(), Defiant->m_your_ship->GetPosition_y());
		collision((*Defiant), (*Badguy->boss_ship), 32);	
		//Update the player and test for keys
		Defiant->Update(screenWidth, screenHeight);
		Defiant->Inputs();
		//Update the star field
		background.Update(screenWidth, screenHeight);

	}

	//Display Player and Boss
	Defiant->Display(surf);
	Badguy->Display(surf);

	//display the background starfield
	background.Display(surf);

	//Display each of teh waves
	for(int i =0; i < m_size; i++)
	{
		Klingons[i]->Display(surf);
	}
	//Display the supplies
	supplies->Display(surf);

	//If the attack is happening then re-new it
	if(attack)
	{
		renew_attack();
	}

	//Update the attack_delay counter when 
	if(attack_delay <= m_size *1000 && frame%speed == 0)
		attack_delay++;

	//calling the Boss at a particular time
	if(frame%(m_size *2500) == 0 && !Badguy->boss_ship->GetActive())
	{
		delete Badguy;
		Badguy = new Boss(screenWidth, screenHeight);
	}

	//calling the Resources at a particular time
	if(frame%(m_size *2000) == 0 && !supplies->GetActive())
	{
		delete supplies;
		supplies = new Resources(screenWidth, screenHeight);
	}

	//If attack_delay gets to high stall it at size*1000 otherwise it will cause array over run
	if(attack_delay > m_size *1000)
	{
		attack_delay = m_size *1000;
	}

	//This functin looks after timing of attacks
	leveltiming();
	
}


// Main program.  This needs to initialise the graphics (screen + font)
// and then loop, waiting for user input while updating the screen frequently
// to allow for animation effects, and to allow the operating system to update
// the application window.
int main(int argc, char *argv[])
{
	//set the pointers to a certain number of attack waves
	for(int i = 0; i < m_size; i++)
	{
		Klingons[i] = new Attack_Wave_II();
	}

	//seed the random number generator
	srand(0);
	//variable for speed
	speed = -1;
	//Opening text while player enters name and sets diffculty
	cout << " Welcome, Please enter your name to start:" << endl;
	cin >> name;
	//To insure the player enters a valid number
	while(speed <  1 || speed > 5)
	{
		cout << " and please enter speed between 1 and 5: 1 normal 5 slowest" << endl;
		cin >> speed;
	}

	//add captian to the name
	name = "captain " + name;
	//declare space to hold the string name as a *char
	capt = new char[name.size()+1];

	//Copy over the string to *char
	for(unsigned int i =0; i < name.size(); i++)
	{
		capt[i] = name[i];
	}
	//Add a zero to the last slot in the *char
	capt[name.size()] = 0;

	//A hit for the cheats I encoded
	cout << endl << " Having trouble? Need a few pointers?" << endl << endl;
	cout << " 057A4EF6" << endl;
	cout << " 38F34AB9" << endl;
	cout << " 4C65DF74" << endl;
	cout << endl << "  What?.." << endl;

	// Initialize SDL's	subsystems - in this case, only video.
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		//If an error cout what the error is
		cout << "Error loading images" << endl;
	}

	// Initialise the font system
	if(TTF_Init() == -1)
	{
		cout << "Error loading fonts" << endl;
	}

	// Now open a specific font (this needs to be in the same directory
	// as the program.  Using font size = 32 for a nice big display.
	font = TTF_OpenFont("C:\\Star Trek\\content\\TNGMONIT.ttf", 32);

	SDL_Window *sdlWindow;
	SDL_Renderer *sdlRenderer;
	SDL_CreateWindowAndRenderer(screenWidth, screenHeight, SDL_SWSURFACE, &sdlWindow, &sdlRenderer);

	// Attempt to create a window of the specified dimensions with 32bit pixels.
	surf = SDL_CreateRGBSurface(0, screenWidth, screenHeight, 32,
		0x00FF0000,
		0x0000FF00,
		0x000000FF,
		0xFF000000);
	SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		screenWidth, screenHeight);
	SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_NONE);
	
	//Attempt to create the audio settings, 
	if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
	{
		cout << "Error loading sound" << endl;
	}


	//Load sound for blasts and initalise the Player and Background and background music
	blast = Mix_LoadWAV( "C:\\Star Trek\\content\\sounds\\Blast.wav" ); 
	music = Mix_LoadMUS("C:\\Star Trek\\content\\sounds\\music.wav");

	Defiant = new Player(screenWidth, screenHeight);

	background = Star_Field(screenWidth, screenHeight);

	// Main loop: loop until the user hits the ESC key.
	bool quitNow = false;
	while (!quitNow)
	{
		// Lock	surface	if needed
		if (SDL_MUSTLOCK(surf))
		{
			if (SDL_LockSurface(surf) < 0)
			{
				cerr << "Unable to lock surface: " << SDL_GetError() << endl;
				exit(1);
				
			}
		}

		//This function deals with the timing of events and displaying various things
		Screen_Order();

		// Tell SDL to update the whole	screen, so that all our drawing 
		// gets flushed to the screen
		SDL_UpdateTexture(sdlTexture, NULL, surf->pixels, surf->pitch);
		SDL_RenderClear(sdlRenderer);
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
		SDL_RenderPresent(sdlRenderer);
		
		// Unlock if needed
		if (SDL_MUSTLOCK(surf))
		{
			SDL_UnlockSurface(surf);
		}

		// Poll for events, and handle the ones we care about.
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			// Handle each type of event we want to trap...
			switch (event.type)
			{
			case SDL_KEYDOWN:
				// If escape is pressed the quit
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quitNow = true;

				// If 's' is pressed the quit
				if (event.key.keysym.sym == SDLK_s)
				{
					//If the music is paused 
					if( Mix_PausedMusic() == 1 ) 
					{ 
						//Resume the music 
						Mix_ResumeMusic(); 
					} 
					//If the music is playing 
					else 
					{	 
						//Pause the music 
						Mix_PauseMusic(); 
					}
				}
				//This controls the speed of the game
				//High is slower
				if (event.key.keysym.sym == SDLK_EQUALS)
					if(speed > 1)
						speed--;
				if (event.key.keysym.sym == SDLK_MINUS)
					if(speed < 5)
						speed++;
					
				break;
			case SDL_QUIT:
				// OS requested that the application quit
				quitNow = true;
				break;
			}
		}

	}

	// If we get here then the user has requested that the appication quit
	// or the application has quit as a result of the windows system requesting
	// it to do so (e.g. window kill button was clicked).
	// Free up the resources the SDL created.
	delete capt;
	Mix_FreeChunk(blast);
	Mix_FreeMusic(music);
	freeFont(font);
	SDL_Quit();
	delete Badguy;
	delete supplies;

	//Delete what the Klingons pointer are pointing to
	for(int i =0; i < m_size; i++)
	{
		delete Klingons[i];
	}

	return 0;
}


// Free the font resource when finished with it.
void freeFont(TTF_Font *&font)
{
	// First check to make sure the font is not NULL
	if(font)
	{
		TTF_CloseFont(font);
		font=0;
	}
}

//This function tests for collision between the player and a sprite
void collision(Player &person, Sprite &enemy, int size)
{
	//First test if the sprites are active and then if they are with in a certain distance of each other. If so do things
	if(enemy.GetActive() && person.m_your_ship->GetActive() && person.m_restart_shield == 0)
	{
		if(test_collision(person.m_your_ship->GetPosition_x(), person.m_your_ship->GetPosition_y(), (16+size), enemy.GetPosition_x(), enemy.GetPosition_y()))
		{
			//If they are touching set the player sprite and enemy sprite to false 
			person.m_your_ship->SetActive(false);
			person.m_your_ship->SetExplosion(true);
			//and activate their explosions and play noise
			enemy.SetActive(false);
			enemy.SetExplosion(true);
			Mix_PlayChannel( -1, blast, 0 );
		}
	}
	//Create a temp pointer to Weaponlist
	Weaponlist *temp;
	temp = person.m_your_ship->lasers;
	//Go through the weaponlist
	while(temp != NULL)
	{
		//Test to see if the laser and the enemy sprite is active and if they are hitting each other
		if(temp->GetActive() && enemy.GetActive())
		{
			if(test_collision(temp->GetPosition_x(), temp->GetPosition_y(), size, enemy.GetPosition_x(), enemy.GetPosition_y()))
			{
				//If they hit set the laser to false and the enemy sprite to false, 
				temp->SetActive(false);
				enemy.SetActive(false);
				//cause the explosion, play a sounds and update the score.
				enemy.SetExplosion(true);
				person.m_score = person.m_score + 3;
				Mix_PlayChannel( -1, blast, 0 );
			}
		}
		//Move along the weaponlist
		temp = temp->m_last;
	}
	//reset the temp to enemy weaponlist
	temp = enemy.lasers;
	//Go through the list
	while(temp != NULL)
	{
		//Test to see if the laser and player are active and if the laser is hitting the player
		if(temp->GetActive() && person.m_your_ship->GetActive() && person.m_restart_shield == 0)
		{
			if(test_collision(person.m_your_ship->GetPosition_x(), person.m_your_ship->GetPosition_y(), 16, temp->GetPosition_x(), temp->GetPosition_y()))
			{
				//If they hit deactivate the player sprite and the enemy laser, p
				person.m_your_ship->SetActive(false);
				person.m_your_ship->SetExplosion(true);
				//play sound and set explosion image
				temp->SetActive(false);
				Mix_PlayChannel( -1, blast, 0 );
			}
		}
		//move along the list
		temp = temp->m_last;
	}

	//Test if the players photon is active and if it has hit an enemy ship
	if(person.m_your_ship->photons.GetActive() && enemy.GetActive())
	{
		if(test_collision(person.m_your_ship->photons.GetPosition_x(), person.m_your_ship->photons.GetPosition_y(), size+8, enemy.GetPosition_x(), enemy.GetPosition_y()))
		{
			//If it hits a ship deactivate the photon and the enemy ship, 
			person.m_your_ship->photons.SetActive(false);
			enemy.SetActive(false);
			//set expolision and increase the score 
			enemy.SetExplosion(true);
			person.m_score = person.m_score + 3;
			//and test to see if the photons blast hits other ships, and play music
			blast_radius(person.m_your_ship->photons.GetPosition_x(), person.m_your_ship->photons.GetPosition_y(), person.m_your_ship->photons.m_blast_radius);
			Mix_PlayChannel( -1, blast, 0 );
		}
	}
}

//this returns true if two point are r distance close to each other
bool test_collision(double x, double y, double r, double px , double py)
{
	//Set diameter
	double dr2 = r*r;
	double dist;
	//calculate the distance between the two points
	dist = (px-x)*(px-x) + (py-y)*(py-y);
	//If teh distance is less then the diameter return true
	if(dist < dr2)
	{
		return true;
	}
	//else return false
	else 
		return false;
}

//This takes two attack waves, tests if they are active and if so returns true if they are overlapping
bool over_lap_test( Attack_Wave &aWave, Attack_Wave &bWave)
{
	//Testif waves are active
	if(!aWave.test_active() && !bWave.test_active())
	{
		//Take the centre position of each wave and if the difference is less then the width and height (depending on the number of ships in the wave) its overlapping
		if(aWave.Wave_Positionx() - bWave.Wave_Positionx() < (aWave.m_number_ships/2 + bWave.m_number_ships/2)*50 && aWave.Wave_Positionx() - bWave.Wave_Positionx() > -(aWave.m_number_ships/2 + bWave.m_number_ships/2)*50)
		{
			if(aWave.Wave_Positiony() - bWave.Wave_Positiony() < 50 && aWave.Wave_Positiony() - bWave.Wave_Positiony() > -50)
			{
				return true;
			}
		}
	}

	return false;
}

//This represents the effects of a photon blast, go thorugh every enemy ship
//if its within a certain distance of the photon its deactivated and explosive image set, and score increased.
void blast_radius(double pos_x, double pos_y, int radius)
{
	//Go through the waves
	for(int i = 0; i < m_size; i++)
	{
		//create a temp pointer to spritelist
		Spritelist *temp = Klingons[i]->enemies;
		//Go through the list
		while(temp != NULL)
		{
			//If active
			if(temp->GetActive())			
			{
				//Test collision
				if(test_collision(pos_x, pos_y, radius, temp->GetPosition_x(), temp->GetPosition_y()))				
				{
					//increase score and deactivate sprites
					Defiant->m_score = Defiant->m_score + 3;
					temp->SetActive(false);
					temp->SetExplosion(true);
				}
			}
			//Move along the list
			temp= temp->m_last;
		}
	}
	//Test the boss
	if(Badguy->boss_ship->GetActive())
	{
		Defiant->m_score = Defiant->m_score + 3;
		Badguy->boss_ship->SetActive(false);
		Badguy->boss_ship->SetExplosion(true);
	}
}

//This test to see if Supplies has hit the players sprite
void test_supplies()
{
	//If player and supplies are active
	if(supplies->GetActive() && Defiant->m_your_ship->m_active)
	{
		//If both are close enough to each other
		if(test_collision(supplies->GetPosition_x(), supplies->GetPosition_y(), 24, Defiant->m_your_ship->GetPosition_x() , Defiant->m_your_ship->GetPosition_y()))
		{
			//If its true(Lives) add a life to player
			if(supplies->GetType())
			{
				Defiant->rechargeShields();
				Defiant->m_lives++;
				supplies->SetActive(false);
			}

			//If its false(ammo) add a torpedeo to the players sprite
			if(!supplies->GetType())
			{
				Defiant->rechargeShields();
				Defiant->m_your_ship->m_torpedoes++;
				supplies->SetActive(false);
			}
		}
	}			
}

//This tests if the players name is a cheat
void cheats()
{
	//Set the first
	string test = "captain 057A4EF6";

	//If it matchs the first
	if(name == test)
	{
		//Add lives when the player goes below 3
		if(Defiant->m_lives < 3)
			Defiant->m_lives++;
	}

	//Set the second
	test = "captain 38F34AB9";

	//If it matchs the second
	if(name == test)
	{
		//Add torpedeos when the player goes below 3
		if(Defiant->m_your_ship->m_torpedoes < 3)
			Defiant->m_your_ship->m_torpedoes++;
	}

	//Set the third
	test = "captain 4C65DF74";

	//If it matchs the third
	if(name == test)
	{
		//Create a temp pointing to the last laser
		Weaponlist *temp = Defiant->m_your_ship->lasers;
		if(temp != NULL)
		{
			//Load the new image of fish. From the Assignment Hand out:
			// "An ability to fire multiple missiles (or bullets/rockets/lasers/FISH) at targets in the game"
			temp->SetImage("C:\\Star Trek\\content\\images\\fish.gif");
		}
	}
}
//This tests if more ships should attack
void renew_attack()
{
	//Go through a certain number of the enemy waves based on the attack_delay counter
	for(int i = 0; i < attack_delay/1000; i++)
	{
		//Create a random number of ships
		int number = rand()%4+2;
		//Test is a wave isn't active
		if(Klingons[i]->test_active())
		{
			//If so delete it and call a new one depending on what type should be called
			delete Klingons[i];
			if(counter == 1)
			{
				Klingons[i] = new Attack_Wave(screenWidth, screenHeight, number);
			}
			if(counter == 2)
			{
				Klingons[i] = new Attack_Wave_III(screenWidth, screenHeight, number);
			}
			if(counter == 3)
			{
				Klingons[i] = new Attack_Wave_II(screenWidth, screenHeight, number);
			}
			//To test if a new wave overlaps with an old wave.     
			int j = 0;
			//While j is less then the size
			while( j< m_size)
			{
				if(i==j) //Just add to j
				{
					j++;
				}
				else
				{//Test the j-th wave if it overlaps set j to zero and call constructor again
					if(over_lap_test(*Klingons[i], *Klingons[j]))
					{
						//call the constructor with a random number of ships between 2 and 6
						delete Klingons[i];
						if(counter == 1)
						{
							Klingons[i] = new Attack_Wave(screenWidth, screenHeight, number);
						}
						if(counter == 2)
						{
							Klingons[i] = new Attack_Wave_III(screenWidth, screenHeight, number);
						}
						if(counter == 3)
						{
							Klingons[i] = new Attack_Wave(screenWidth, screenHeight, number);
						}
						j =0;
					}
					else //if no overlap add to j
					{
						j++;
					}
				}
			}
		}
	}
}
	
//This tests if all the waves are deactive
bool test_all_waves()
{
	int counter = 0;
	//test each wave
	for(int i = 0; i < m_size; i ++)
	{
		//if deactive add to counter
		if(Klingons[i]->test_active())
		{
			counter++;
		}
	}
	//if they are all deactive return true
	if(counter == m_size)
	{
		return true;
	}
	else 
		return false;

}
//This controls level timing
void leveltiming()
{
	
	//After a certain number of times set attack to false and increase counter
	if(frame == 5* m_size *1000)
	{
		attack = false;
		counter++;
	}
	//After a certain number of times set attack to false and increase counter
	if(frame == 10* m_size *1000)
	{
		attack = false;
		counter++;
	}
	//After a certain time set attack to false
	if(frame == 15* m_size *1000)
	{
		attack = false;
	}

	//After a long time and when there are no enemy ships add MORE
	if(frame >= 15* m_size *1000 && test_all_waves())
	{
		//reset frame back to the start
		frame = 800;
		//reset the counter and attack_delay
		counter = 1;
		attack_delay = 500;
		//Delete the attack_waves
		for(int i = 0; i < m_size; i++)
		{
			delete Klingons[i];
		}
		//if size is less then the max
		if(m_size < max_size)
		{
			//Increase the number of attack waves
			m_size++;
		}
		else
			game_Won = true;

		//Then point to the base class again
		for(int i = 0; i < m_size; i++)
		{
			Klingons[i] = new Attack_Wave;
		}
		//renew the attack
		attack = true;
		attack_delay = 0;
	}

	//If attack is stopped test if the remaining ships are gone of the screen
	if(!attack && test_all_waves())
	{
		//Call a different class depending on the counter
		if(counter == 2)
		{
			//If so delete the base class
			for(int i = 0; i < m_size; i++)
			{
				delete Klingons[i];
			}

			//Then point to the derived class
			for(int i = 0; i < m_size; i++)
			{
				Klingons[i] = new Attack_Wave_III;
			}
			//renew the attack
			attack = true;
			attack_delay = 0;
		}

		if(counter == 3)
		{
			//If so delete the base class
			for(int i = 0; i < m_size; i++)
			{
				delete Klingons[i];
			}

			//Then point to the derived class
			for(int i = 0; i < m_size; i++)
			{
				Klingons[i] = new Attack_Wave_II;
			}
			//renew the attack
			attack = true;
			attack_delay = 0;
		}
	}
}
//Loads the starting image and blits it to the screen
void start_screen(SDL_Rect rect)
{
	SDL_Surface *image;
	image = IMG_Load("C:\\Star Trek\\content\\images\\title screen.GIF");

	// Draw the text to the screen
	// First render the text into a new surface (not on screen)
	SDL_Color col = {255, 0, 0, 0}; // white

	// Draw the text
	SDL_Surface *text=TTF_RenderText_Blended(font, capt, col);

	// if set to 0 the BlitSurface uses the width and height of the surface
	rect.w = rect.h = 0; 
	rect.x = 135;
	rect.y = 75;	

	//Draw image to screen
	SDL_BlitSurface(image, 0, surf, 0);
	
	// Display the Players name to the screen
	SDL_BlitSurface(text, 0, surf, &rect);	

	//Free the image
	SDL_FreeSurface(image);

	// Free the surface used for the text once we're done drawing it.
	SDL_FreeSurface(text);
}

//Loads the end image and blits it to the screen
void end_screen(SDL_Rect rect)
{
	SDL_Surface *image;
	image = IMG_Load("C:\\Star Trek\\content\\images\\end screen.GIF");

	// Draw the text to the screen
	// First render the text into a new surface (not on screen)
	SDL_Color col = {255, 0, 0, 0}; // white

	// Draw the text
	SDL_Surface *text=TTF_RenderText_Blended(font, capt, col);

	// if set to 0 the BlitSurface uses the width and height of the surface
	rect.w = rect.h = 0; 
	rect.x = 140;
	rect.y = 85;	

	//Draw image to screen
	SDL_BlitSurface(image, 0, surf, 0);
	
	// Display the Players name to the screen
	SDL_BlitSurface(text, 0, surf, &rect);	

	//Dipslay the score
	Defiant->Display_Final_Score(surf, 280, 182);

	//Free the image
	SDL_FreeSurface(image);

	// Free the surface used for the text once we're done drawing it.
	SDL_FreeSurface(text);
}
//Displays the winning screen
void winning_screen(SDL_Rect rect)
{
	SDL_Surface *image;
	image = IMG_Load("C:\\Star Trek\\content\\images\\winning screen.GIF");

	// Draw the text to the screen
	// First render the text into a new surface (not on screen)
	SDL_Color col = {255, 0, 0, 0}; // white

	// Draw the text
	SDL_Surface *text=TTF_RenderText_Blended(font, capt, col);

	// if set to 0 the BlitSurface uses the width and height of the surface
	rect.w = rect.h = 0; 
	rect.x = 140;
	rect.y = 85;	

	//Draw image to screen
	SDL_BlitSurface(image, 0, surf, 0);
	
	// Display the Players name to the screen
	SDL_BlitSurface(text, 0, surf, &rect);	

	//Dipslay the score
	Defiant->Display_Final_Score(surf, 280, 182);

	//Free the image
	SDL_FreeSurface(image);

	// Free the surface used for the text once we're done drawing it.
	SDL_FreeSurface(text);
}

//This controls the various start image playing images and end image
void Screen_Order()
{
	
	// Clear the screen	before doing anything
	SDL_Rect rect = {0, 0, screenWidth, screenHeight}; 
	SDL_FillRect(surf, &rect, 0);  

	//Increase frame till its arbitrarly high
	//Just in case some decides to play for a long long time
	if(frame <= 4000000000)
		frame++;
	
	//If frame is low display the start screen
	if(frame < 500)
	{
		start_screen(rect);
	}

	//If frame is high and the game isn't over call render which sorts all the game functions/displaying/updating
	if(frame > 500 && !Defiant->Game_Over)
	{
		render();
	}

	//If frame is between a certain period before the first attack display a message
	if(frame > 800 && frame < 800 + 300*speed)
	{
		//Set a temp to hold "level"
		string temp = "level ";
		//Create an array of chars
		char *level = new char[8];
		//"safely" convert an int to char
		SDL_itoa(m_size -2, level, 10);
		
		//Place that number near the end
		level[6] = level[0];
		//Fill in the word "level"
		for(int i = 0; i < 6; i++)
		{
			level[i] = temp[i];
		}
		//Null terminate it
		level[7] = 0;

		// Draw the text to the screen
		// First render the text into a new surface (not on screen)
		SDL_Color col = {255, 255, 255, 0}; // white

		// Draw the text
		SDL_Surface *text=TTF_RenderText_Blended(font,"Watch out more Klingons are attacking!", col);

		// if set to 0 the BlitSurface uses the width and height of the surface
		rect.w = rect.h = 0; 
		rect.x = (screenWidth - text->w)/2; // centre the text
		rect.y = (screenHeight - text->h)/2;

		// Draw the text
		SDL_Surface *text2=TTF_RenderText_Blended(font, level, col);
		//Create a second rect
		SDL_Rect rect2;

		// if set to 0 the BlitSurface uses the width and height of the surface
		rect2.w = rect2.h = 0; 
		rect2.x = (screenWidth - text2->w)/2; // centre the text
		rect2.y = (screenHeight - text2->h)/2 +  TTF_FontHeight(font); //Below the above text

		// Draw the text to the screen centered.
		SDL_BlitSurface(text, 0, surf, &rect);
		SDL_BlitSurface(text2, 0, surf, &rect2);

		// Free the surface used for the text once we're done drawing it.
		SDL_FreeSurface(text);
		SDL_FreeSurface(text2);
		delete[] level;
	}
	
	//If the game is over display the end screen.
	if(Defiant->Game_Over == true)
	{
		end_screen(rect);
	}
	//If the game is won display game won screen
	if(game_Won)
	{
		winning_screen(rect);
	}
	//If music isn't playing
	if(!Mix_PlayingMusic())
    {
      // then start playing it.
      Mix_PlayMusic(music, 0);
    }

	cheats();
}