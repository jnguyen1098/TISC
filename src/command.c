/**
 * @file    command.c
 * @brief   Command execution
 */

#include "TISC.h"

bool do_command(struct TISC *tisc)
{
    static bool traceflag  = false;
    static bool icountflag = false;
    int         stepcnt    = 0;
    int         i          = 0;
    int         printcnt   = 0;
    int         regNo      = 0;
    int         loc        = 0;

    do {
        printf("Enter command: ");
        if (fflush(stdout) != 0) {
            perror("fflush");
            exit(EXIT_FAILURE);
        }

        if (fgets(tisc->line_buf, (size_t)BUFSIZ, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        tisc->inCol = 0;
    }

    while (get_word(tisc) == 0);

    char cmd = tisc->word[0];
    switch (cmd) {
        case 't':
            traceflag = !traceflag;
            printf("Tracing now ");
            if (traceflag) {
                printf("on.\n");
            } else {
                printf("off.\n");
            }
            break;

        case 'h':
            printf("Commands are:\n");
            printf(
                "   s(tep <n>      "
                "Execute n (default 1) TM instructions\n");
            printf(
                "   g(o            "
                "Execute TM instructions until HALT\n");
            printf(
                "   r(egs          "
                "Print the contents of the registers\n");
            printf(
                "   i(Mem <b <n>>  "
                "Print n iMem locations starting at b\n");  // TODO(jason)
            printf(
                "   d(Mem <b <n>>  "
                "Print n data memory locations starting at b\n");
            printf(
                "   t(race         "
                "Toggle instruction trace\n");
            printf(
                "   p(rint         "
                "Toggle print of total instructions executed"
                " ('go' only)\n");
            printf(
                "   c(lear         "
                "Reset simulator for new execution of program\n");
            printf(
                "   h(elp          "
                "Cause this list of commands to be printed\n");
            printf(
                "   q(uit          "
                "Terminate the simulation\n");
            break;

        case 'p':
            icountflag = !icountflag;
            printf("Printing instruction count now ");
            if (icountflag) {
                printf("on.\n");
            } else {
                printf("off.\n");
            }
            break;

        case 's':
            stepcnt = 1;
            if (get_num(tisc)) {
                stepcnt = abs(tisc->num);
            }
            break;

        case 'g':
            stepcnt = 1;
            break;

        case 'r':
            for (i = 0; i < NO_REGS; i++) {
                printf("%1d: %4d    ", i, tisc->reg[i]);
                if (i % 4 == 3) {
                    printf("\n");
                }
            }
            break;

        case 'i':
            printcnt = 1;
            if (get_num(tisc)) {
                tisc->inst_itr = tisc->num;
                if (get_num(tisc)) {
                    printcnt = tisc->num;
                }
            }
            if ((tisc->curr_char = get_next_non_blank_char(tisc)) == '\0') {
                printf("Instruction locations?\n");
            } else {
                while ((tisc->inst_itr >= 0) && (tisc->inst_itr < IADDR_SIZE) &&
                       (printcnt > 0)) {
                    write_instruction(tisc, tisc->inst_itr);
                    tisc->inst_itr++;
                    printcnt--;
                }
            }
            break;

        case 'd':
            printcnt = 1;
            if (get_num(tisc)) {
                tisc->data_itr = tisc->num;
                if (get_num(tisc)) {
                    printcnt = tisc->num;
                }
            }
            if ((tisc->curr_char = get_next_non_blank_char(tisc)) == '\0') {
                printf("Data locations?\n");
            } else {
                while ((tisc->data_itr >= 0) && (tisc->data_itr < DADDR_SIZE) &&
                       (printcnt > 0)) {
                    printf("%5d: %5d\n", tisc->data_itr,
                           tisc->data_memory[tisc->data_itr]);
                    tisc->data_itr++;
                    printcnt--;
                }
            }
            break;

        case 'c':
            tisc->inst_itr = 0;
            tisc->data_itr = 0;
            stepcnt        = 0;
            for (regNo = 0; regNo < NO_REGS; regNo++) {
                tisc->reg[regNo] = 0;
            }
            tisc->data_memory[0] = DADDR_SIZE - 1;
            for (loc = 1; loc < DADDR_SIZE; loc++) {
                tisc->data_memory[loc] = 0;
            }
            break;

        case 'q':
            return false;

        default:
            fprintf(stderr, "Command %c unknown.\n", cmd);
            break;
    }
    enum step_result stepResult = srOKAY;
    if (stepcnt > 0) {
        if (cmd == 'g') {
            stepcnt = 0;
            while (stepResult == srOKAY) {
                tisc->inst_itr = tisc->reg[PC_REG];
                if (traceflag) {
                    write_instruction(tisc, tisc->inst_itr);
                }
                stepResult = step(tisc);
                stepcnt++;
            }
            if (icountflag) {
                printf("Number of instructions executed = %d\n", stepcnt);
            }
        } else {
            while ((stepcnt > 0) && (stepResult == srOKAY)) {
                tisc->inst_itr = tisc->reg[PC_REG];
                if (traceflag) {
                    write_instruction(tisc, tisc->inst_itr);
                }
                stepResult = step(tisc);
                stepcnt--;
            }
        }
        if (puts(stepResultTab[stepResult]) == EOF) {
            perror("puts");
            exit(EXIT_FAILURE);
        }
    }
    return true;
}
