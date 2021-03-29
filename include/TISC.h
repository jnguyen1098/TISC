/**
 * @file TISC.h
 * @author Jason Nguyen
 *
 * @mainpage
 * This file holds definitions to the functions used in TISC.
 * As such, it should be treated as the front-facing interface.
 *
 * @date March 2021
 * @brief TISC function signatures.
 */

#ifndef TISC_H
#define TISC_H

#include "TISC_defs.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TISC_DEFAULT                                                 \
    {                                                                \
        .inst_itr = 0, .data_itr = 0, .instruction_memory = {{0}},   \
        .data_memory = {0}, .reg = {0}, .line_buf = {0}, .inCol = 0, \
        .curr_char = 0, .word = {0}, .padding = {0}, .num = 0        \
    }

// TODO(jason) document
struct TISC {
    int inst_itr;
    int data_itr;

    struct instruction instruction_memory[IADDR_SIZE];
    int                data_memory[DADDR_SIZE];
    int                reg[NO_REGS];

    char line_buf[BUFSIZ];
    int  inCol;
    char curr_char;

    char word[WORD_SIZE];
    char padding[3];
    int  num;
};

// pre post param return see

/**
 * Consumes line input until current character is non-blank,
 * then returns the character to the user (or '\0' if EOF)
 *
 * @post    Line buffer iterator will either point to a non-
 *          blank character and sent it to the current char
 *          variable, or will stop at the NULL-terminator
 *
 * @return  the next non-blank charcter if it exists;
 *          '\0' otherwise.
 */
static char get_next_non_blank_char(struct TISC *tisc);

/**
 * Consumes the next character in the line buffer and returns
 * it to the user if it exists, otherwise it returns ' '.
 *
 * @post    The line buffer iterator will either point to a
 *          none-blank character or the buffer will be
 *          completely consumed and will point to a NULL-term.
 *
 * @return   The next character, or the ' ' space character.
 */
static char get_next_char(struct TISC *tisc);

/**
 * Emits an error message and then returns false.
 *
 * @param     msg   error to emit
 * @param line_no   error line number
 * @param inst_no   error instruction number
 */
static bool error(char *msg, int line_no, int inst_no);

/**
 * Skips input until first char after, setting current char to that
 *
 * @param   c The character to be skipped over in the input buffer
 * @return  whether the skip was successful. If the input buffer
 *          reaches EOF or there is no occurrence of char c in the
 *          input buffer, it returns false instead.
 * @post    input stream may be advanced forward
 */
static bool get_next_char_after(struct TISC *tisc, char c);

/**
 * Gets the next word from input buffer, which is defined as a
 * space-delimited group of letters, greedily consumed.
 *
 * @post    input buffer will likely be consumed normally
 * @return  length of the consumed word. 0 if nonexistence
 */
static int get_word(struct TISC *tisc);

/**
 * Consumes a number from the input and returns it as an int
 *
 * @param tisc  the machine to get the number from
 * @return      whether the parsed object is truly a num
 */
static bool get_num(struct TISC *tisc);

/**
 * Emits an assembly instruction based on the location in the .text
 *
 * @pre         loc is a valid, accessible index for the inst array
 * @param tisc  TISC computer to read the data from
 * @param loc   location in the inst array of the opcode to write
 * @post        stdout has output emitted from TISC
 */
static void write_instruction(struct TISC *tisc, int loc);

#endif
