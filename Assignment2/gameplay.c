//

#include <stdio.h>
#include "gameplay.h"

void stackMerge (square* origin, square* new, player* players)
{
    piece* prev;
    piece* tmp_stack = origin->stack;
    piece* tmp = tmp_stack;

    // Counter of pieces in stack
    int count = 0;

    while(tmp->next != NULL) {
        tmp = tmp->next;
        count++;
    }

    tmp->next = new->stack;
    while (tmp->next != NULL) {
        if (count >= 5) {
            if (tmp->p_color == players->player_color) {
                players->pieces_owned++;
            }
            else if (tmp->p_color != players->player_color) {
                players->pieces_captured++;
            }
        }

        prev = tmp->next;
        if (count == 4) {
            tmp->next = NULL;
            new->num_pieces = 5;
        }
        tmp = prev;
        count++;
    }

    if (count > 4) {
        new->num_pieces = 5;
    } else {
        new->num_pieces = count + 1;
    }

    new->stack = tmp_stack;
    origin->stack = NULL;
    origin->num_pieces = 0;
    // new->stack = tmp_stack;
}