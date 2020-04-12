//

#include <stdio.h>
#include "input_output.h"

// Printing out the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n_____________________ The Board _____________________\n");
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
