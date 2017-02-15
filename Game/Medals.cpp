//source file containing the code that is run when the medals function is run

#include "Medals.h" //includes the header file needed for the medal function

void Medals(int _score)
{
	BITMAP* medals = load_bitmap("Medals.bmp",0);				//create allegro pointers from files
	BITMAP* medalSprites = load_bitmap("MedalSprites.bmp",0);
	FONT* chalk = load_bitmap_font("ChalkFont.bmp",0,0);

	
	blit(medals,screen,0,0,0,0,1600,900);						//copy a background to the screen
	textprintf_ex(screen, chalk, 1000,200,makecol(255,255,255),-1,"%d", _score);	//print the score to the appropriate area of the screen

	if (_score < 1000)											//if you scored less than 1000 points display the appropriate message 
	{
		textout_ex(screen, chalk, "you got no medal,", 50, 410, makecol(255,255,255), -1);
		textout_ex(screen, chalk, "better luck next time.", 50, 490, makecol(255,255,255), -1);
	}
	else if (_score < 1500)										//if you scored less than 1500 points display the appropriate message
	{
		textout_ex(screen, chalk, "you got a bronze medal!", 50, 410, makecol(255,255,255), -1);
		textout_ex(screen, chalk, "good effort!", 50, 490, makecol(255,255,255), -1);
		masked_blit(medalSprites,screen,0,0,1230,150,200,128);
	}
	else if (_score < 2000)										//if you scored less than 2000 points display the appropriate message
	{
		textout_ex(screen, chalk, "you got a silver medal!", 50, 410, makecol(255,255,255), -1);
		textout_ex(screen, chalk, "Well done!!", 50, 490, makecol(255,255,255), -1);
		masked_blit(medalSprites,screen,200,0,1230,150,200,128);
	}
	else														//if you scored 2000 points or more display the appropriate message
	{
		textout_ex(screen, chalk, "you got a gold medal!", 50, 410, makecol(255,255,255), -1);
		textout_ex(screen, chalk, "Amazing!!!", 50, 490, makecol(255,255,255), -1);
		masked_blit(medalSprites,screen,400,0,1230,150,200,128);
	}



	while(!key[KEY_ESC]){}										//wait for the user to press esc to return to the main menu

	destroy_bitmap(medals);										//delete allegro pointers
	destroy_bitmap(medalSprites);
	destroy_font(chalk);

}
