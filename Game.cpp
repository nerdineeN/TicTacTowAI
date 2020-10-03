#include "Game.h"
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

void Game::SetupGame()
{
	while (NumPlayers > 2)
	{
		cout << "Can only have 2 players, how many players are playing (1 or 2)" << endl;
		cin >> NumPlayers;
	}

	std::string playerName = "";
	char token;
	switch (NumPlayers)
	{
	case 1:
		cout << "Player one enter your name and token you wish to use. " << endl;
		cin >> playerName;
		cin >> token;
		PlayerOne.InitPlayer(true, token, playerName,true);
		PlayerTwo.InitPlayer(false, 'O', "Turing", false);
		break;
	case 2:
		cout << "Player one enter your name and token you wish to use. " << endl;
		cin >> playerName;
		cin >> token;
		PlayerOne.InitPlayer(true, token, playerName, true);
		cout << "Player Two enter your name and token you wish to use. " << endl;
		cin >> playerName;
		cin >> token;
		PlayerTwo.InitPlayer(true, token, playerName, false);
		break;
	default:
		PlayerOne.InitPlayer(false, 'X', "Allen", true);
		PlayerTwo.InitPlayer(false, 'O', "Turing", false);
		break;
	}

  //Print the Board
	GameBoard.PrintBoardState();
}

void Game::PlayGame()
{
	while (true)
	{
		cout << PlayerOne.GetName() << endl;
		//player one chooses a spot on the board
		auto choiceOne = PlayerOne.ChooseASpotOnTheBoard(GameBoard);
		//board checks to see if move is valid
		//if move is not valid, choose again, otherwise
		bool isValid = GameBoard.IsThatAValidMove(get<0>(choiceOne), get<1>(choiceOne));
		while (isValid != true)
		{
			choiceOne = PlayerOne.ChooseASpotOnTheBoard(GameBoard);
			isValid = GameBoard.IsThatAValidMove(get<0>(choiceOne), get<1>(choiceOne));
		}
		//board updates
		GameBoard.UpdateBoard(get<0>(choiceOne), get<1>(choiceOne), PlayerOne.GetToken());

		//prints board
		GameBoard.PrintBoardState();
		//board checks to see if there is a winner
		auto DidPlayerOneWin = GameBoard.IsThereAWinner();
		//print player one has won, and exit
		if (DidPlayerOneWin)
		{
			cout << PlayerOne.GetName() << " wins the game" << endl;
			break;
		}
		//Check for a stalemate
		if (GameBoard.IsThereAStalemate())
		{
			cout << "Tie Game" << endl;
			break;
		}
		//player two repeats
		cout << PlayerTwo.GetName() << endl;
		//player one chooses a spot on the board
		auto choiceTwo = PlayerTwo.ChooseASpotOnTheBoard(GameBoard);
		//board checks to see if move is valid
		//if move is not valid, choose again, otherwise
		isValid = GameBoard.IsThatAValidMove(get<0>(choiceTwo), get<1>(choiceTwo));
		while (isValid != true)
		{
			choiceOne = PlayerTwo.ChooseASpotOnTheBoard(GameBoard);
			isValid = GameBoard.IsThatAValidMove(get<0>(choiceTwo), get<1>(choiceTwo));
		}
		//board updates
		GameBoard.UpdateBoard(get<0>(choiceTwo), get<1>(choiceTwo), PlayerTwo.GetToken());

		//prints board
		GameBoard.PrintBoardState();
		//board checks to see if there is a winner
		auto DidPlayerTwoWin = GameBoard.IsThereAWinner();
		//print player one has won, and exit
		if (DidPlayerTwoWin)
		{
			cout << PlayerTwo.GetName() << " wins the game" << endl;
			break;
		}
		

	}
	cout << "End Game" << endl;
}