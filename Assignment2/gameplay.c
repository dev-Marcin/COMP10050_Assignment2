//

#include <stdio.h>
#include "gameplay.h"

void stackMerge (square* origin, square* new, player* players)
{
    piece* prev; // will hold old stack
    piece* tmp_stack = origin->stack; // current stack
    piece* tmp = tmp_stack;

    // Counter of pieces in stack
    int count = 0;

    // Counts number of pieces in stack, goes to end of stack
    while(tmp->next != NULL) {
        tmp = tmp->next;
        count++;
    }

    // Adding new stack to end of the old stack
    tmp->next = new->stack;

    // Checking for end of stack
    while (tmp != NULL) {
        // Removing pieces from stack size >5, and adding them to captured or owned pieces
        if (count >= 5) {
            if (tmp->p_color == players->player_color) {
                players->pieces_owned++;
            }
            else if (tmp->p_color != players->player_color) {
                players->pieces_captured++;
            }
        }

        // 'prev' stack set as old stack
        prev = tmp->next;

        // When tmp reaches 5th piece in stack
        if (count == 4) {
            tmp->next = NULL;
            new->num_pieces = 5;
        }
        tmp = prev;
        count++;
    }

    // When stack size is <5, setting stack size to count
    if (count <= 4) {
        new->num_pieces = count;
    }

    new->stack = tmp_stack;
    origin->stack = NULL;
    origin->num_pieces = 0;
}

