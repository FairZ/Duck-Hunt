//source file containing the code for the menu and all 3 button classes

#include "Menu.h" //include the needed headers for the functions run and defined in this file
#include "Game.h"

void Menu()			//function to display a simple menu with two buttons
{
	//creates a font pointer and then displays a loading message onto the screen while the allegro pointers, button objects and other variables are being created
	FONT *chalk = load_bitmap_font("ChalkFont.bmp",NULL,NULL);
	textout_centre_ex(screen,chalk,"loading...",SCREEN_W/2,SCREEN_H/2,makecol(255,255,255),-1);

	int menuController = MENU_ON;						//setting of default variable values, creation of allegro pointers and button objects
	BITMAP *buffer = create_bitmap(1600,900);			
	BITMAP *target = load_bitmap("Target.bmp",0);
	BITMAP *background = load_bitmap("Menu.bmp",0);
	ExitButton exit;
	PlayButton play;
	SAMPLE *backing = load_sample("BackingMusic.wav");

	play_sample(backing,125,0,1000,1);					//begin the backing music and loop it

	while(menuController == MENU_ON)					//while the menu is running loop through this game loop
	{
		blit(background,buffer,0,0,0,0,1600,900);		//copy the menu background onto the buffer
		
		masked_blit(target, buffer,0,0,mouse_x-128,mouse_y-128,256,256);	//draw a reticule at the mouse position
		
		if (mouse_b & 1)									//if the mouse has been clicked check if the exit button has been clicked and adjust the menu controller accordingly
		{
			menuController = exit.ButtonClick();
		}
		if ((mouse_b & 1)&&(menuController != MENU_END))	//if the exit button wasn't clicked check if the play button was clicked
		{
			menuController = play.ButtonClick();			//if it has run, run the game and adjust the menu controller accordingly
		}
		blit(buffer,screen,0,0,0,0,1600,900);				//copy the buffer to the screen
	}
	destroy_bitmap(buffer);				//destroy allegro pointers
	destroy_bitmap(target);
	destroy_bitmap(background);
	destroy_font(chalk);
	destroy_sample(backing);
}

int Button::GetWidth()						// anumber of get and set functions for the button class, each returns or alters its corresponding variable
{
	return m_width;
}

int Button::GetHeight()
{
	return m_height;
}

int Button::GetDestinationX()
{
	return m_destinationX;
}

int Button::GetDestinationY()
{
	return m_destinationY;
}

void Button::SetDestinationX(int _x)
{
	m_destinationX = _x;
}

void Button::SetDestinationY(int _y)
{
	m_destinationY = _y;
}


Button::Button()				//constructor sets default values of the button objects
{
	m_height = 270;
	m_width = 860;
}

int Button::ButtonClick(){return MENU_ON;}	//virtual function that won't be used


ExitButton::ExitButton():Button()	//constructor sets default values for exit button object
{
	SetDestinationX(670);
	SetDestinationY(520);
}

PlayButton::PlayButton():Button()	//constructor sets default values for play button object
{
	SetDestinationX(670);
	SetDestinationY(200);
}

int ExitButton::ButtonClick()		//checks the position of the mouse when the mouse button is clicked, if it is within the button the return value is set appropriately
{
	int returnValue = MENU_ON;
	if((mouse_y > GetDestinationY())&&(mouse_y < GetDestinationY()+GetWidth())&&(mouse_x > GetDestinationX())&&(mouse_x < GetDestinationX()+GetWidth()))
	{
		returnValue = MENU_END;
	}

	return returnValue;
}

int PlayButton::ButtonClick()	//checks the position of the mouse when the mouse button is clicked, if it is within the button the screen is cleared and the game is run
{
	if((mouse_y > GetDestinationY())&&(mouse_y < GetDestinationY()+GetWidth())&&(mouse_x > GetDestinationX())&&(mouse_x < GetDestinationX()+GetWidth()))
	{
		clear_to_color(screen, makecol(0,0,0));
		Game();
	}
	return MENU_ON;
}

