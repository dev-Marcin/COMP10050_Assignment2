//

#include <stdio.h>
#include "input_output.h"


void print_board(square board[BOARD_SIZE][BOARD_SIZE])
{
    // Printing out the board
    printf("\n***************** ___ The Board ___ *****************\n");
    // Squares with X - Coordinates
    printf("|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |   |\n");
    printf("|-----|-----|-----|-----|-----|-----|-----|-----|---|\n");


    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|     ");
                else {
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G %d ", board[i][j].num_pieces);  // Green piece
                    else printf("| R %d ", board[i][j].num_pieces); // Red piece
                }
            }
            else
                printf("|  =  "); // Corner slots
        }
        // Right edge slots - Slots with Y - Coordinates
        printf("| %d |\n", i);
        // Separating row
        printf("|-----|-----|-----|-----|-----|-----|-----|-----|---|\n");
    }
}
