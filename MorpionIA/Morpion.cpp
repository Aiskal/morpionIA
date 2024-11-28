#include "Morpion.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

Morpion::Morpion() {
    initGrid();
}
void Morpion::initGrid() {
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
    std::cout << "You play as " << PLAYERCASE << ". And the IA plays as " << IACASE << ".\n"
        "Answer between 1 and 9. Like your keyboard pad.\nEx : Top - left is 7. Bottom - Left is line 1.\n";
}


void Morpion::askChoice() {
    std::string validAnswers = "123456789";

    while (true) {
        std::string choice;
        std::cout << "Where will you play? (1-9 according to numpad)\n";
        std::cin >> choice;

        if (validAnswers.find(choice) != std::string::npos) {
            int num = choice[0] - '0';  // Convertit '1' à '9' en nombre entier

            int row = 2 - (num - 1) / 3;  // Ligne
            int col = (num - 1) % 3;      // Colonne

            if (canPlaceBlock(row, col)) {
                placeBlock(row, col, PLAYERCASE);
                break;
            }
            else {
                std::cout << "You can't place a block here, it's already taken!" << std::endl;
            }

        }
        else {
            std::cout << "Invalid input. Please enter a digit between 1 and 9." << std::endl;
        }
    }
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
    std::vector<std::pair<int, int>> availableMoves = getAvailableMoves();
    int bestScore = -1000;
    std::vector<std::pair<int, int>> bestMoves;

    for (const auto& move : availableMoves) {
        int row = move.first;
        int col = move.second;

        placeBlock(row, col, IACASE);
        int score = minimax(0, false);
        placeBlock(row, col, DEFAULTCASE);

        // Garde le meilleur coup
        if (score > bestScore) {
            bestScore = score;
            bestMoves.clear();
            bestMoves.push_back(move);
        }
        else if (score == bestScore) {
            bestMoves.push_back(move);
        }
    }

    if (!bestMoves.empty()) {
        int randomIndex = std::rand() % bestMoves.size();
        int bestRow = bestMoves[randomIndex].first;
        int bestCol = bestMoves[randomIndex].second;

        placeBlock(bestRow, bestCol, IACASE);
    }
    else {
        std::cout << "IA cannot play. The cells are full.\n";
    }
}

int Morpion::minimax(int depth, bool isMaximizing) {
    if (isWinPlayer(IACASE)) {
        return 10 - depth;  // L'IA a gagné
    }
    if (isWinPlayer(PLAYERCASE)) {
        return depth - 10;  // Le joueur a gagné
    }
    if (isGridFull()) {
        return 0;  // Match nul
    }

    if (isMaximizing) {
        //Test IA
        int bestScore = INT_MIN;
        for (const auto& move : getAvailableMoves()) {
            placeBlock(move.first, move.second, IACASE);
            int score = minimax(depth + 1, false);
            placeBlock(move.first, move.second, DEFAULTCASE);
            bestScore = std::max(score, bestScore);
        }
        return bestScore;
    }
    else {
        //Test Player
        int bestScore = INT_MAX;
        for (const auto& move : getAvailableMoves()) {
            placeBlock(move.first, move.second, PLAYERCASE);
            int score = minimax(depth + 1, true);
            placeBlock(move.first, move.second, DEFAULTCASE);
            bestScore = std::min(score, bestScore);
        }
        return bestScore;
    }
}


std::vector<std::pair<int, int>> Morpion::getAvailableMoves() {
    std::vector<std::pair<int, int>> availableMoves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grille[i][j] == DEFAULTCASE) {
                availableMoves.push_back({ i, j });
            }
        }
    }
    return availableMoves;
}


bool Morpion::isWinPlayer(char player) {
    // Lignes
    for (int i = 0; i < 3; ++i) {
        if (grille[i][0] == player && grille[i][1] == player && grille[i][2] == player) {
            //std::cout << "Player " << player << " wins (line)!" << std::endl;
            return true;
        }
    }

    // Colonnes
    for (int j = 0; j < 3; ++j) {
        if (grille[0][j] == player && grille[1][j] == player && grille[2][j] == player) {
            //std::cout << "Player " << player << " wins (column)!" << std::endl;
            return true;
        }
    }

    // Diagonales
    if (grille[0][0] == player && grille[1][1] == player && grille[2][2] == player) {
        //std::cout << "Player " << player << " wins (diagonal)!" << std::endl;
        return true;
    }
    if (grille[0][2] == player && grille[1][1] == player && grille[2][0] == player) {
        //std::cout << "Player " << player << " wins (diagonal)!" << std::endl;
        return true;
    }

    return false;
}

bool Morpion::isWin() {
    if (isWinPlayer(PLAYERCASE)) {
        std::cout << "Player wins!" << std::endl;
        return true;
    }

    if (isWinPlayer(IACASE)) {
        std::cout << "IA wins!" << std::endl;
        return true;
    }

    if (isGridFull()) {
        std::cout << "Grid is full! Draw.\n";
    }

    return false;
}

void Morpion::Game() {
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

bool isPlayAgain() {
    char choice;
    std::cout << "Do you wanna play again? (y/n)" << std::endl;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        return true;
    }
    return false;
}