//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_output.h"


// Function to set up players at beginning of the game
void initialize_players(player players[PLAYERS_NUM])
{
    char c = 'c'; // player colour

    // Assigning player names and colours
    for (int i = 0; i < PLAYERS_NUM; i++) {
        // Player inputs
        printf("Player %d's name:\n", i+1);
        scanf("%s", players[i].player_name);

        // 1st player choice of colour
        if (i == 0) {
            while (!(c == 'G' || c == 'g'|| c == 'R' || c == 'r')) {
                printf("Chose your colour: 'R' for RED, or 'G' for GREEN?\n");
                scanf("\n%c", &c);
            }
        } else {
            // 2nd player receives remaining colour / Code runs on second loop
            if (c == 'G') {
                players[i].player_color = GREEN;
                players[i].pieces_captured = 0;
                players[i].pieces_owned = 0;
                // Clearing screen and showing player colours at end of player initialization
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("> %d: %s's colour is RED.\n", i, players[i-1].player_name);
                printf("> %d: %s's colour is GREEN.\n", i+1, players[i].player_name);
            }
            else if (c == 'R') {
                players[i].player_color = RED;
                players[i].pieces_captured = 0;
                players[i].pieces_owned = 0;
                // Clearing screen and showing player colours at end of player initialization
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("> %d: %s's colour is GREEN.\n", i, players[i-1].player_name);
                printf("> %d: %s's colour is RED.\n", i+1, players[i].player_name);
            }
        }

        // Player 1 choice of colour - Sets 'char c' to remaining colour for Player 2
        if (i == 0 && (c == 'G' || c == 'g')) {
            players[i].player_color = GREEN;
            players[i].pieces_captured = 0;
            players[i].pieces_owned = 0;
            c = 'R';
        } else if (i == 0 && (c == 'R' || c == 'r')) {
            players[i].player_color = RED;
            players[i].pieces_captured = 0;
            players[i].pieces_owned = 0;
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