#pragma once

#include <vector>
#define DEFAULTCASE '-'
#define PLAYERCASE 'O'
#define IACASE 'X'

class Morpion
{
private:
	char grille[3][3];

public:
	Morpion();

	void initGrid();

	void displayMorpion();
	void displayRules();
	void askChoice();

	void placeBlock(int row, int col, char value);
	bool isGridFull();
	bool canWinIAPlay(char player);
	bool canPlaceBlock(int row, int col);

	void iaPlay();

	int minimax(int depth, bool isMaximizing);

	std::vector<std::pair<int, int>> getAvailableMoves();

	bool isWinPlayer(char player);

	bool isWin();

	void Game();

};

bool isPlayAgain();

