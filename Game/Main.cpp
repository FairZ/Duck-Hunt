//source file containing the main function which is run first

#include "AllegroInit.h" //includes headers needed to run functions within the main function
#include "Menu.h"

int main(void)
{
	if (AllegroInit() == 0)	//if the allegro initialization works then run the menu
	{
	Menu();
	}
	AllegroDeInit();		//deinitialize allegro at the game exit
	return 0;				//exit with a default value
}
END_OF_MAIN()				//Macro needed by allegro to find where the main function ends