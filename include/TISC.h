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

/**
 * Initializes a TISC machine's data to default values
 *
 * @pre         tisc is not NULL and is a valid pointer
 * @param tisc  the TISC machine to initialize
 * @post        TISC machine values are initialized
 * @return      true if success, false otherwose
 *
 */
bool init_TISC(struct TISC *tisc);

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
char get_next_non_blank_char(struct TISC *tisc);

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
char get_next_char(struct TISC *tisc);

/**
 * Skips input until first char after, setting current char to that
 *
 * @param   c   The character to be skipped over in the input buffer
 *
 * @return      whether the skip was successful. If the input buffer
 *              reaches EOF or there is no occurrence of char c in the
 *              input buffer, it returns false instead.
 *
 * @post        input stream may be advanced forward
 */
bool get_next_char_after(struct TISC *tisc, char c);

/**
 * Gets the next word from input buffer, which is defined as a
 * space-delimited group of letters, greedily consumed.
 *
 * @post    input buffer will likely be consumed normally
 * @return  length of the consumed word. 0 if nonexistence
 */
int get_word(struct TISC *tisc);

/**
 * Consumes a number from the input and returns it as an int
 *
 * @param tisc  the machine to get the number from
 * @return      whether the parsed object is truly a num
 */
bool get_num(struct TISC *tisc);

/**
 * Emits an error message and then returns false.
 *
 * @param     msg   error to emit
 * @param line_no   error line number
 * @param inst_no   error instruction number
 */
bool error(char *msg, int line_no, int inst_no);

/**
 * Emits an assembly instruction based on the location in the .text
 *
 * @pre         loc is a valid, accessible index for the inst array
 * @param tisc  TISC computer to read the data from
 * @param loc   location in the inst array of the opcode to write
 * @post        stdout has output emitted from TISC
 */
void write_instruction(struct TISC *tisc, int loc);

/**
 * Attempts to read the instructions out of a file
 *
 * @pre         tisc is a valid TISC computer
 * @param tisc  TISC computer to read the data from
 * @param pgm   FILE pointer to the program
 * @return      whether reading the file was successful
 * @post        pgm will be exhausted and tisc will have lines
 */
bool read_program(struct TISC *tisc, FILE *pgm);

/**
 * Step through a single instruction of a given program
 *
 * @pre         program is loaded successfully in tisc
 * @param tisc  TISC computer to step through
 * @return      an enum step_result signifying status
 * @post        tisc's instruction buffer will be advanced
 */
enum step_result step(struct TISC *tisc);

/**
 * Execute a TISC interactive CLI command from the user
 *
 * @pre         user enters a command interactive
 * @param tisc  TISC computer to run command with
 * @return      whether to continue asking for input
 * @post        action is taken or program main loops ends
 */
bool do_command(struct TISC *tisc);

#endif
