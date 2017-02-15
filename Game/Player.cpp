//source file containing the definitions of the player class methods

#include "Player.h" //includes the file needed for the player class prototypes

Player::Player()	//constructor sets up default values
{
	m_shotgun = load_bitmap("ShotgunSprite.bmp",0);
	m_reloadSound = load_sample("ShotgunReload.wav");
	m_score = 0;
	m_reloadCount = 0;
	m_reloading = false;
}

Player::~Player()	//deconstructor deletes the allegro pointers created by the constructor
{
	destroy_bitmap(m_shotgun);
	destroy_sample(m_reloadSound);
}

void Player::AddToScore(int _value)	//adds parameter input to the current score
{
	m_score += _value;
}

int Player::GetScore()	//returns the score value
{
	return m_score;
}

void Player::UpdateGun(BITMAP* _buffer)	//draws the gun in a position based on the mouse position inorder to give the illusion of movement
{
	if (mouse_x < 533)	//if the mouse is less than a third of the way accross the screen draw the first sprite
	{
		masked_blit(m_shotgun,_buffer,0,0,(775 + mouse_x / 75),(550 + mouse_y / 75),670,370);
	}
	else if (mouse_x < 1066) //if the mouse is less than 2 thirds of the way accross the screen but more than a third draw the second sprite
	{
		masked_blit(m_shotgun,_buffer,45,390,(870 + mouse_x / 75),(560 + mouse_y / 75),485,390);
	}
	else	//otherwise draw the final sprite
	{
		masked_blit(m_shotgun,_buffer,810,19,(910 + mouse_x / 75),(620 + mouse_y / 75),381,360);
	}
}

bool Player::GetReloading() //returns the value of the reloading variable
{
	return m_reloading;
}

void Player::SetReloading(bool _reloading)	//sets the reloading variable
{
	m_reloading = _reloading;
}


void Player::Reload(int &clip)	//function used for reloading, the number of shells is passed by reference in order to edit it automatically
{
	m_reloading = true;								//sets the reloading variable to true
	m_reloadCount++;								//increases the value of the counter
	
	if((m_reloadCount % 20) == 0)					//if the reload counter is 20 play a reload noise, add a shell and reset the reload counter
	{
		play_sample(m_reloadSound,125,0,1000,0);
		clip++;
		m_reloadCount = 0;
	}
	if (clip == 5)		//if the clip is full stop reloading
	{
		m_reloading = false;
	}

}