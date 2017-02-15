//source file containing allegro initialization

#include "AllegroInit.h"	//includes the header file for the functions used in this file

int AllegroInit()			//this function is run to initialize allegro and its components for later use
{
	int returnValue = 0;	//value that will be returned
	int graphicsMode = 0;	//variable that holds the state of the graphics mode (working/broken)
	int soundCheck = 0;		//variable that holds the state of the sound initialization (working/broken)
	
	if (allegro_init() != 0)	//runs the allegro initialization fuciton to include allegro in the program
	{
		returnValue = -1;		//if allegro failed to initialize returnValue is set accordingly
	}
	else						//if allegro has initilized continue to set up allegro
	{
		set_color_depth(32);	//set the colour depth to 32

		graphicsMode = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1600, 900, 0, 0);		//set the values of graphics mode and sound check according to if either initilizations worked
		soundCheck = install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);

		if (graphicsMode !=0)														//if the graphics did't set up properly tell the user in a pop-up and set the return value accordingly
		{
			returnValue = -2;
			allegro_message("Unable to initialize graphics mode!",allegro_error);
		}
		else if (soundCheck !=0)													//if the audio did't set up properly tell the user in a pop-up and set the return value accordingly
		{
			returnValue = -3;
			allegro_message("unable to initialize sound",allegro_error);
		}
		else																		//if everything worked finish installing allegro and set return value accordingly
		{
			install_keyboard();
			install_mouse();
			install_timer();
			returnValue = 0;													
		}
	}
	
	return returnValue;				//return the final result
}

void AllegroDeInit()				//function to remove used up memory to avoid memory leaks
{
	remove_sound();					
	clear_keybuf();
}
