#include "Game.h"


Game::Game()
{
	player = new Player;

	computer = new Player;

	turn = FIRST_PLAYER;

	end = false;

}
//---------------------------------------------------------------

Game::~Game()
{
	delete player;

	delete computer;

}
//---------------------------------------------------------------
void Game::SetHistory(const string &history)
{
	this->history.push_back(history);
}// void Game::SetHistory(const string &history)
//---------------------------------------------------------------

void Game::ChangeTurn(const TURN &turn)
{
	this->turn = turn;


}// void Game::ChangeTurn(const TURN &turn)
//---------------------------------------------------------------

Player &Game::GetPlayer()
{
	return *player;
}
//---------------------------------------------------------------

Player &Game::GetComputer()
{
	return *computer;
}
//---------------------------------------------------------------

TURN Game::GetTurn()
{

	return this->turn;

}// TURN Game::GetTurn()
//---------------------------------------------------------------

bool Game::IsOver()
{
	return this->end;

}// bool Game::IsOver()
//---------------------------------------------------------------

void Game::SetEnd(const int &health)
{
	if (health <= 0)
	{
		end = true;

	}//if (health <= 0)

}// void Game::SetEnd(const int &health)
//---------------------------------------------------------------