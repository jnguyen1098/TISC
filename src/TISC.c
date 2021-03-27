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

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/** Temporary iterator for iMem. TODO: counter or actual instruction? */
int inst_itr = 0;

/** Temporary iterator for data_memory when using `d` */
int data_itr = 0;

int traceflag = false;
int icountflag = false;

struct instruction iMem[IADDR_SIZE];
int data_memory[DADDR_SIZE];
int reg[NO_REGS];

/** Current line buffer. */
char line_buf[BUFSIZ];
int buf_len;

/** Not the current char, but a text column iterator for input. */
int inCol; // TODO: refactor this out

int num;
char word[WORDSIZE] ;
char curr_char; // TODO: refactor this global variable
int done  ;

/********************************************/
int opClass( int c )
{ 
    if      ( c <= opRRLim) return ( opclRR );
    else if ( c <= opRMLim) return ( opclRM );
    else                    return ( opclRA );
} /* opClass */

/********************************************/
void writeInstruction ( int loc )
{ 
    printf( "%5d: ", loc) ;
    if ( (loc >= 0) && (loc < IADDR_SIZE) )
    { 
        printf("%6s%3d,", opCodeTab[iMem[loc].iop], iMem[loc].iarg1);
        switch ( opClass(iMem[loc].iop) )
        { 
            case opclRR: printf("%1d,%1d", iMem[loc].iarg2, iMem[loc].iarg3);
                         break;
            case opclRM:
            case opclRA: printf("%3d(%1d)", iMem[loc].iarg2, iMem[loc].iarg3);
                         break;
        }
        printf ("\n") ;
    }
} /* writeInstruction */

/********************************************/
void getCh (void)
{ 
    curr_char = line_buf[++inCol] ? line_buf[inCol] : ' ';
}

/********************************************/
bool nonBlank (void)
{ 
    while (line_buf[inCol] == ' ')
        inCol++;

    if (line_buf[inCol])
    { 
        curr_char = line_buf[inCol];
        return true; 
    }
    else
    { 
        curr_char = ' ' ;
        return false;
    }
}

/********************************************/
int getNum (void)
{ 
    int sign;
    int term;
    bool temp = false;
    num = 0;
    do
    { 
        sign = 1;
        while ( nonBlank() && ((curr_char == '+') || (curr_char == '-')) )
        { 
            temp = false;
            if (curr_char == '-')  sign = - sign ;
            getCh();
        }
        term = 0 ;
        nonBlank();
        while (isdigit(curr_char))
        { 
            temp = true;
            term = term * 10 + ( curr_char - '0' ) ;
            getCh();
        }
        num = num + (term * sign) ;
    } while ( (nonBlank()) && ((curr_char == '+') || (curr_char == '-')) ) ;
    return temp;
}

/********************************************/
int getWord (void)
{ 
    int temp = false;
    int length = 0;
    if (nonBlank ())
    { 
        while (isalnum(curr_char))
        { 
            if (length < WORDSIZE-1) word [length++] =  curr_char;
            getCh() ;
        }
        word[length] = '\0';
        temp = (length != 0);
    }
    return temp;
} /* getWord */

/********************************************/
int skipCh ( char c  )
{

    bool temp = false;
    if ( nonBlank() && (curr_char == c) )
    { 
        getCh();
        temp = true;
    }
    return temp;
} /* skipCh */

/********************************************/
int atEOL(void)
{ 
    return ( ! nonBlank ());
} /* atEOL */

/********************************************/
int error(char *msg, int lineNo, int instNo)
{ 
    fprintf(stderr, "Line %d", lineNo);
    if (instNo >= 0) fprintf(stderr, " (Instruction %d)", instNo);
    fprintf(stderr, "   %s\n", msg);
    return false;
}

/********************************************/
int readInstructions (FILE *pgm)
{ 
    OPCODE op;
    int arg1, arg2, arg3;
    int loc, regNo, lineNo;
    for (regNo = 0 ; regNo < NO_REGS ; regNo++)
        reg[regNo] = 0 ;
    data_memory[0] = DADDR_SIZE - 1 ;
    for (loc = 1 ; loc < DADDR_SIZE ; loc++)
        data_memory[loc] = 0 ;
    for (loc = 0 ; loc < IADDR_SIZE ; loc++)
    { 
        iMem[loc].iop = opHALT ;
        iMem[loc].iarg1 = 0 ;
        iMem[loc].iarg2 = 0 ;
        iMem[loc].iarg3 = 0 ;
    }
    lineNo = 0 ;
    while (fgets(line_buf, BUFSIZ, pgm))
    { 
        inCol = 0 ; 
        lineNo++;
        buf_len = strlen(line_buf) - 1;
        if (line_buf[buf_len]=='\n') line_buf[buf_len] = '\0';
        else line_buf[++buf_len] = '\0';
        if ( (nonBlank()) && (line_buf[inCol] != '*') )
        { 
            if (! getNum())
                return error("Bad location", lineNo,-1);
            loc = num;
            if (loc > IADDR_SIZE)
                return error("Location too large",lineNo,loc);
            if (! skipCh(':'))
                return error("Missing colon", lineNo,loc);
            if (! getWord ())
                return error("Missing opcode", lineNo,loc);
            op = opHALT ;
            while ((op < opRALim)
                    && (strncmp(opCodeTab[op], word, 4) != 0) )
                op++ ;
            if (strncmp(opCodeTab[op], word, 4) != 0)
                return error("Illegal opcode", lineNo,loc);
            switch ( opClass(op) )
            { 
                case opclRR :
                    /***********************************/
                    if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
                        return error("Bad first register", lineNo,loc);
                    arg1 = num;
                    if ( ! skipCh(','))
                        return error("Missing comma", lineNo, loc);
                    if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
                        return error("Bad second register", lineNo, loc);
                    arg2 = num;
                    if ( ! skipCh(',')) 
                        return error("Missing comma", lineNo,loc);
                    if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
                        return error("Bad third register", lineNo,loc);
                    arg3 = num;
                    break;

                case opclRM :
                case opclRA :
                    /***********************************/
                    if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
                        return error("Bad first register", lineNo,loc);
                    arg1 = num;
                    if ( ! skipCh(','))
                        return error("Missing comma", lineNo,loc);
                    if (! getNum ())
                        return error("Bad displacement", lineNo,loc);
                    arg2 = num;
                    if ( ! skipCh('(') && ! skipCh(',') )
                        return error("Missing LParen", lineNo,loc);
                    if ( (! getNum ()) || (num < 0) || (num >= NO_REGS))
                        return error("Bad second register", lineNo,loc);
                    arg3 = num;
                    break;
            }
            iMem[loc].iop = op;
            iMem[loc].iarg1 = arg1;
            iMem[loc].iarg2 = arg2;
            iMem[loc].iarg3 = arg3;
        }
    }
    return true;
} /* readInstructions */


/********************************************/
enum step_result stepTM (void)
{ 
    struct instruction currentinstruction;
    int pc;
    int r, s, t, m;
    int ok;

    pc = reg[PC_REG] ;
    if ( (pc < 0) || (pc > IADDR_SIZE)  )
        return srIMEM_ERR ;
    reg[PC_REG] = pc + 1 ;
    currentinstruction = iMem[ pc ] ;
    switch (opClass(currentinstruction.iop) )
    { 
        case opclRR :
            /***********************************/
            r = currentinstruction.iarg1 ;
            s = currentinstruction.iarg2 ;
            t = currentinstruction.iarg3 ;
            break;

        case opclRM :
            /***********************************/
            r = currentinstruction.iarg1 ;
            s = currentinstruction.iarg3 ;
            m = currentinstruction.iarg2 + reg[s] ;
            if ( (m < 0) || (m > DADDR_SIZE))
                return srDMEM_ERR ;
            break;

        case opclRA :
            /***********************************/
            r = currentinstruction.iarg1 ;
            s = currentinstruction.iarg3 ;
            m = currentinstruction.iarg2 + reg[s] ;
            break;
    } /* case */

    switch ( currentinstruction.iop)
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
                fgets(line_buf, BUFSIZ, stdin);
                buf_len = strlen(line_buf);
                inCol = 0;
                ok = getNum();
                if ( ! ok ) fprintf(stderr, "Illegal value\n");
                else reg[r] = num;
            }
            while (! ok);
            break;

        case opOUT :  
            printf ("OUT instruction prints: %d\n", reg[r] ) ;
            break;
        case opADD :  reg[r] = reg[s] + reg[t] ;  break;
        case opSUB :  reg[r] = reg[s] - reg[t] ;  break;
        case opMUL :  reg[r] = reg[s] * reg[t] ;  break;

        case opDIV :
                      /***********************************/
                      if ( reg[t] != 0 ) reg[r] = reg[s] / reg[t];
                      else return srZERODIVIDE ;
                      break;

                      /*************** RM instructions ********************/
        case opLD :    reg[r] = data_memory[m] ;  break;
        case opST :    data_memory[m] = reg[r] ;  break;

                       /*************** RA instructions ********************/
        case opLDA :    reg[r] = m ; break;
        case opLDC :    reg[r] = currentinstruction.iarg2 ;   break;
        case opJLT :    if ( reg[r] <  0 ) reg[PC_REG] = m ; break;
        case opJLE :    if ( reg[r] <=  0 ) reg[PC_REG] = m ; break;
        case opJGT :    if ( reg[r] >  0 ) reg[PC_REG] = m ; break;
        case opJGE :    if ( reg[r] >=  0 ) reg[PC_REG] = m ; break;
        case opJEQ :    if ( reg[r] == 0 ) reg[PC_REG] = m ; break;
        case opJNE :    if ( reg[r] != 0 ) reg[PC_REG] = m ; break;

                            /* end of legal instructions */
    } /* case */
    return srOKAY ;
} /* stepTM */

/********************************************/
int doCommand (void)
{ 
    char cmd;
    int stepcnt=0, i;
    int printcnt;
    int stepResult;
    int regNo, loc;
    do
    { 
        printf ("Enter command: ");
        fflush (stdout);
        fgets(line_buf, BUFSIZ, stdin);
        buf_len = strlen(line_buf);
        inCol = 0;
    }
    while (! getWord ());

    cmd = word[0] ;
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
                    "Print n iMem locations starting at b\n");
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
            if ( getNum ())  stepcnt = abs(num);
            break;

        case 'g' :   stepcnt = 1 ;     break;

        case 'r' :
                     /***********************************/
                     for (i = 0; i < NO_REGS; i++)
                     { 
                         printf("%1d: %4d    ", i,reg[i]);
                         if ( (i % 4) == 3 ) printf ("\n");
                     }
                     break;

        case 'i' :
                     /***********************************/
                     printcnt = 1 ;
                     if ( getNum ())
                     { 
                         inst_itr = num;
                         if ( getNum ()) printcnt = num ;
                     }
                     //if ( ! atEOL ())
                     if ( atEOL ())
                         printf ("Instruction locations?\n");
                     else
                     { 
                         while ((inst_itr >= 0) && (inst_itr < IADDR_SIZE)
                                 && (printcnt > 0) )
                         { 
                             writeInstruction(inst_itr);
                             inst_itr++;
                             printcnt-- ;
                         }
                     }
                     break;

        case 'd' :
                     /***********************************/
                     printcnt = 1 ;
                     if ( getNum  ())
                     { 
                         data_itr = num ;
                         if ( getNum ()) printcnt = num ;
                     }
                     //if ( ! atEOL ())
                     if ( atEOL ())
                         printf("Data locations?\n");
                     else
                     { 
                         while ((data_itr >= 0) && (data_itr < DADDR_SIZE)
                                 && (printcnt > 0))
                         { 
                             printf("%5d: %5d\n",data_itr, data_memory[data_itr]);
                             data_itr++;
                             printcnt--;
                         }
                     }
                     break;

        case 'c' :
                     /***********************************/
                     inst_itr = 0;
                     data_itr = 0;
                     stepcnt = 0;
                     for (regNo = 0;  regNo < NO_REGS ; regNo++)
                         reg[regNo] = 0 ;
                     data_memory[0] = DADDR_SIZE - 1 ;
                     for (loc = 1 ; loc < DADDR_SIZE ; loc++)
                         data_memory[loc] = 0 ;
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
                inst_itr = reg[PC_REG] ;
                if ( traceflag ) writeInstruction(inst_itr) ;
                stepResult = stepTM ();
                stepcnt++;
            }
            if ( icountflag )
                printf("Number of instructions executed = %d\n",stepcnt);
        }
        else
        {
            while ((stepcnt > 0) && (stepResult == srOKAY))
            {
                inst_itr = reg[PC_REG] ;
                if ( traceflag ) writeInstruction(inst_itr) ;
                stepResult = stepTM ();
                stepcnt-- ;
            }
        }
        printf( "%s\n",stepResultTab[stepResult] );
    }
    return true;
} /* doCommand */

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    FILE *program_text;
    if (!(program_text = fopen(argv[1], "r"))) {
        perror("TISC");
        exit(1);
    }

    /* read the program */
    if (!readInstructions(program_text)) {
        exit(1);
    }

    /* switch input file to terminal */
    /* reset( input ); */
    /* read-eval-print */
    printf("TM  simulation (enter h for help)...\n");
    do
        done = ! doCommand ();
    while (! done );
    printf("Simulation done.\n");

    fclose(program_text);
    return 0;
}
