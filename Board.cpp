#include "Board.h"
#include <iostream>

using namespace std;

void Board::PrintBoardState()
{
	for (int i = 0; i < boardState.size(); i++)
	{
		for (int j = 0; j < boardState.size(); j++)
		{
			cout << boardState[i][j] << ' ' ;
		}
		cout << "\n _____" << endl;
	}
	cout << "\n\n\n" << endl;
}

bool Board::IsThatAValidMove(int row, int col)
{
	if (boardState[row][col] == '0')
	{
		return true;
	}

	return false;
}

bool Board::IsThereAWinner()
{

/*
	(0,0) | (0,1) | (0,2)

	(1,0) | (1,1) | (1,2)
	
	(2,0) | (2,1) | (2,2)

	
*/
	bool isWinner = false;
	//Check rows first
	for (int col = 0; col < boardState.size(); col++)
	{
		if (boardState[lastRow][col] == lastToken)
		{
			isWinner = true;
		}
		else
		{
			isWinner = false;
			break;
		}
	}

	if (isWinner == true)
		return isWinner;

	//Then col first
	for (int row = 0; row < boardState.size(); row++)
	{
		if (boardState[row][lastCol] == lastToken)
		{
			isWinner = true;
		}
		else
		{
			isWinner = false;
			break;
		}
	}

	if (isWinner == true)
		return isWinner;
		
	//Now check the diags
	if ((lastRow == 0 && lastCol == 0) ||
		(lastRow == 0 && lastCol == 2) ||
		(lastRow == 2 && lastCol == 0) ||
		(lastRow == lastCol))
	{
		//0,0 to 0,1
		if ((boardState[0][0] == lastToken) &&
			(boardState[1][1] == lastToken) &&
			(boardState[2][2] == lastToken))
		{
			return true;
		}
		if ((boardState[0][2] == lastToken) &&
			(boardState[1][1] == lastToken) &&
			(boardState[2][0] == lastToken))
		{
			return true;
		}
	}
		
	return isWinner;
}

bool Board::IsThereAStalemate()
{
	for (int i = 0; i < boardState.size(); i++)
	{
		for (int j = 0; j < boardState.size(); j++)
		{
			if (boardState[i][j] == '0')
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::IsBoardEmpty()
{
	for (int i = 0; i < boardState.size(); i++)
	{
		for (int j = 0; j < boardState.size(); j++)
		{
			if (boardState[i][j] != '0')
			{
				return false;
			}
		}
	}
	return true;
}


void Board::UpdateBoard(int row, int col, char token)
{
	boardState[row][col] = token;
	lastRow = row;
	lastCol = col;
	lastToken = token;
}