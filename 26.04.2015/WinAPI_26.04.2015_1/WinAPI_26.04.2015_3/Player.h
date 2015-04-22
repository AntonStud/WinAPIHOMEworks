#pragma once

#include<vector>
#include <time.h>

using std::vector;

#include"Arms.h"
#include"Blocks.h"

class Player
{
private:

	int health;

	vector<Arms*> arms;
	vector<Blocks*> blocks;

	const int HEALTH;
	const int MINDAMAGE;
	const int DAMAGETWO;
	const int HEALTHLIMIT;
	const int DAMAGELIMIT;

	

public:

	Player();
	~Player();

	int ChooseBlock();
	int ChooseDirect();
	int ChooseArm();

	void SetHealth(const int &health);
	int GetHealth()const;

	int CalculateDamage(const int &arms, const int &dir, const int &block);


	vector<Arms*> &GetAmmo();
	vector<Blocks*> &GetBlocks();
};

