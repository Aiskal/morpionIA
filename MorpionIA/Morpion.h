#pragma once

#include <vector>
#define DEFAULTCASE '-'
#define PLAYERCASE 'O'
#define IACASE 'X'

#define INT_MIN 10

class Morpion
{
private:
	char grille[3][3];

public:
	Morpion();

	void displayMorpion();
	void displayRules();
	void askChoice();

	void placeBlock(int row, int col, char value);
	bool isGridFull();
	int minimax(char currentPlayer, char board[3][3], int depth);
	bool canWinIAPlay(char player);
	bool canPlaceBlock(int row, int col);

	void iaPlay();

	bool isWinPlayer(char player);

	bool isWin();

	void Game();

};

