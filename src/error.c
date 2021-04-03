/**
 * @brief   Error handling
 * @file    error.c
 */

#include "TISC.h"

#include <stdio.h>
#include <stdbool.h>

bool error(char *msg, int line_no, int inst_no)
{
    fprintf(stderr, "Line %d", line_no);
    if (inst_no >= 0) {
        fprintf(stderr, " (Instruction %d)", inst_no);
    }
    fprintf(stderr, "   %s\n", msg);
    return false;
}
