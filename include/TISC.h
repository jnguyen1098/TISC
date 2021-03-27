/**
 * @file TISC.h
 * @author Jason Nguyen
 * @date March 2021
 * @brief TISC function signatures.
 */

#ifndef TISC_H
#define TISC_H

#include <stdlib.h>

/** Instruction address array size */
#define IADDR_SIZE  1024

/** Data memory array size */
#define DADDR_SIZE  1024

/** Number of registers */
#define NO_REGS     8

/** Program counter register */
#define PC_REG      (NO_REGS - 1)

/** Size of an instruction word */
#define WORDSIZE    20

typedef enum {
    opclRR,     /* reg operands r,s,t */
    opclRM,     /* reg r, mem d+s */
    opclRA      /* reg r, int d+s */
} OPCLASS;

typedef enum {

        // REGISTER-TO-REGISTER (RR) INSTRUCTIONS
    opHALT,     /**< Halt                                       */

    opIN,       /**< Read into reg(r)                           */
    opOUT,      /**< Write from reg(r)                          */

    opADD,      /**< reg(r) = reg(s) + reg(t)                   */
    opSUB,      /**< reg(r) = reg(s) - reg(t)                   */
    opMUL,      /**< reg(r) = reg(s) * reg(t)                   */
    opDIV,      /**< reg(r) = reg(s) / reg(t)                   */

    opRRLim,    /**< RR opcode limit                            */


        // REGISTER-TO-MEMORY (RM) INSTRUCTIONS
    opLD,       /**< reg(r) = mem(d + reg(s))                   */
    opST,       /**< mem(d + reg(s)) = reg(r)                   */

    opRMLim,    /**< RM opcode limit                            */


        // REGISTER-TO-ADDRESS (RA) INSTRUCTIONS
    opLDA,      /**< reg(r) = d + reg(s)                        */
    opLDC,      /**< reg(r) = d                                 */

    opJLT,      /**< if reg(r) <  0 then reg(7) = d + reg(s)    */
    opJLE,      /**< if reg(r) <= 0 then reg(7) = d + reg(s)    */
    opJGT,      /**< if reg(r) >  0 then reg(7) = d + reg(s)    */
    opJGE,      /**< if reg(r) >= 0 then reg(7) = d + reg(s)    */

    opJEQ,      /**< if reg(r) == 0 then reg(7) = d + reg(s)    */
    opJNE,      /**< if reg(r) != 0 then reg(7) = d + reg(s)    */

    opRALim,    /**< RA opcode limit                            */

} OPCODE;

/**
 * Step result
 */
enum step_result {
    srOKAY,         /**< OK, no errors  */
    srHALT,         /**< Halt operations */
    srIMEM_ERR,     /**< Instruction memory error */
    srDMEM_ERR,     /**< Data memory error */
    srZERODIVIDE    /**< Division by zero */
};

/**
 * Instruction struct
 */
struct instruction {
    int iop;        /**< TODO: is this input/output processor? */
    int iarg1;      /**< TODO: input argument 1? */
    int iarg2;      /**< TODO: input argument 2? */
    int iarg3;      /**< TODO: input argument 3? */
};

const char *opCodeTab[] = {
    /* RR opcodes */
    "HALT", "IN", "OUT", "ADD", "SUB", "MUL", "DIV", "<unknown RR>",

    /* RM opcodes */
    "LD", "ST", "<unknown RM>",

    /* RA opcodes */
    "LDA", "LDC", "JLT", "JLE", "JGT", "JGE", "JEQ", "JNE", "<unknown RA>", NULL,
};

const char *stepResultTab[] = {
    "OK",
    "Halted",
    "Instruction Memory Fault",
    "Data Memory Fault",
    "Division by 0",
    NULL,
};

/**
 * Get character
 * 
 * @pre Stream exists
 * @post Stream may or may not exist
 **/
void getCh(void);

#endif
