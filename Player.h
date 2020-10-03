#pragma once

#include <string>
#include "Board.h"

class Player
{
public:
	Player() : IsHuman(true), Token('A'), Name("Allen Turing"), isPlayerOne(false), bestMoveMax(0), bestMoveMin(0) {}
	void InitPlayer(bool human, char token, std::string name, bool playerOne); 

	std::tuple<int, int> ChooseASpotOnTheBoard(Board boardCondition);
	char GetToken() { return Token; }
	std::string GetName() { return Name; }
	int minimaxAlgorithm(Board boardCondition, int depth, bool isMax);
	int evaluateMove(Board boardCondition, bool isMax);

private:

	bool IsHuman;
	char Token;
	char OppToken;
	std::string Name;
	bool isPlayerOne;
	int bestMoveMax;
	int bestMoveMin;
};