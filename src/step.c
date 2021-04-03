/**
 * @file    step.c
 * @brief   Instruction stepping functions
 */

#include "TISC.h"

enum step_result step(struct TISC *tisc)
{
    bool ok = false;
    int  r  = 0;
    int  s  = 0;
    int  t  = 0;
    int  m  = 0;

    int program_counter = tisc->reg[PC_REG];

    if (program_counter < 0) {
        return STEP_ILLEGAL_PROGRAM_COUNTER_INDEX;
    }

    if (program_counter > IADDR_SIZE) {
        return STEP_ILLEGAL_PROGRAM_COUNTER_INDEX;
    }

    tisc->reg[PC_REG]++;
    struct instruction curr_instruction =
        tisc->instruction_memory[program_counter];

    switch (get_op_class[curr_instruction.iop]) {
        case opclRR:
            r = curr_instruction.iarg1;
            s = curr_instruction.iarg2;
            t = curr_instruction.iarg3;
            break;

        case opclRM:
            r = curr_instruction.iarg1;
            s = curr_instruction.iarg3;
            m = curr_instruction.iarg2 + tisc->reg[s];
            if (m < 0 || m > DADDR_SIZE) {
                return STEP_ILLEGAL_DATA_MEMORY_INDEX;
            }
            break;

        case opclRA:
            r = curr_instruction.iarg1;
            s = curr_instruction.iarg3;
            m = curr_instruction.iarg2 + tisc->reg[s];
            break;
    }

    switch (curr_instruction.iop) {
        /* RR */
        case opHALT:
            printf("HALT: %1d,%1d,%1d\n", r, s, t);
            return srHALT;

        case opIN:
            do {
                printf("Enter value for IN instruction: ");
                if (fflush(stdout) != 0) {
                    perror("fflush");
                    exit(EXIT_FAILURE);
                }
                if (fgets(tisc->line_buf, (size_t)BUFSIZ, stdin) == NULL) {
                    perror("fgets");
                    exit(EXIT_FAILURE);
                }
                tisc->inCol = 0;
                ok          = get_num(tisc);
                if (!ok) {
                    fprintf(stderr, "Illegal value\n");
                } else {
                    tisc->reg[r] = tisc->num;
                }
            } while (!ok);
            break;

        case opOUT:
            printf("OUT instruction prints: %d\n", tisc->reg[r]);
            break;

        case opADD:
            tisc->reg[r] = tisc->reg[s] + tisc->reg[t];
            break;

        case opSUB:
            tisc->reg[r] = tisc->reg[s] - tisc->reg[t];
            break;

        case opMUL:
            tisc->reg[r] = tisc->reg[s] * tisc->reg[t];
            break;

        case opDIV:
            if (tisc->reg[t] != 0) {
                tisc->reg[r] = tisc->reg[s] / tisc->reg[t];
            } else {
                return srZERODIVIDE;
            }
            break;

            /* RM */
        case opLD:
            tisc->reg[r] = tisc->data_memory[m];
            break;

        case opST:
            tisc->data_memory[m] = tisc->reg[r];
            break;

            /* RA */
        case opLDA:
            tisc->reg[r] = m;
            break;

        case opLDC:
            tisc->reg[r] = curr_instruction.iarg2;
            break;

        case opJLT:
            if (tisc->reg[r] < 0) {
                tisc->reg[PC_REG] = m;
            }
            break;

        case opJLE:
            if (tisc->reg[r] <= 0) {
                tisc->reg[PC_REG] = m;
            }
            break;

        case opJGT:
            if (tisc->reg[r] > 0) {
                tisc->reg[PC_REG] = m;
            }
            break;

        case opJGE:
            if (tisc->reg[r] >= 0) {
                tisc->reg[PC_REG] = m;
            }
            break;

        case opJEQ:
            if (tisc->reg[r] == 0) {
                tisc->reg[PC_REG] = m;
            }
            break;

        case opJNE:
            if (tisc->reg[r] != 0) {
                tisc->reg[PC_REG] = m;
            }
            break;

        case opRRLim:
        case opRMLim:
        case opRALim:
            fprintf(stderr, "Placeholder/limit instructions used. Aborting\n");
            exit(EXIT_FAILURE);
    }
    return srOKAY;
}
