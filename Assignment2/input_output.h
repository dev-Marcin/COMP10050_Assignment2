// Written by Marcin Nowak - 19300156

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#include "game_init.h"

// Function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);

// Main game function - handles player inputs and movements on the board
void turns(player players[PLAYERS_NUM], square board[BOARD_SIZE][BOARD_SIZE]);

// Function to add spare pieces onto empty squares on the board
void addPieces(player players[PLAYERS_NUM], square board[BOARD_SIZE][BOARD_SIZE], int turn);

// Function to show end game screen
void victoryScreen(player players[PLAYERS_NUM], int turn, char colour);

#endif //FOCUS_INPUT_OUTPUT_H