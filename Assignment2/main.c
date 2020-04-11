//j

#include <stdio.h>

#include "input_output.h"


int main() {

    // Declaration of players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    // Initializing players and board
    initialize_players(players);
    initialize_board(board);
    print_board(board);

    // Player turns
    turns(players, board);
    return 0;
}
