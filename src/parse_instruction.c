/**
 * @file    parse_instruction.c
 * @brief   Instruction parsing
 */

#include "TISC.h"

#include <string.h>

bool init_TISC(struct TISC *tisc); // TODO(jason) should this be in a header?
// TODO(jason) should this be in its own file? 

bool init_TISC(struct TISC *tisc)
{
    // TODO(jason) should these be commented? or functionized?
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

    // lmao
    return true;
}

bool read_instructions(struct TISC *tisc, FILE *pgm)
{
    int arg1   = 0;
    int arg2   = 0;
    int arg3   = 0;
    int loc    = 0;
    int lineNo = 0;

    if (!init_TISC(tisc)) {
        return error("Could not initialize TISC in read_instructions()", 0, 0);
    }

    while (fgets(tisc->line_buf, (size_t)BUFSIZ, pgm)) {
        tisc->inCol = 0;
        lineNo++;
        tisc->line_buf[strcspn(tisc->line_buf, "\r\n")] = '\0';
        if ((tisc->curr_char = get_next_non_blank_char(tisc)) != '\0' &&
            (tisc->line_buf[tisc->inCol] != '*')) {
            if (!get_num(tisc)) {
                return error("Bad location", lineNo, -1);
            }
            loc = tisc->num;
            if (loc > IADDR_SIZE) {
                return error("Location too large", lineNo, loc);
            }
            if (!get_next_char_after(tisc, ':')) {
                return error("Missing colon", lineNo, loc);
            }
            if (get_word(tisc) == 0) {
                return error("Missing opcode", lineNo, loc);
            }
            enum op_code op = opHALT;
            while ((op < opRALim) &&
                   (strncmp(opCodeTab[op], tisc->word, 4) != 0)) {
                op++;
            }
            if (strncmp(opCodeTab[op], tisc->word, 4) != 0) {
                return error("Illegal opcode", lineNo, loc);
            }

            switch (get_op_class[op]) {
                case opclRR:
                    if ((!get_num(tisc)) || (tisc->num < 0) ||
                        (tisc->num >= NO_REGS)) {
                        return error("Bad first register", lineNo, loc);
                    }
                    arg1 = tisc->num;
                    if (!get_next_char_after(tisc, ',')) {
                        return error("Missing comma", lineNo, loc);
                    }
                    if ((!get_num(tisc)) || (tisc->num < 0) ||
                        (tisc->num >= NO_REGS)) {
                        return error("Bad second register", lineNo, loc);
                    }
                    arg2 = tisc->num;
                    if (!get_next_char_after(tisc, ',')) {
                        return error("Missing comma", lineNo, loc);
                    }
                    if ((!get_num(tisc)) || (tisc->num < 0) ||
                        (tisc->num >= NO_REGS)) {
                        return error("Bad third register", lineNo, loc);
                    }
                    arg3 = tisc->num;
                    break;

                case opclRM:
                case opclRA:
                    if ((!get_num(tisc)) || (tisc->num < 0) ||
                        (tisc->num >= NO_REGS)) {
                        return error("Bad first register", lineNo, loc);
                    }
                    arg1 = tisc->num;
                    if (!get_next_char_after(tisc, ',')) {
                        return error("Missing comma", lineNo, loc);
                    }
                    if (!get_num(tisc)) {
                        return error("Bad displacement", lineNo, loc);
                    }
                    arg2 = tisc->num;
                    if (!get_next_char_after(tisc, '(') &&
                        !get_next_char_after(tisc, ',')) {
                        return error("Missing LParen", lineNo, loc);
                    }
                    if ((!get_num(tisc)) || (tisc->num < 0) ||
                        (tisc->num >= NO_REGS)) {
                        return error("Bad second register", lineNo, loc);
                    }
                    arg3 = tisc->num;
                    break;
            }
            tisc->instruction_memory[loc].iop   = op;
            tisc->instruction_memory[loc].iarg1 = arg1;
            tisc->instruction_memory[loc].iarg2 = arg2;
            tisc->instruction_memory[loc].iarg3 = arg3;
        }
    }
    return true;
}
