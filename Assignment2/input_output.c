//

#include <stdio.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R |
 */

void print_board(square board[BOARD_SIZE][BOARD_SIZE])
{
    printf("\n******************** __ The Board __ ********************\n");
    printf("|------|------|------|------|------|------|------|------|\n");

    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|      ");
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G  %d ", board[i][j].num_pieces);
                    else printf("| R  %d ", board[i][j].num_pieces);
                }
            }
            else
                printf("|  ==  ");
        }
        printf("|\n");
        printf("|------|------|------|------|------|------|------|------|\n");
    }
}
