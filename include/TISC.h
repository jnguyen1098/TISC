/**
 * @file TISC.h
 * @author Jason Nguyen
 * @date March 2021
 * @brief TISC function signatures.
 */

#ifndef TISC_H
#define TISC_H

/** Instruction address array size */
#define IADDR_SIZE  1024

/** Data memory array size */
#define DADDR_SIZE  1024

/** Number of registers */
#define NO_REGS     8

/** Program counter register */
#define PC_REG      7

/** Size of an instruction word */
#define WORDSIZE    20

// pre post return param

/**
 * Get character
 * 
 * @pre Stream exists
 * @post Stream may or may not exist
 **/
void getCh(void);

#endif
