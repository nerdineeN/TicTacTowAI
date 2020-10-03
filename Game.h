#pragma once
#include "Player.h"
#include "Board.h"
#include "Player.h"

class Game
{
public:
	Game(int numPlayers)
		: NumPlayers(numPlayers), GameBoard(), PlayerOne(), PlayerTwo(), IsPlayerOne(true)
	{
		SetupGame();
	}


	void SetupGame();
	void PlayGame();

private:
	int NumPlayers;
	Board GameBoard;
	Player PlayerOne;
	Player PlayerTwo;
	bool IsPlayerOne;

};