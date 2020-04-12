//

#include <stdio.h>
#include "input_output.h"

// Printing out the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n____________________  The Board  ____________________\n");
    // Top edge: Squares with X - Coordinates
    printf("|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |   |\n");
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
    char movement[11];  // Player movement
    int turn = 0;       // Turn count
    // board[i][j] corresponds as: i = y-coord | j = x-coord
    unsigned int x=0, y=0;
    unsigned int x1, y1;

    // Loop runs until game over
    while (turn != -1) {

        // Player input and clearing/printing board
        while (board[y][x].type == INVALID) {

            // Refreshing screen
            while (turn != 0) {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("\n> Turn End Pos :       x:%d y:%d\n", x1, y1);
                print_board(board);
                break;
            }

            // Picking which square to move
            printf("\n> Player %d's turn.\nWhich square would you like to move? X Y\n", (turn % 2)+1);
            scanf("\n%d %d", &x, &y);
            if ((x==0 && (y==0 || y==1 || y==6 || y==7)) ||
                (x==1 && (y==0 || y==7)) || (x==6 && (y==0 || y==7)) ||
                (x==7 && (y==0 || y==1 || y==6 || y==7))) {
                printf(" ~ Cannot move to invalid square! ~\n");
            }

            if (board[y][x].type == VALID) {
                if (players[turn%2].player_color != board[y][x].stack->p_color) {
                    x = 0;
                    y = 0;
                }
            }
        }

        x1 = x;
        y1 = y;


        printf("Which direction do you want to move? Length of movement = Stack Size\nChoices: U, D, L, R. No spaces!\n");
        scanf("\n%s", movement);

        for (int i = 0; i < 11; i++) {

            if (movement[i] == 'U') {
                y1--;
            } else if (movement[i] == 'D') {
                y1++;
            } else if (movement[i] == 'L') {
                x1--;
            } else if (movement[i] == 'R') {
                x1++;
            }
        }

        // Turn counter and reset
        turn++;
        x = 0;
        y = 0;
    }


}
