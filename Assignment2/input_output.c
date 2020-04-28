// Written by Marcin Nowak - 19300156

#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"
#include "gameplay.h"

// Printing out the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n____________________  The Board  ____________________\n");
    // Top edge: Squares with X - Coordinates
    printf("|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  | # |\n");
    printf("|-----|-----|-----|-----|-----|-----|-----|-----|---|\n");

    // Printing the body of the board
    for(int j = 0; j < BOARD_SIZE; j ++){
        for (int i = 0; i < BOARD_SIZE; i++){
            if(board[j][i].type == VALID) {
                if(board[j][i].stack == NULL)
                    printf("|     "); // Empty slots
                else {
                    if (board[j][i].stack->p_color == GREEN)
                        printf("| G %d ", board[j][i].num_pieces);  // Green piece
                    else printf("| r %d ", board[j][i].num_pieces); // Red piece
                }
            }
            else
                printf("|  X  "); // INVALID/Corner slots
        }
        // Right edge: Squares with Y - Coordinates
        printf("| %d |\n", j);
        // Separating row
        printf("|-----|-----|-----|-----|-----|-----|-----|-----|---|\n");
    }

}

// Main game function - handles player inputs and movements on the board
void turns(player players[PLAYERS_NUM], square board[BOARD_SIZE][BOARD_SIZE])
{
    char movement[6];   // Player movement
    int turn = 0;       // Turn count
    // board[i][j] corresponds as: i = y-coord | j = x-coord
    unsigned int x=0, y=0;
    unsigned int x1, y1;

    // Loop runs until game over
    while (turn != -1) {

        // Player input and clearing/printing board
        while (board[y][x].type == INVALID) {

            // Checking for winning conditions & ending game if met
            if (turn != 0) {
                if (gameOver(board) == 1) {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    print_board(board);
                    printf("\n\n> GREEN wins!\n");
                    victoryScreen(players, turn, 'G');
                    exit(0); // Game over
                }
                else if (gameOver(board) == 2) {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    print_board(board);
                    printf("\n\n> RED wins!\n");
                    victoryScreen(players, turn, 'R');
                    exit(0); // Game over
                }
            }

            // Ability to add spare 'pieces_owned'
            addPieces(players, board, turn);

            // Choosing which square to move
            printf("\n> Player %d's turn.\nWhich piece would you like to move? X space Y\n", turn%2+1);
            scanf("\n%d %d", &x, &y);

            // Reset if chosen square is invalid
            if (board[y][x].type == INVALID) {
                printf(" ~ Cannot move that square!\n");
            }

            // Reset if chosen square is not the right colour
            if (board[y][x].type == VALID && board[y][x].stack != NULL) {
                if (players[turn%2].player_color != board[y][x].stack->p_color) {
                    printf(" ~ Cannot move an opponents square!\n");
                    x = 0;
                    y = 0;
                }
            }
        }
        // x1y1 set to selected piece - desired player movement applied below
        x1 = x;
        y1 = y;

        // Player movement input
        printf("Which direction do you want to move? Max length of movement = Stack size\nChoices: U, D, L, R. No spaces!\n");
        scanf("\n%s", movement);

        // Reading player movement above, and modifying x1y1 accordingly, with respect to stack size
        for (int i = 0; i < board[y][x].num_pieces; i++) {
            if (movement[i] == 'U' || movement[i] == 'u') {
                y1--;
            } else if (movement[i] == 'D' || movement[i] == 'd') {
                y1++;
            } else if (movement[i] == 'L' || movement[i] == 'l') {
                x1--;
            } else if (movement[i] == 'R' || movement[i] == 'r') {
                x1++;
            }
        }

        // Reset if player makes an invalid move
        if (board[y1][x1].type == INVALID) {
            printf("~ Cannot move to that square. You just lost a turn!\n");
        }

        // Clearing screen, printing end pos and merging/moving stacks on the board
        if (board[y1][x1].type != INVALID) {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\n> Turn End Pos :       x:%d y:%d\n", x1, y1);

            stackMerge(&board[y][x], &board[y1][x1], &players[turn%2]);
            // Showing number of captured and owned pieces
            printf("> Player 1: Captured: %d. Owned: %d.\n", players[0].pieces_captured, players[0].pieces_owned);
            printf("> Player 2: Captured: %d. Owned: %d.\n", players[1].pieces_captured, players[1].pieces_owned);
            print_board(board);
        }

        // Turn counter and position reset
        turn++;
        x = 0;
        y = 0;
    }
}

// Function to add spare pieces onto empty squares on the board
void addPieces(player players[PLAYERS_NUM], square board[BOARD_SIZE][BOARD_SIZE], int turn)
{
    char spare = 'n';   // For checking if player wants to insert a spare piece
    int x=0, y=0;

    // Code runs once the current player has any spare 'pieces_owned'
    if (players[turn%2].pieces_owned != 0) {
        printf("> Player %d's turn.\nWould you like to place a spare piece? Y / N\n", turn%2+1);
        scanf("\n%c", &spare);

        if (spare == 'Y' || spare == 'y') {
            while (board[y][x].type == INVALID || board[y][x].stack != NULL) {
                printf("Where would you like to place a piece? X space Y\n> You can only place a piece on an EMPTY square.\n");
                scanf("\n%d %d", &x, &y);

            }
            // Adding spare piece to desired board coordinates
            if (players[turn%2].player_color == RED) {
                set_red(&board[y][x]);
                players[turn%2].pieces_owned--;
            }
            else if (players[turn%2].player_color == GREEN) {
                set_green(&board[y][x]);
                players[turn%2].pieces_owned--;
            }

            // Reprinting board
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("> Player 1: Captured: %d. Owned: %d.\n", players[0].pieces_captured, players[0].pieces_owned);
            printf("> Player 2: Captured: %d. Owned: %d.\n", players[1].pieces_captured, players[1].pieces_owned);
            print_board(board);
        }
    }
}

// Function to show end game screen
void victoryScreen(player players[PLAYERS_NUM], int turn, char colour)
{
    // Victory message for both player colours
    if (colour == 'G') {
        printf("> Congratulations %s! You won in %d rounds.\n> You captured %d enemy piece(s)! The enemy captured %d of your pieces.\n\n", players[GREEN].player_name, turn, players[GREEN].pieces_captured, players[RED].pieces_captured);
        printf("< Thanks for playing! :)\n");
    }
    else if (colour == 'R') {
        printf("> Congratulations %s! You won in %d rounds.\n> You captured %d enemy piece(s)! The enemy captured %d of your pieces.\n\n", players[RED].player_name, turn, players[RED].pieces_captured, players[GREEN].pieces_captured);
        printf("< Thanks for playing! :)\n");
    }
}
