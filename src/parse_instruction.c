/**
 * @file    parse_instruction.c
 * @brief   Instruction parsing
 */

#include "TISC.h"

#include <string.h>

bool read_program(struct TISC *tisc, FILE *pgm)
{
    int arg1   = 0;
    int arg2   = 0;
    int arg3   = 0;
    int loc    = 0;
    int lineNo = 0;

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
