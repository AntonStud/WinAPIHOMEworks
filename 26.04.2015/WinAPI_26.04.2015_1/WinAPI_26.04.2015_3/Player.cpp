#include "Player.h"


Player::Player() :HEALTH(100), MINDAMAGE(1), HEALTHLIMIT(20), DAMAGETWO(2), DAMAGELIMIT(10)
{
	Init();

	arms.push_back(new Arms("Arm", MINDAMAGE));
	arms.push_back(new Arms("Leg", DAMAGETWO));

	blocks.push_back(new Blocks("Head", DAMAGETWO));
	blocks.push_back(new Blocks("Body", DAMAGETWO));
	blocks.push_back(new Blocks("Leg", DAMAGETWO));

	srand(time(NULL));

}

//--------------------------------------------------------------------------
Player::~Player()
{
}
//--------------------------------------------------------------------------

int Player::ChooseBlock()
{
	return rand() % blocks.size();
}
//--------------------------------------------------------------------------
int Player::ChooseDirect()
{
	return rand() % blocks.size();
}
//--------------------------------------------------------------------------
int Player::ChooseArm()
{
	return rand() % arms.size();
}
//--------------------------------------------------------------------------

void Player::SetHealth(const int &health)
{
	this->health = health;
}
//--------------------------------------------------------------------------
int Player::GetHealth()const
{
	return this->health;
}
//--------------------------------------------------------------------------
int Player::CalculateDamage(const int &arms, const int &dir, const int &block) 
{
	int damage = 0;

	// ≈сли здоровье больше 20, то урон зависит от здоровь€
	if (this->health > HEALTHLIMIT)
	{
		damage = this->health / DAMAGELIMIT;
	}
	else
	{
		damage = MINDAMAGE;
	}

	damage *= this->arms[arms]->GetStrength();

	// ѕри маленьком здоровье бьющего и попадании в блок урон минимальный или вообще не будет
	if (dir == block)
	{
		damage /= this->blocks[block]->GetStrength();
	}

	return damage;
}
//--------------------------------------------------------------------------

vector<Arms*> &Player::GetAmmo()
{
	return this->arms;
}// vector<Arms*> &Player::GetAmmo()
//--------------------------------------------------------------------------
vector<Blocks*> &Player::GetBlocks()
{
	return this->blocks;
}// vector<Blocks*> &Player::GetBlocks()
//--------------------------------------------------------------------------
void Player::Init()
{
	health = HEALTH;
}// void Player::Init()