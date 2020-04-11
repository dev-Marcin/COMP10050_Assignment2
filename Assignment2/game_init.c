//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_output.h"


// Function to set up players at beginning of the game
void initialize_players(player players[PLAYERS_NUM])
{
    char c = 'c';
    for (int i = 0; i < PLAYERS_NUM; i++) {
        // Player inputs
        printf("Player %d's name:\n", i+1);
        scanf("%s", players[i].player_name);

        // 1st player choice of colour
        if (i == 0) {
            while (!(c == 'G' || c == 'R')) {
                printf("Player %d's colour 'R' for RED, or 'G' for GREEN?\n", i+1);
                scanf("\n%c", &c);
            }
        } else {
            // 2nd player gets remaining colour
            if (c == 'G') {
                players[i].player_color = GREEN;
                printf("Player %d's colour is GREEN.\n", i+1);
            } else if (c == 'R') {
                players[i].player_color = RED;
                printf("Player %d's colour is RED.\n", i+1);
            }
        }

        // Player 1 choice of colour - Sets 'char c' to remaining colour for Player 2
        if (i == 0 && c == 'G') {
            players[i].player_color = GREEN;
            printf("Player %d's colour is GREEN.\n", i+1);
            c = 'R';
        } else if (i == 0 && c == 'R') {
            players[i].player_color = RED;
            printf("Player %d's colour is RED.\n", i+1);
            c = 'G';
        }
    }
}


//Set Invalid Squares (where it is not possible to place stacks)
void set_invalid(square * s)
{
    s->type = INVALID;
    s->stack = NULL;
    s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
void set_empty(square * s)
{
    s->type = VALID;
    s->stack = NULL;
    s->num_pieces = 0;
}

//Set squares  with a GREEN piece
void set_green(square * s)
{
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->p_color = GREEN;
    s->stack->next = NULL;
    s->num_pieces = 1;
}

//Set squares with a RED piece
void set_red(square * s)
{
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->p_color = RED;
    s->stack->next = NULL;
    s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE])
{
    for(int i=0; i< BOARD_SIZE; i++) {
        for(int j=0; j< BOARD_SIZE; j++) {
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else {
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }
    }
}

void turns (player players[PLAYERS_NUM], square board[BOARD_SIZE][BOARD_SIZE])
{
    int turn = 0;
    char direction[15];
    // board[i][j] corresponds as: i = y-coord | j = x-coord
    unsigned int x=0, y=0;
    unsigned int x1, y1;

    while (turn != -1) {

        while (board[y][x].type == INVALID) {

            // Clear screen
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            print_board(board);
            
            printf("* Player %d's turn.\nWhich square would you like to move? X Y\n", (turn % 2)+1);
            scanf("\n%d %d", &x, &y);

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
        scanf("\n%s", direction);

        for (int i = 0; i < 15; i++) {

            if (direction[i] == 'U') {
                y1--;
            }
            else if (direction[i] == 'D') {
                y1++;
            }
            else if (direction[i] == 'L') {
                x1--;
            }
            else if (direction[i] == 'R') {
                x1++;
            }
        }
        printf("\nEnd pos: %d %d\n", x1, y1);
        turn++;

        x = 0;
        y = 0;
    }


}

