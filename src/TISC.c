/**
 * @file    file.c
 * @brief   File parsing functions
 */

#include "TISC.h"

#include <ctype.h>

bool init_TISC(struct TISC *tisc)
{
    if (tisc == NULL) {
        return error("NULL TISC passed to init_tisc()", 0, 0);
    }

    // initialize registers
    for (int i = 0; i < NO_REGS; i++) {
        tisc->reg[i] = 0;
    }

    // first data address is written
    tisc->data_memory[0] = DADDR_SIZE - 1;

    // initialize rest of data address
    for (int i = 1; i < DADDR_SIZE; i++) {
        tisc->data_memory[i] = 0;
    }

    // initialize all instructions to nul
    for (int i = 0; i < IADDR_SIZE; i++) {
        tisc->instruction_memory[i].iop   = opHALT;
        tisc->instruction_memory[i].iarg1 = 0;
        tisc->instruction_memory[i].iarg2 = 0;
        tisc->instruction_memory[i].iarg3 = 0;
    }

    return true;
}

char get_next_non_blank_char(struct TISC *tisc)
{
    // TODO(jason): this function has to die in the global exodus
    while (tisc->line_buf[tisc->inCol] == ' ') {
        tisc->inCol++;
    }
    return tisc->line_buf[tisc->inCol];
}

char get_next_char(struct TISC *tisc) { return tisc->line_buf[++tisc->inCol]; }

bool get_next_char_after(struct TISC *tisc, char c)
{
    if ((tisc->curr_char = get_next_non_blank_char(tisc)) != '\0' &&
        (tisc->curr_char == c)) {
        tisc->curr_char = get_next_char(tisc);
        return true;
    }
    return false;
}

int get_word(struct TISC *tisc)
{
    int length = 0;
    if ((tisc->curr_char = get_next_non_blank_char(tisc)) != '\0') {
        while (isalnum(tisc->curr_char)) {
            if (length < WORD_SIZE - 1) {
                tisc->word[length++] = tisc->curr_char;
            } else {
                fprintf(stderr, "Word is too big (%d, limit %d)\n", length,
                        WORD_SIZE);
                fprintf(stderr, "TODO: should this be a fatal error?\n");
            }
            tisc->curr_char = get_next_char(tisc);
        }
        tisc->word[length] = '\0';
    }
    return length;
}

bool get_num(struct TISC *tisc)
{
    // TODO(jason) solve this int vs bool confusion
    const int TEN    = 10;
    bool      is_num = false;
    tisc->num        = 0;
    do {
        int sign = 1;
        while ((tisc->curr_char = get_next_non_blank_char(tisc)) != '\0' &&
               ((tisc->curr_char == '+') || (tisc->curr_char == '-'))) {
            is_num = true;
            if (tisc->curr_char == '-') {
                sign = -sign;
            }
            tisc->curr_char = get_next_char(tisc);
        }
        int term        = 0;
        tisc->curr_char = get_next_non_blank_char(tisc);
        while (isdigit(tisc->curr_char)) {
            is_num          = true;
            term            = term * TEN + (tisc->curr_char - '0');
            tisc->curr_char = get_next_char(tisc);
        }
        tisc->num = tisc->num + (term * sign);
    } while ((tisc->curr_char = get_next_non_blank_char(tisc)) != '\0' &&
             ((tisc->curr_char == '+') || (tisc->curr_char == '-')));
    return is_num;
}
