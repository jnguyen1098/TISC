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
char get_next_non_blank_char(void);

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
char get_next_char(void);

/**
 * Emits an error message and then returns false.
 *
 * @param     msg   error to emit
 * @param line_no   error line number
 * @param inst_no   error instruction number
 */
bool error(char *msg, int line_no, int inst_no);

#endif
