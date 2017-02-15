//source file containing all the definitions of the methods from the animal and inherited classes

#include "Animals.h"								//includes the prototypes and class definitions used in this file

#define DEAD false									//defines keywords to easily understand the animals alive state
#define ALIVE true

Animal::Animal()									//constructor assigns default values to common variable
{
	this->m_animFrame = 1;							//"this->" is used throughout to ensure only the values o each specific object are edited rather than all of the same type of object
	this->m_animCount = 1;
	this->m_spriteX = 0;
}

Duck::Duck():Animal()								//constructor assigns default values for each duck object
{
	srand(time(NULL));								//each time a duck is created the random seed is reset
	this->m_velocityX = 20;							//x velocity determines movement accross the screen
	this->m_velocityY = (rand() % 20) - 10;			//y velocity is set to random to make the ducks move in different directions
	this->m_alive = ALIVE;
	this->m_xPos = -128;
	this->m_yPos = (rand() % 500) + 75;				//set to random to make the ducks come from different heights on the screen
	this->m_xWidth = 128;							//width and height of the sprite, used to determine drawing and hitbox
	this->m_yHeight = 126;
	this->m_score = 100;							//points that are gained for killing a duck
	this->m_spriteY = 0;							//y position of the sprites in the spritesheet
}

Deer::Deer():Animal()								//constructor assigns default values for each deer object
{
	srand(time(NULL));								//each time a deer is created the random seed is reset
	this->m_velocityX = -15;						//x velocity determines movement accross the screen
	this->m_velocityY = 0;							
	this->m_alive = ALIVE;
	this->m_xPos = 1600;
	this->m_yPos = (rand() % 70) + 350;				//set to random to make the deer come from different heights on the screen
	this->m_xWidth = 128;							//width and height of the sprite, used to determine drawing and hitbox
	this->m_yHeight = 172;
	this->m_score = -200;							//points that are gained for killing a duck
	this->m_spriteY = 128;							//y position of the sprites in the spritesheet
}		

bool Animal::GetAlive()								//returns alive value
{
	return this->m_alive;
}

int Animal::GetXPos()								//returns x position value
{
	return this->m_xPos;
}

int Animal::GetYPos()								//returns y position value
{
	return this->m_yPos;
}

int Animal::GetXWidth()								//returns sprite width value
{
	return this->m_xWidth;
}

int Animal::GetYHeight()							//returns sprite height value
{
	return this->m_yHeight;
}

int Animal::GetSpriteX()							//returns sprite x value
{
	return this->m_spriteX;
}

int Animal::GetSpriteY()							//returns sprite y value
{
	return this->m_spriteY;
}

int Animal::GetScore()								//returns score value
{
	return this->m_score;
}

void Animal::UpdateAnimation(){}					//empty virtual methods that will never be called

void Animal::UpdateMovement(){}

bool Animal::HitCheck(){return true;}				//return value was required so a default was added (this function will never be called)

void Duck::UpdateAnimation()						//updates the animation each time it's called
{
	switch (this->m_animFrame)						//changes the sprite sheet position values according to which frame of the animation it is on
	{
	case 1:
		this->m_spriteX = 0;
		this->m_spriteY = 0;
		break;
	case 2:
		this->m_spriteY = 0;
		this->m_spriteX = 128;
		break;
	case 3:
		this->m_spriteY = 0;
		this->m_spriteX = 256;
		break;
	case 4:
		this->m_spriteY = 0;
		this->m_spriteX = 384;
		break;
	}
	if(this->m_alive == ALIVE)						//if the duck is still alive animation counter is increased by 1
	{
	this->m_animCount++;
	}
	if (this->m_animCount % 3 == 0)					//every 3 counts the animation frame is updated according to the number on the counter (up to frame 4)
	{
		this->m_animFrame = this->m_animCount / 3;
	}
	if (this->m_animCount > 12)						//if the counter is over 12 it is reset to 1 so that the frame number cannot be over 4
	{
		this->m_animCount = 1;
	}

}

void Duck::UpdateMovement()							//moves the duck and updates it's movement pattern
{
	this->m_xPos += this->m_velocityX;				//x position increased by x velocity
	this->m_yPos += this->m_velocityY;				//y position increased by y velocity

	if (this->m_alive == DEAD)						//if the duck is dead, increase the y velocity by 3 each iteration in order to simulate gravity
	{
		this->m_velocityY += 3;
	}

	if ((this->m_yPos > 520)&&(m_alive == ALIVE))	//if the duck is alive and hits the bottom of the viewing area make it fly upwards
	{
		this->m_velocityY = -10;
	}
	else if ((this->m_yPos < 80)&&(m_alive == ALIVE)) //if the duck is alive and hits the top of the viewing area make it fly downwards
	{
		this->m_velocityY = 10;
	}
}

bool Duck::HitCheck()								//checks if the click that triggered the function has occured over the duck and returns an appropriate value
{
	bool retVal = false;							//creates a return value with a default false value
	if ((mouse_x > this->m_xPos)&&(mouse_x < (this->m_xPos + this->m_xWidth))&&(mouse_y > this->m_yPos + 10)&& (mouse_y < (this->m_yPos + this->m_yHeight)))
	{												//if the mouse is inside the duck when the click happens the duck becoms dead and the function returns true
		this->m_alive = DEAD;
		retVal = true;
	}
	return retVal;
}



void Deer::UpdateAnimation()						//updates the animation each time it's called
{
	switch (this->m_animFrame)						//changes the sprite sheet position values according to which frame of the animation it is on
	{
	case 1:
		this->m_spriteX = 0;
		this->m_spriteY = 128;
		break;
	case 2:
		this->m_spriteY = 128;
		this->m_spriteX = 128;
		break;
	case 3:
		this->m_spriteY = 128;
		this->m_spriteX = 256;
		break;
	case 4:
		this->m_spriteY = 128;
		this->m_spriteX = 384;
		break;
	case 5:
		this->m_spriteY = 128;
		this->m_spriteX = 512;
		break;
	case 6:
		this->m_spriteY = 128;
		this->m_spriteX = 640;
		break;
	case 7:
		this->m_spriteY = 128;
		this->m_spriteX = 768;
		break;
	}
	this->m_animCount++;							//if the deer is still alive animation counter is increased by 1
	if (this->m_animCount % 3 == 0)					//every 3 counts the animation frame is updated according to the number on the counter (up to frame 7)
	{
		this->m_animFrame = this->m_animCount / 3;
	}
	if (this->m_animCount > 21)						//if the counter is over 21 it is reset to 1 so that the frame number cannot be over 7
	{
		this->m_animCount = 1;
	}

}

void Deer::UpdateMovement()							//moves the deer and updates it's movement pattern
{
	if (this->m_alive == DEAD)						//if the deer has been hit make it increase speed in order to look like it is running away
	{
		this->m_velocityX += -3;
	}

	this->m_xPos += this->m_velocityX;				//move the deer by it x velocity (it does not move up or down)
}

bool Deer::HitCheck()								//checks if the click that triggered the function has occured over the deer and returns an appropriate value
{
	bool retVal = false;							//creates a return value with a default false value
	if ((mouse_x > this->m_xPos)&&(mouse_x < (this->m_xPos + this->m_xWidth))&&(mouse_y > this->m_yPos + 10)&& (mouse_y < (this->m_yPos + this->m_yHeight)))
	{												//if the mouse is inside the duck when the click happens the deer has been hit and the function returns true
		this->m_alive = DEAD;
		retVal = true;
	}
	return retVal;
}