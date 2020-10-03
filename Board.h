#pragma once
#include <array>

struct Board
{
	std::array< std::array<char, 3>, 3> boardState = {};

	Board() 
	{
		for (int i = 0; i < boardState.size(); i++)
		{
			for (int j = 0; j < boardState.size(); j++)
			{
				boardState[i][j] = '0';
			}
		}
	}

	void PrintBoardState();
	void UpdateBoard(int row, int col, char token);
	bool IsThatAValidMove(int row, int col);
	bool IsThereAWinner();
	bool IsThereAStalemate();
	bool IsBoardEmpty();


private:
	int lastRow;
	int lastCol;
	char lastToken;
};