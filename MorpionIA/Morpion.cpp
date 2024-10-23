#include "Morpion.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

Morpion::Morpion() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grille[i][j] = DEFAULTCASE;
        }
    }
}

void Morpion::displayMorpion() {
    std::cout << " +---+---+---+" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << " | " << grille[i][j];

        }
        std::cout << " |" << std::endl;
    }
    std::cout << " +---+---+---+" << std::endl;
}

void Morpion::displayRules()
{
    std::cout << "Yo play as " << PLAYERCASE << ".IA plays as " << IACASE << ".\nAnswer in two numbers : first from top to bottom, second from left to right.\nEx : Top - left is 11. Bottom - Left is line 31.\n";
}


void Morpion::askChoice()
{
    std::string validAnswers = "123";

    while (true) {
        std::string choice;
        std::cout << "Where will you play ?";
        std::cin >> choice;

        if (validAnswers.find(choice[0]) != std::string::npos &&
            validAnswers.find(choice[1]) != std::string::npos) {

            int row = choice[0] - '1';  // Convertit '1', '2', '3' en 0, 1, 2
            int col = choice[1] - '1';

            if (canPlaceBlock(row, col)) {
                placeBlock(row, col, PLAYERCASE);
                break;
            }
            else {
                std::cout << "You can't place a block here, it's already taken!" << std::endl;
            }

        }
        else {
            std::cout << "Invalid input. Please enter two digits between 1 and 3 (e.g., 11, 23)." << std::endl;
        }
    }
    return;
}

void Morpion::placeBlock(int row, int col, char value)
{
    grille[row][col] = value;
}

bool Morpion::canPlaceBlock(int row, int col)
{
    return grille[row][col] == DEFAULTCASE;
}

bool Morpion::isGridFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grille[i][j] == DEFAULTCASE) {
                return false;
            }
        }
    }
    return true;
}



bool Morpion::canWinIAPlay(char player) {
    bool ignoreColumns[3] = { false, false, false };

    // Lignes
    for (int i = 0; i < 3; ++i) {
        int playerCount = 0;
        int emptyCount = 0;

        for (int j = 0; j < 3; ++j) {
            if (grille[i][j] == player) {
                playerCount++;
            }
            else if (grille[i][j] == DEFAULTCASE) {
                emptyCount++;
            }
            else if (grille[i][j] == PLAYERCASE) {
                ignoreColumns[j] = true;
            }
        }

        //Win
        if (playerCount == 2 && emptyCount == 1) {
            for (int j = 0; j < 3; ++j) {
                if (grille[i][j] == DEFAULTCASE) {
                    placeBlock(i, j, IACASE);
                    return true;
                }
            }
        }
    }

    // Colonnes
    for (int j = 0; j < 3; ++j) {
        if (ignoreColumns[j]) continue; //Nice c'est efficace !

        int playerCount = 0;
        int emptyCount = 0;

        for (int i = 0; i < 3; ++i) {
            if (grille[i][j] == player) {
                playerCount++;
            }
            else if (grille[i][j] == DEFAULTCASE) {
                emptyCount++;
            }
        }

        //Win
        if (playerCount == 2 && emptyCount == 1) {
            for (int i = 0; i < 3; ++i) {
                if (grille[i][j] == DEFAULTCASE) {
                    placeBlock(i, j, IACASE);
                    return true;
                }
            }
        }
    }

    //Diagonales
    if (grille[1][1] == PLAYERCASE || grille[1][1] == DEFAULTCASE) {
        //Première diagonale
        int playerCount = 0;
        int emptyCount = 0;

        for (int i = 0; i < 3; ++i) {
            if (grille[i][i] == player) {
                playerCount++;
            }
            else if (grille[i][i] == DEFAULTCASE) {
                emptyCount++;
            }
        }

        //Win
        if (playerCount == 2 && emptyCount == 1) {
            for (int i = 0; i < 3; ++i) {
                if (grille[i][i] == DEFAULTCASE) {
                    placeBlock(i, i, IACASE);
                    return true;
                }
            }
        }

        //Deuxième diagonale
        playerCount = 0;
        emptyCount = 0;

        for (int i = 0; i < 3; ++i) {
            if (grille[i][2 - i] == player) {
                playerCount++;
            }
            else if (grille[i][2 - i] == DEFAULTCASE) {
                emptyCount++;
            }
        }

        //Win
        if (playerCount == 2 && emptyCount == 1) {
            for (int i = 0; i < 3; ++i) {
                if (grille[i][2 - i] == DEFAULTCASE) {
                    placeBlock(i, 2 - i, IACASE);
                    return true;
                }
            }
        }
    }

    return false;
}



void Morpion::iaPlay() {
    if (canWinIAPlay(IACASE)) {
        return;
    }
    if (canWinIAPlay(PLAYERCASE)) {
        return; // Bloque le coup gagnant du joueur
    }

    //Sinon random!
    std::vector<std::pair<int, int>> emptyCells;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grille[i][j] == DEFAULTCASE) {
                emptyCells.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!emptyCells.empty()) {
        int randomIndex = std::rand() % emptyCells.size();
        int row = emptyCells[randomIndex].first;
        int col = emptyCells[randomIndex].second;

        placeBlock(row, col, IACASE);
    }
    else {
        std::cout << "IA cannot play. The cells are full.\n";
    }
}

bool Morpion::isWinPlayer(char player) {
    // Lignes
    for (int i = 0; i < 3; ++i) {
        if (grille[i][0] == player && grille[i][1] == player && grille[i][2] == player) {
            std::cout << "Player " << player << " wins (line)!" << std::endl;
            return true;
        }
    }

    // Colonnes
    for (int j = 0; j < 3; ++j) {
        if (grille[0][j] == player && grille[1][j] == player && grille[2][j] == player) {
            std::cout << "Player " << player << " wins (column)!" << std::endl;
            return true;
        }
    }

    // Diagonales
    if (grille[0][0] == player && grille[1][1] == player && grille[2][2] == player) {
        std::cout << "Player " << player << " wins (diagonal)!" << std::endl;
        return true;
    }
    if (grille[0][2] == player && grille[1][1] == player && grille[2][0] == player) {
        std::cout << "Player " << player << " wins (diagonal)!" << std::endl;
        return true;
    }

    return false;
}

bool Morpion::isWin() {
    if (isWinPlayer(PLAYERCASE)) {
        return true;
    }

    if (isWinPlayer(IACASE)) {
        return true;
    }

    if (isGridFull()) {
        std::cout << "Grid is full! Draw.\n";
    }

    return false;
}

void Morpion::Game() {
    displayRules();
    displayMorpion();

    while (!isWin() || isGridFull()) {
        askChoice();
        displayMorpion();
    
        if (isWin() || isGridFull()) {
            break;
        }

        iaPlay(); 
        displayMorpion();
    }
}