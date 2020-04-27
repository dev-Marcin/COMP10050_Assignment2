//j

#include <stdio.h>

#include "input_output.h"


int main() {

    // Declaration of players and board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    // Welcome message
    printf("developed by Marcin Nowak - ucd 19300156\n\n");
    printf("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
    printf("                          - || F O C U S || -\n");
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");

    // Initializing players and board
    initialize_players(players);
    initialize_board(board);
    print_board(board);

    // Player turns - main game
    turns(players, board);
    return 0;
}
