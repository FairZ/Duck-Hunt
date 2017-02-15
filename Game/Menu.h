//Header file containing function prototypes and classes used in the running of the main menu

#ifndef _Menu_H_			//redefine guard prevents the header file from being compiled multiple times
#define _Menu_H_

#include "AllegroInit.h"	//allows use of allegro functions

#define MENU_ON 1			//definitions to help to easily understand menu states
#define MENU_END 0

void Menu();				//function used to run the menu


class Button				//base class contains all neccessary variables and methods as well as a virtual function
{
private:					//variables are set as private in order to stop them from being edited by outside sources
	int m_destinationX;	
	int m_destinationY;
	int m_width;
	int m_height;

public:						//methods set as public to allow them to be run by the main program
	Button();				//constructor is used to give default values to the variables
	int GetWidth();			//get and set functions allow the variable to be accessed by the main program
	int GetHeight();
	int GetDestinationX();
	int GetDestinationY();
	void SetDestinationX(int _x);
	void SetDestinationY(int _y);
	virtual int ButtonClick();		//virtual method to allow different functions of the same name in inherited classes
};

class ExitButton: public Button
{
public:
	ExitButton();					//constructor is used to give default values for each object
	int ButtonClick();				//redefined virtual functions too allow seperate functions with the same name
};

class PlayButton: public Button
{
public:
	PlayButton();					//constructor is used to give default values for each object
	int ButtonClick();				//redefined virtual functions too allow seperate functions with the same name
};

#endif