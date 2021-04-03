/**
 * @file    write_instruction.c
 * @brief   Functions for writing instructions.
 */

#include "TISC.h"

void write_instruction(struct TISC *tisc, int loc)
{
    printf("%5d: ", loc);
    if (loc >= 0 && loc < IADDR_SIZE) {
        printf("%6s%3d,", opCodeTab[tisc->instruction_memory[loc].iop],
               tisc->instruction_memory[loc].iarg1);
        switch (get_op_class[tisc->instruction_memory[loc].iop]) {
            case opclRR:
                printf("%1d,%1d", tisc->instruction_memory[loc].iarg2,
                       tisc->instruction_memory[loc].iarg3);
                break;
            case opclRM:
            case opclRA:
                printf("%3d(%1d)", tisc->instruction_memory[loc].iarg2,
                       tisc->instruction_memory[loc].iarg3);
                break;
        }
        printf("\n");
    } else {
        // TODO(Jason): test this branch
        fprintf(stderr, "Called write_instruction(..., %d) with %d limit\n",
                loc, IADDR_SIZE);
        fprintf(stderr, "TODO(jason) should this just kill the program?\n");
    }
}
