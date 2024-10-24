// MorpionIA.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Morpion.h";

int main()
{
    std::srand(std::time(nullptr));

    Morpion morpion;
    bool play = true;
    morpion.displayRules();

    while (play) {
        morpion.initGrid();
        morpion.Game();
        play = isPlayAgain();
    }

    return 0;
}