//source file containing the game part of the program (where the player has to shoot ducks)

#include "Game.h"	//includes the header that contains all functions and classes used in this file

//a number of global variables are set up here in order to be able to use allegro timers
bool fireControl;		//switches states depending on if the gun is being fired
bool reloadControl;		//switches states depending on if the gun is reloading
bool soundPlayed;		//switches states depending on if reaction sounds are being played
float fireX;			//stores location of mouse when shot was fired
float fireY;
int clip;				//stores number of bullets in the magazine
int duckCount;			//stores the number of ducks that have been spawned
Deer* deer;				//pointer to a deer object
Duck* ducks[25];		//array of pointers to duck objects
int gameController;		//switches states depending on if the game is still running

void Game()				//function containing the game loop and a number of allegro timers
{
	FONT *chalk = load_bitmap_font("ChalkFont.bmp",NULL,NULL);									//creates a font pointer and then displays a loading message onto the screen while
	textout_centre_ex(screen,chalk,"loading...",SCREEN_W/2,SCREEN_H/2,makecol(255,255,255),-1);	//the global variables are being reset and the other pointers are being created

	fireControl = false;			//resetting of global variables to allow the game to be played multiple times per session
	reloadControl = false;
	soundPlayed = false;
	fireX = 0.0f;
	fireY = 0.0f;
	clip = 5;
	duckCount = 0;
	gameController = GAME_PLAY;
	bool ending = false;

	BITMAP *buffer = create_bitmap(1600,900);				//creation of allegro pointers from files in the project folder
	BITMAP *target = load_bitmap("Target.bmp",0);
	BITMAP *shot = load_bitmap("Shot.bmp",0);
	BITMAP *background = load_bitmap("background.bmp",0);
	BITMAP *HUD = load_bitmap("HUD.bmp",0);
	BITMAP *animals = load_bitmap("Animals.bmp",0);
	BITMAP *ready = load_bitmap("Ready.bmp",0);
	SAMPLE *bang = load_sample("ShotgunBlast.wav");
	SAMPLE *roar = load_sample("Roar.wav");
	SAMPLE *quack = load_sample("Quack.wav"); 

	blit(ready,screen,0,0,0,0,1600,900);					//displays an image on the screen to allow the player to start the game when ready

	while(!key[KEY_SPACE]){}								//waits for the player to press space to start the game

	Player player;											//creation of initial objects
	deer = new Deer;
	ducks[0] = new Duck;

	srand(time(NULL));										//sets random seed

	install_int(FireCheck,16);								//start of allegro timers
	install_int(DeerSpawn,(rand() % 5000) + 5000);
	install_int(DuckSpawn,(rand() % 2000) + 1000);

	while (gameController == GAME_PLAY)						//runs the game loop over and over while the game controller is in the right state
	{

		blit(background,buffer,0,0,0,-100,1600,900);		//copies the background onto the buffer so that it is the lowest bitmap

		if (deer != NULL)									//if there is a deer present draw the deer in the correct postion and animation state then update its movement and animation
		{
		masked_stretch_blit(animals, buffer, deer->GetSpriteX(), deer->GetSpriteY(),deer->GetXWidth(),deer->GetYHeight(),deer->GetXPos(),deer->GetYPos(),deer->GetXWidth() + 50,deer->GetYHeight() +50);
		deer->UpdateMovement();
		deer->UpdateAnimation();
		}

		if (duckCount < 25 && duckCount != 0)				//if there are ducks and it is not the first duck then draw all the ducks and update their animation and movement
		{
			for(int i = 0; i < duckCount; i++)
			{
				masked_blit(animals, buffer, ducks[i]->GetSpriteX(), ducks[i]->GetSpriteY(),ducks[i]->GetXPos(),ducks[i]->GetYPos(),ducks[i]->GetXWidth(),ducks[i]->GetYHeight());
				ducks[i]->UpdateMovement();
				ducks[i]->UpdateAnimation();
			}
		}
		else if (duckCount == 0)							//draw the first duck and update it's movement and animation
		{
			masked_blit(animals, buffer, ducks[0]->GetSpriteX(), ducks[0]->GetSpriteY(),ducks[0]->GetXPos(),ducks[0]->GetYPos(),ducks[0]->GetXWidth(),ducks[0]->GetYHeight());
			ducks[0]->UpdateMovement();
			ducks[0]->UpdateAnimation();
		}

		masked_blit(target, buffer,0,0,mouse_x-128,mouse_y-128,256,256);	//draw a reticule at the mouse position so that it is above the animals but below blasts and the HUD

		if(fireControl == true)								//if a shot has been fired run more if statements and draw a blast on the screen where the mouse was clicked
		{

			if (soundPlayed == false)						//on the first loop through play a shot noise, check if any animals have been hit play an appropriate sound and adjust score
			{
				play_sample(bang,125,0,1000,0);
				soundPlayed = true;

				if (deer != NULL)
				{
					if (deer->HitCheck())
					{
						player.AddToScore(-200);
						play_sample(roar,150,0,1000,0);
					}
				}
				if (duckCount < 25 && duckCount!= 0)
				{
					for(int i = 0; i < duckCount; i++)
					{
						if(ducks[i]->HitCheck())
						{
							player.AddToScore(100);
							play_sample(quack,150,0,1000,0);
						}
					}
				}
				else if (duckCount == 0)
				{
					if(ducks[0]->HitCheck())
					{
						player.AddToScore(100);
					}
				}
			}
			masked_blit(shot, buffer,0,0,fireX,fireY,256,256);
		}

		masked_blit(HUD, buffer,0,0,0,0,1600,900);				//draw the HUD backing onto the screen so that only relevant information and the player object is above it

		textprintf_ex(buffer,chalk,70,765,makecol(255,255,255),-1,"Score: %d",player.GetScore());		//write the score and number of shells remaining on top of the HUD
		textprintf_ex(buffer,chalk,70,830,makecol(255,255,255),-1,"Shells: %d / 5",clip);

		if(((key[KEY_R])&&(clip < 5)&&(fireControl==false)) || (player.GetReloading() == true))
		{														//if R is pressed, the gun is not firing and  the clip isn't full or the gun is reloading run the reload function
			player.Reload(clip);								//and change the reload control value
			reloadControl = player.GetReloading();
		}
		else if (player.GetReloading() == false)				//otherwise if they aren't reloading draw the gun on top of the HUD according to the update gun function
		{
			player.UpdateGun(buffer);
		}

		blit(buffer,screen,0,0,0,0,1600,900);					//copy the buffer to the screen

		if(deer != NULL)										//if there is a deer off the screen delete it and return its value to NULL
		{
			if (deer->GetXPos() < -128)
			{
				delete deer;
				deer = NULL;
			}
		}

		_sleep(16);												//stop the game for 16 ms to stop the game from running too quickly and having a noticeably fluctuating framerate

		if ((duckCount == 20)&&(ending == false))				//if there have been enough ducks spawned and it hasn't already been started, start the end game timer
		{
			install_int(GameEnd, 15000);
			ending = true;
			gameController = GAME_END;
		}
	}

	Medals(player.GetScore());									//once the game has ended display the medal screen with information based on your score

	for (int j = 0 ; j <= 24; j++)								//delete all the duck pointers and return their values to NULL
	{
		delete ducks[j];
		ducks[j] = NULL;
	}

	destroy_bitmap(buffer);										//destroy all the allegro pointers
	destroy_bitmap(target);
	destroy_bitmap(shot);
	destroy_bitmap(background);
	destroy_bitmap(HUD);
	destroy_bitmap(animals);
	destroy_sample(bang);
	destroy_font(chalk);
}


void FireCheck()												//when triggered do a number of firing checks and react appropriately
{
	if ((mouse_b & 1) && (fireControl == false) && (clip > 0)&&(reloadControl == false))	//if the left mouse has been clicked, the gun isn't already firing, there are bullets left
	{																						//and the gun isn't reloading change the firecheck rate, set the shot position, remove a bullet
		install_int(FireCheck,500);															//and switch firecontrol
		fireX = mouse_x-128;
		fireY = mouse_y-128;
		clip--;
		fireControl = true;
	}
	else if (fireControl == true)															//half a second after firing reset the timer to 16 ms and reset the appropriate variables
	{
		fireControl = false;
		soundPlayed = false;
		install_int(FireCheck,16);
	}
}

void DeerSpawn()										//controls the spawning of a deer when triggered by the timer
{
	if (duckCount < 24 && deer == NULL)					//if there are still ducks and there is no current deer create a new deer and reset the deer spawn rate
	{
		deer = new Deer;
		install_int(DeerSpawn, (rand() % 5000) + 5000);
	}
	else if (deer != NULL)								//if there is already a deer wait for it to be deleted
	{
		install_int(DeerSpawn,50);
	}
	else if(duckCount == 24)							//if there are no ducks left stop spawning deer
	{
		remove_int(DeerSpawn);
	}


}

	
void DuckSpawn()											//controls the spawning of ducks when triggered by the timer
{
	if (duckCount < 25)										//if there have yet to be 25 ducks spawn a new duck, increase the counter and reset the spawn timer
	{
		duckCount++;
		ducks[duckCount] = new Duck;
		install_int(DuckSpawn, (rand() % 2000) + 1000);
	}
	else if (duckCount >= 25)								//if there have been 25 ducks stop spawning ducks
	{
		remove_int(DuckSpawn);
	}

}

void GameEnd()												//when run the game is ended and it removes it's own timer
{
	remove_int(GameEnd);
	gameController = 0;

}
