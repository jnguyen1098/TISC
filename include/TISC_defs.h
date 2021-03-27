/**
 * @file TISC_defs.h
 * @author Jason Nguyen
 *
 * @mainpage
 * This file may not exist in the future. It is supposed to house
 * definitions, but honestly I may just separate this into a file
 * full of constants/macros and then another file for structs/enums.
 *
 * @date March 2021
 * @brief TISC consts/structs/enums
 */

#ifndef TISC_DEFS_H
#define TISC_DEFS_H

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
#define WORD_SIZE   20

enum op_code {

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

};

/**
 * Enum that represents an opcode's given class.
 */
const enum op_class {
    opclRR,     /**< Register-Register operations (r, s, t)     */
    opclRM,     /**< Register-Memory operations (r) v. (d, s)   */
    opclRA,     /**< Register-Address operations (r). (d, s)    */
}

/**
 * Lookup table for quick conversion between op_code and op_class
 */
get_op_class[] = {
    [opHALT]  = opclRR,
    [opIN]    = opclRR,
    [opOUT]   = opclRR,
    [opADD]   = opclRR,
    [opSUB]   = opclRR,
    [opMUL]   = opclRR,
    [opDIV]   = opclRR,
    [opRRLim] = opclRR,

    [opLD]    = opclRM,
    [opST]    = opclRM,
    [opRMLim] = opclRM,

    [opLDA]   = opclRA,
    [opLDC]   = opclRA,
    [opJLT]   = opclRA,
    [opJLE]   = opclRA,
    [opJGT]   = opclRA,
    [opJGE]   = opclRA,
    [opJEQ]   = opclRA,
    [opJNE]   = opclRA,
    [opRALim] = opclRA,
};

/**
 * Step result
 */
enum step_result {
    srOKAY,                             /**< OK, no errors  */
    srHALT,                             /**< Halt operations */
    STEP_ILLEGAL_PROGRAM_COUNTER_INDEX, /**< Illegal program counter index */
    STEP_ILLEGAL_DATA_MEMORY_INDEX,     /**< Illegal data memory index */
    srZERODIVIDE                        /**< Division by zero */
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

#endif
