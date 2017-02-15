//Header file containing the player class

#ifndef _PLAYER_H_			//redefine guard prevents the header file from being compiled multiple times
#define _PLAYER_H_

#include "AllegroInit.h"	//included to allow allegro functions

class Player				//class contains all neccessary variables and methods
{
private:					//variables are set as private in order to stop them from being edited by outside sources
	int m_score;
	bool m_reloading;
	int m_reloadCount;
	BITMAP *m_shotgun;
	SAMPLE *m_reloadSound;
public:						//methods set as public to allow them to be run by the main program
	Player();				//constructor is used to give default values to the variables
	~Player();				//deconstructor is used to delete allegro pointers when the object is destroyed
	void AddToScore(int _value);	//getters and setters use to edit variables from outside the object
	int GetScore();
	bool GetReloading();
	void SetReloading(bool _reloading);
	void UpdateGun(BITMAP* _buffer);	//parameters passed by reference allow editing of variables
	void Reload(int &clip);			
};

#endif