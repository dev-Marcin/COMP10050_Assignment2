// Written by Marcin Nowak - 19300156

#ifndef FOCUS_GAMEPLAY_H
#define FOCUS_GAMEPLAY_H

#include "input_output.h"

// Function to merge and move stacks, and to remove and count pieces from stacks >5
void stackMerge(square* origin, square* new, player players[PLAYERS_NUM]);

// Function to check if a game is over
int gameOver(square board[BOARD_SIZE][BOARD_SIZE]);

#endif //FOCUS_GAMEPLAY_H
