//

#include <stdio.h>
#include "input_output.h"
#include "gameplay.h"

// Printing out the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n____________________  The Board  ____________________\n");
    // Top edge: Squares with X - Coordinates
    printf("|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  | # |\n");
    printf("|-----|-----|-----|-----|-----|-----|-----|-----|---|\n");


    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|     "); // Empty slots
                else {
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G %d ", board[i][j].num_pieces);  // Green piece
                    else printf("| R %d ", board[i][j].num_pieces); // Red piece
                }
            }
            else
                printf("|  X  "); // INVALID/Corner slots
        }
        // Right edge: Squares with Y - Coordinates
        printf("| %d |\n", i);
        // Separating row
        printf("|-----|-----|-----|-----|-----|-----|-----|-----|---|\n");
    }

}

void turns (player players[PLAYERS_NUM], square board[BOARD_SIZE][BOARD_SIZE])
{
    char movement[10];  // Player movement
    int turn = 0;       // Turn count
    // board[i][j] corresponds as: i = y-coord | j = x-coord
    unsigned int x=0, y=0;
    unsigned int x1, y1;

    // Loop runs until game over
    while (turn != -1) {

        // Player input and clearing/printing board
        while (board[y][x].type == INVALID) {

            // Picking which square to move
            printf("\n> Player %d's turn.\nWhich piece would you like to move? X Y\n", turn%2+1);
            scanf("\n%d %d", &x, &y);

            if (board[y][x].type == INVALID) {
                printf(" ~ Cannot move to corner squares!\n");
            }

            if (board[y][x].type == VALID) {
                if (players[turn%2].player_color != board[y][x].stack->p_color) {
                    x = 0;
                    y = 0;
                }
            }
        }
        // x1y1 set to selected piece - player movement applied below
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

        // Clearing screen, printing end pos and moving stacks on the board
        if (board[y1][x1].type != INVALID) {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\n> Turn End Pos :       x:%d y:%d\n", x1, y1);

            stackMerge(&board[y][x], &board[y1][x1], &players[0]);
            print_board(board);
        }

        // Turn counter and position reset
        turn++;
        x = 0;
        y = 0;
    }


}
