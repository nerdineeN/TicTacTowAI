#include "Player.h"
#include <iostream>
#include <tuple>
#include <math.h>

using namespace std;

void Player::InitPlayer(bool human, char token, std::string name, bool playerOne = true)
{
	IsHuman = human;
	if (playerOne)
	{
		Token = 'X';
		OppToken = 'O';
	}
	else
	{
		Token = 'O';
		OppToken = 'X';
	}
		
	Name = name;
	isPlayerOne = playerOne;
}

std::tuple<int, int> Player::ChooseASpotOnTheBoard(Board boardCondition)
{
	int row, col;

	if (IsHuman)
	{
		cout << "Choose your coordinates 0 - 2 for row and column" << endl;
		cin >> row;
		cin >> col;
	}
	else
	{
		if (boardCondition.IsBoardEmpty())
		{
			return make_tuple(0, 0);
		}

		int bestVal = -100000;

		for (int i = 0; i < boardCondition.boardState.size(); i++)
		{
			for (int j = 0; j < boardCondition.boardState.size(); j++)
			{
				if (boardCondition.boardState[i][j] == '0')
				{
					boardCondition.UpdateBoard(i, j, Token);
					int MoveValue = minimaxAlgorithm(boardCondition, 0, isPlayerOne);
					boardCondition.UpdateBoard(i, j, '0');
					if (MoveValue > bestVal)
					{
						row = i;
						col = j;
						bestVal = MoveValue;
					}
				}
			}
		}
	}

	

	return make_tuple(row, col);
}


//sees if we can win or not.... and gives a score
int Player::evaluateMove(Board boardCondition, bool isMax)
{
	bool isWinner = false;
	int score = 0;
	//Check rows first
	for (int col = 0; col < boardCondition.boardState.size(); col++)
	{
		if (boardCondition.boardState[0][col] == Token ||
			boardCondition.boardState[1][col] == Token ||
			boardCondition.boardState[2][col] == Token)
		{
			score += 10;
		}
		else if (boardCondition.boardState[0][col] == OppToken ||
			boardCondition.boardState[1][col] == OppToken ||
			boardCondition.boardState[2][col] == OppToken)
		{
			score += -10;
		}
	}

	//Then col first
	for (int row = 0; row < boardCondition.boardState.size(); row++)
	{
		if (boardCondition.boardState[row][0] == Token ||
			boardCondition.boardState[row][1] == Token ||
			boardCondition.boardState[row][2] == Token)
		{
			score += 10;
		}
		else if(boardCondition.boardState[row][0] == OppToken ||
			boardCondition.boardState[row][1] == OppToken ||
			boardCondition.boardState[row][2] == OppToken)
		{
			score += -10;
		}
	}

	//Now check the diags
	//0,0 to 0,1
	if ((boardCondition.boardState[0][0] == Token) &&
		(boardCondition.boardState[1][1] == Token) &&
		(boardCondition.boardState[2][2] == Token))
	{
		score += 10;
	}
	if ((boardCondition.boardState[0][2] == Token) &&
		(boardCondition.boardState[1][1] == Token) &&
		(boardCondition.boardState[2][0] == Token))
	{
		score += 10;
	}
	if ((boardCondition.boardState[0][0] == OppToken) &&
		(boardCondition.boardState[1][1] == OppToken) &&
		(boardCondition.boardState[2][2] == OppToken))
	{
		score += -10;
	}
	if ((boardCondition.boardState[0][2] == OppToken) &&
		(boardCondition.boardState[1][1] == OppToken) &&
		(boardCondition.boardState[2][0] == OppToken))
	{
		score += -10;
	}
	
	if (score >= bestMoveMax)
	{
		bestMoveMax = score;
	}
	else if (score <= bestMoveMin)
	{
		bestMoveMin = score;
	}

	return score;
}

int Player::minimaxAlgorithm(Board boardCondition, int depth, bool isMax)
{
	int score = evaluateMove(boardCondition, isMax);
	
	if (isMax && depth == 10)
	{
		return bestMoveMax;
	}
	else if (!isMax && depth == 10)
	{
		return bestMoveMin;
	}

	if (boardCondition.IsThereAStalemate()) //stalemate
	{
		return score;
	}

	if (isMax)
	{
		int bestScore = -1000;
		for (int i = 0; i < boardCondition.boardState.size(); i++)
		{
			for (int j = 0; j < boardCondition.boardState.size(); j++)
			{
				int bestScore = -1000;
				if (boardCondition.IsThatAValidMove(i, j))
				{
					boardCondition.UpdateBoard(i, j, Token);
					bestScore = std::max(bestScore, minimaxAlgorithm(boardCondition, depth + 1, !isMax));
					//boardCondition.PrintBoardState();

					boardCondition.UpdateBoard(i, j, '0');
				}
				
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 1000;
		for (int i = 0; i < boardCondition.boardState.size(); i++)
		{
			for (int j = 0; j < boardCondition.boardState.size(); j++)
			{
				int bestScore = 1000;
				if (boardCondition.IsThatAValidMove(i, j))
				{
					boardCondition.UpdateBoard(i, j, OppToken);
					bestScore = std::min(bestScore, minimaxAlgorithm(boardCondition, depth + 1, !isMax));
					//boardCondition.PrintBoardState();
					boardCondition.UpdateBoard(i, j, '0');
				}
			}
		}
		return bestScore;
	}

	

}