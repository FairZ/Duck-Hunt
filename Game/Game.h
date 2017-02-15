//header file containing definitions and function prototypes used by the Game function

#ifndef _GAME_H_			//redefine guard prevents the header file from being compiled multiple times
#define _GAME_H_

#include "AllegroInit.h"	//included to allow allegro functions
#include "Player.h"			//included to allow interaction with the player object
#include "Animals.h"		//included to allow interaction with the animal objects and functions
#include "Medals.h"			//included to allow the running of the medal (end) screen

#define GAME_PLAY 1			//definitions to help easily understand game states
#define GAME_END 0

void Game();				//functions to be used while running the game
void FireCheck();
void DeerSpawn();
void DuckSpawn();
void GameEnd();

#endif