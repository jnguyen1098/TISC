/**
 * @brief Success
 */
/****************************************************/
/* @file: TISC.c                                    */
/* The TM ("Tiny Machine") computer                 */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "TISC.h"

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void write_instruction(struct TISC *tisc, int loc)
{ 
    printf("%5d: ", loc);
    if (loc >= 0 && loc < IADDR_SIZE) { 
        printf("%6s%3d,", opCodeTab[tisc->instruction_memory[loc].iop], tisc->instruction_memory[loc].iarg1);
        switch (get_op_class[tisc->instruction_memory[loc].iop]) { 
            case opclRR:
                printf("%1d,%1d", tisc->instruction_memory[loc].iarg2, tisc->instruction_memory[loc].iarg3);
                break;
            case opclRM:
            case opclRA:
                printf("%3d(%1d)", tisc->instruction_memory[loc].iarg2, tisc->instruction_memory[loc].iarg3);
                break;
        }
        printf ("\n");
    }
}

char get_next_char(struct TISC *tisc)
{ 
    return tisc->line_buf[++tisc->inCol];
}

char get_next_non_blank_char(struct TISC *tisc)
{ 
    // TODO: this function has to die in the global exodus
    while (tisc->line_buf[tisc->inCol] == ' ') {
        tisc->inCol++;
    }
    return tisc->line_buf[tisc->inCol];
}

/********************************************/
int get_num(struct TISC *tisc)
{ 
    int is_num = false;
    tisc->num = 0;
    do { 
        int sign = 1;
        while ( (tisc->curr_char = get_next_non_blank_char(tisc)) != '\0' && ((tisc->curr_char == '+') || (tisc->curr_char == '-')) )
        { 
            is_num = false;
            if (tisc->curr_char == '-') {
                sign = -sign;
            }
            tisc->curr_char = get_next_char(tisc);
        }
        int term = 0;
        tisc->curr_char = get_next_non_blank_char(tisc);
        while (isdigit(tisc->curr_char))
        { 
            is_num = true;
            term = term * 10 + (int)(tisc->curr_char - '0');
            tisc->curr_char = get_next_char(tisc);
        }
        tisc->num = tisc->num + (term * sign) ;
    } while ( (tisc->curr_char = get_next_non_blank_char(tisc)) != '\0'  && ((tisc->curr_char == '+') || (tisc->curr_char == '-')) ) ;
    return is_num;
}

int get_word(struct TISC *tisc)
{ 
    int length = 0;
    if ((tisc->curr_char = get_next_non_blank_char(tisc)))
    { 
        while (isalnum(tisc->curr_char))
        { 
            if (length < WORD_SIZE - 1) {
                tisc->word[length++] = tisc->curr_char;
            }
            tisc->curr_char = get_next_char(tisc);
        }
        tisc->word[length] = '\0';
    }
    return length;
}

bool get_next_char_after(struct TISC *tisc, char c)
{
    if ((tisc->curr_char = get_next_non_blank_char(tisc)) && (tisc->curr_char == c) )
    { 
        tisc->curr_char = get_next_char(tisc);
        return true;
    }
    return false;
}

bool error(char *msg, int line_no, int inst_no)
{ 
    fprintf(stderr, "Line %d", line_no);
    if (inst_no >= 0) fprintf(stderr, " (Instruction %d)", inst_no);
    fprintf(stderr, "   %s\n", msg);
    return false;
}

int read_instructions(struct TISC *tisc, FILE *pgm)
{ 
    enum op_code op;
    int arg1, arg2, arg3;
    int loc, regNo, lineNo;
    for (regNo = 0 ; regNo < NO_REGS ; regNo++)
        tisc->reg[regNo] = 0 ;
    tisc->data_memory[0] = DADDR_SIZE - 1 ;
    for (loc = 1 ; loc < DADDR_SIZE ; loc++)
        tisc->data_memory[loc] = 0 ;
    for (loc = 0 ; loc < IADDR_SIZE ; loc++)
    { 
        tisc->instruction_memory[loc].iop = opHALT ;
        tisc->instruction_memory[loc].iarg1 = 0 ;
        tisc->instruction_memory[loc].iarg2 = 0 ;
        tisc->instruction_memory[loc].iarg3 = 0 ;
    }
    lineNo = 0 ;
    while (fgets(tisc->line_buf, BUFSIZ, pgm))
    { 
        tisc->inCol = 0 ; 
        lineNo++;
        tisc->line_buf[strcspn(tisc->line_buf, "\r\n")] = '\0';
        if ( (tisc->curr_char = get_next_non_blank_char(tisc)) && (tisc->line_buf[tisc->inCol] != '*') )
        { 
            if (!get_num(tisc))
                return error("Bad location", lineNo,-1);
            loc = tisc->num;
            if (loc > IADDR_SIZE)
                return error("Location too large",lineNo,loc);
            if (!get_next_char_after(tisc, ':'))
                return error("Missing colon", lineNo,loc);
            if (!get_word(tisc))
                return error("Missing opcode", lineNo,loc);
            op = opHALT ;
            while ((op < opRALim)
                    && (strncmp(opCodeTab[op], tisc->word, 4) != 0) )
                op++ ;
            if (strncmp(opCodeTab[op], tisc->word, 4) != 0)
                return error("Illegal opcode", lineNo,loc);
            switch (get_op_class[op])
            { 
                case opclRR :
                    /***********************************/
                    if ( (!get_num(tisc)) || (tisc->num < 0) || (tisc->num >= NO_REGS) )
                        return error("Bad first register", lineNo,loc);
                    arg1 = tisc->num;
                    if ( !get_next_char_after(tisc, ','))
                        return error("Missing comma", lineNo, loc);
                    if ( (!get_num(tisc)) || (tisc->num < 0) || (tisc->num >= NO_REGS) )
                        return error("Bad second register", lineNo, loc);
                    arg2 = tisc->num;
                    if ( !get_next_char_after(tisc, ',')) 
                        return error("Missing comma", lineNo,loc);
                    if ( (!get_num(tisc)) || (tisc->num < 0) || (tisc->num >= NO_REGS) )
                        return error("Bad third register", lineNo,loc);
                    arg3 = tisc->num;
                    break;

                case opclRM :
                case opclRA :
                    /***********************************/
                    if ( (!get_num(tisc)) || (tisc->num < 0) || (tisc->num >= NO_REGS) )
                        return error("Bad first register", lineNo,loc);
                    arg1 = tisc->num;
                    if ( !get_next_char_after(tisc, ','))
                        return error("Missing comma", lineNo,loc);
                    if (!get_num(tisc))
                        return error("Bad displacement", lineNo,loc);
                    arg2 = tisc->num;
                    if ( !get_next_char_after(tisc, '(') && !get_next_char_after(tisc, ',') )
                        return error("Missing LParen", lineNo,loc);
                    if ( (!get_num(tisc)) || (tisc->num < 0) || (tisc->num >= NO_REGS))
                        return error("Bad second register", lineNo,loc);
                    arg3 = tisc->num;
                    break;
            }
            tisc->instruction_memory[loc].iop = op;
            tisc->instruction_memory[loc].iarg1 = arg1;
            tisc->instruction_memory[loc].iarg2 = arg2;
            tisc->instruction_memory[loc].iarg3 = arg3;
        }
    }
    return true;
}


enum step_result step(struct TISC *tisc)
{ 
    int r, s, t, m;
    int ok;

    int program_counter = tisc->reg[PC_REG];

    if (program_counter < 0 || program_counter > IADDR_SIZE) {
        return STEP_ILLEGAL_PROGRAM_COUNTER_INDEX;
    }

    tisc->reg[PC_REG]++;
    struct instruction curr_instruction = tisc->instruction_memory[program_counter];

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

    switch ( curr_instruction.iop)
    { 
        /* RR instructions */
        case opHALT :
            /***********************************/
            printf("HALT: %1d,%1d,%1d\n",r,s,t);
            return srHALT ;
            /* break; */

        case opIN :
            /***********************************/
            do
            { 
                printf("Enter value for IN instruction: ") ;
                fflush (stdout);
                fgets(tisc->line_buf, BUFSIZ, stdin);
                tisc->inCol = 0;
                ok = get_num(tisc);
                if ( ! ok ) fprintf(stderr, "Illegal value\n");
                else tisc->reg[r] = tisc->num;
            }
            while (! ok);
            break;

        case opOUT :  
            printf ("OUT instruction prints: %d\n", tisc->reg[r] ) ;
            break;
        case opADD :  tisc->reg[r] = tisc->reg[s] + tisc->reg[t] ;  break;
        case opSUB :  tisc->reg[r] = tisc->reg[s] - tisc->reg[t] ;  break;
        case opMUL :  tisc->reg[r] = tisc->reg[s] * tisc->reg[t] ;  break;

        case opDIV :
                      /***********************************/
                      if ( tisc->reg[t] != 0 ) tisc->reg[r] = tisc->reg[s] / tisc->reg[t];
                      else return srZERODIVIDE ;
                      break;

                      /*************** RM instructions ********************/
        case opLD :    tisc->reg[r] = tisc->data_memory[m] ;  break;
        case opST :    tisc->data_memory[m] = tisc->reg[r] ;  break;

                       /*************** RA instructions ********************/
        case opLDA :    tisc->reg[r] = m ; break;
        case opLDC :    tisc->reg[r] = curr_instruction.iarg2 ;   break;
        case opJLT :    if ( tisc->reg[r] <  0 ) tisc->reg[PC_REG] = m ; break;
        case opJLE :    if ( tisc->reg[r] <=  0 ) tisc->reg[PC_REG] = m ; break;
        case opJGT :    if ( tisc->reg[r] >  0 ) tisc->reg[PC_REG] = m ; break;
        case opJGE :    if ( tisc->reg[r] >=  0 ) tisc->reg[PC_REG] = m ; break;
        case opJEQ :    if ( tisc->reg[r] == 0 ) tisc->reg[PC_REG] = m ; break;
        case opJNE :    if ( tisc->reg[r] != 0 ) tisc->reg[PC_REG] = m ; break;

                            /* end of legal instructions */
    }
    return srOKAY ;
}

/********************************************/
int doCommand (struct TISC *tisc)
{ 
    static int traceflag = false;
    static int icountflag = false;
    char cmd;
    int stepcnt=0, i;
    int printcnt;
    int stepResult;
    int regNo, loc;
    do
    { 
        printf ("Enter command: ");
        fflush (stdout);
        fgets(tisc->line_buf, BUFSIZ, stdin);
        tisc->inCol = 0;
    }
    while (!get_word(tisc))
        ;

    cmd = tisc->word[0];
    switch ( cmd )
    { 
        case 't' :
            /***********************************/
            traceflag = ! traceflag ;
            printf("Tracing now ");
            if ( traceflag ) printf("on.\n"); else printf("off.\n");
            break;

        case 'h' :
            /***********************************/
            printf("Commands are:\n");
            printf("   s(tep <n>      "\
                    "Execute n (default 1) TM instructions\n");
            printf("   g(o            "\
                    "Execute TM instructions until HALT\n");
            printf("   r(egs          "\
                    "Print the contents of the registers\n");
            printf("   i(Mem <b <n>>  "\
                        "Print n iMem locations starting at b\n"); // TODO: change iMem
            printf("   d(Mem <b <n>>  "\
                    "Print n data memory locations starting at b\n");
            printf("   t(race         "\
                    "Toggle instruction trace\n");
            printf("   p(rint         "\
                    "Toggle print of total instructions executed"\
                    " ('go' only)\n");
            printf("   c(lear         "\
                    "Reset simulator for new execution of program\n");
            printf("   h(elp          "\
                    "Cause this list of commands to be printed\n");
            printf("   q(uit          "\
                    "Terminate the simulation\n");
            break;

        case 'p' :
            /***********************************/
            icountflag = ! icountflag ;
            printf("Printing instruction count now ");
            if ( icountflag ) printf("on.\n"); else printf("off.\n");
            break;

        case 's' :
            /***********************************/
            stepcnt = 1;
            if (get_num(tisc))  stepcnt = abs(tisc->num);
            break;

        case 'g' :   stepcnt = 1 ;     break;

        case 'r' :
                     /***********************************/
                     for (i = 0; i < NO_REGS; i++)
                     { 
                         printf("%1d: %4d    ", i, tisc->reg[i]);
                         if ( (i % 4) == 3 ) printf ("\n");
                     }
                     break;

        case 'i' :
                     /***********************************/
                     printcnt = 1 ;
                     if (get_num(tisc))
                     { 
                         tisc->inst_itr = tisc->num;
                         if (get_num(tisc)) printcnt = tisc->num;
                     }
                     if (!(tisc->curr_char = get_next_non_blank_char(tisc)))
                         printf ("Instruction locations?\n");
                     else
                     { 
                         while ((tisc->inst_itr >= 0) && (tisc->inst_itr < IADDR_SIZE)
                                 && (printcnt > 0) )
                         { 
                             write_instruction(tisc, tisc->inst_itr);
                             tisc->inst_itr++;
                             printcnt--;
                         }
                     }
                     break;

        case 'd' :
                     /***********************************/
                     printcnt = 1 ;
                     if (get_num(tisc))
                     { 
                         tisc->data_itr = tisc->num;
                         if (get_num(tisc)) printcnt = tisc->num;
                     }
                     if (!(tisc->curr_char = get_next_non_blank_char(tisc)))
                         printf("Data locations?\n");
                     else
                     { 
                         while ((tisc->data_itr >= 0) && (tisc->data_itr < DADDR_SIZE)
                                 && (printcnt > 0))
                         { 
                             printf("%5d: %5d\n", tisc->data_itr, tisc->data_memory[tisc->data_itr]);
                             tisc->data_itr++;
                             printcnt--;
                         }
                     }
                     break;

        case 'c' :
                     /***********************************/
                     tisc->inst_itr = 0;
                     tisc->data_itr = 0;
                     stepcnt = 0;
                     for (regNo = 0;  regNo < NO_REGS; regNo++)
                         tisc->reg[regNo] = 0;
                     tisc->data_memory[0] = DADDR_SIZE - 1;
                     for (loc = 1 ; loc < DADDR_SIZE; loc++)
                         tisc->data_memory[loc] = 0 ;
                     break;

        case 'q' : return false;  /* break; */

        default : fprintf(stderr, "Command %c unknown.\n", cmd); break;
    }  /* case */
    stepResult = srOKAY;
    if ( stepcnt > 0 )
    { 
        if ( cmd == 'g' )
        { 
            stepcnt = 0;
            while (stepResult == srOKAY)
            { 
                tisc->inst_itr = tisc->reg[PC_REG] ;
                if (traceflag) write_instruction(tisc, tisc->inst_itr) ;
                stepResult = step(tisc);
                stepcnt++;
            }
            if ( icountflag )
                printf("Number of instructions executed = %d\n",stepcnt);
        }
        else
        {
            while ((stepcnt > 0) && (stepResult == srOKAY))
            {
                tisc->inst_itr = tisc->reg[PC_REG] ;
                if (traceflag) write_instruction(tisc, tisc->inst_itr) ;
                stepResult = step(tisc);
                stepcnt--;
            }
        }
        puts(stepResultTab[stepResult]);
    }
    return true;
} /* doCommand */

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct TISC tisc = { 0 };
    memset(&tisc, 0, sizeof(struct TISC));

    FILE *program_text;
    if (!(program_text = fopen(argv[1], "r"))) {
        perror("TISC");
        exit(EXIT_FAILURE);
    }

    /* read the program */
    if (!read_instructions(&tisc, program_text)) {
        fprintf(stderr, "Could not read read %s. Exiting\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* switch input file to terminal */
    /* reset( input ); */
    /* read-eval-print */
    printf("TM  simulation (enter h for help)...\n");

    while (doCommand(&tisc))
        ;

    printf("Simulation done.\n");

    fclose(program_text);
    return 0;
}
