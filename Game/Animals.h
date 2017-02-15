//Header file containing function prototypes and classes used by the game to create the animal objects

#ifndef _ANIMALS_H_			//redefine guard prevents the header file from being compiled multiple times
#define _ANIMALS_H_

#include "AllegroInit.h"	//included to allow allegro functions
#include <time.h>			//included to give a better random seed

class Animal				//base animal class contains all neccessary variables and methods as well as some virtual functions
{
protected:					//variables are set as protected in order to easily edit them fromthe inherited class' methods
  float m_velocityX;
  float m_velocityY;
  bool m_alive;
  int m_xPos;
  int m_yPos;
  int m_xWidth;
  int m_yHeight;
  int m_spriteX;
  int m_spriteY;
  int m_animFrame;
  int m_score;
  int m_animCount;
public:						//methods set as public to allow them to be run by the main program
  Animal();					//constructor is used to give default values for each object
  bool GetAlive();			//get and set functions allow the variable to be accessed by the main program
  int GetXPos();
  int GetYPos();
  int GetXWidth();
  int GetYHeight();
  int GetSpriteX();
  int GetSpriteY();
  int GetScore();
  void SetAlive(bool _value);
  virtual void UpdateAnimation();	//virtual methods to allow different functions of the same name in inherited classes
  virtual void UpdateMovement();
  virtual bool HitCheck();
};

class Duck: public Animal			//inherited class includes its own constructor and versions of the virtual methods
{
public:
	Duck();							//constructor is used to give default values for each object
	void UpdateMovement();			//redefined virtual functions too allow seperate functions with the same name
	void UpdateAnimation();
	bool HitCheck();
};

class Deer: public Animal			//inherited class includes its own constructor and versions of the virtual methods
{
public:		
	Deer();							//constructor is used to give default values for each object
	void UpdateMovement();			//redefined virtual functions too allow seperate functions with the same name
	void UpdateAnimation();
	bool HitCheck();
};

#endif