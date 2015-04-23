#pragma once

#include<vector>


#include "Player.h"


using std::vector;


enum TURN{FIRST_PLAYER, COMPUTER};

class Game
{
private:

	Player *player;
	Player *computer;

	TURN turn;

	bool end;

	vector<string>history;

	

public:
	Game();
	~Game();

	void Init();

	void SetHistory(const string &history);

	void ChangeTurn(const TURN &turn);
	TURN GetTurn();

	Player &GetPlayer();
	Player &GetComputer();

	bool IsOver();

	void SetEnd(const int &health);

};
