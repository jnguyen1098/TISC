* C-Minus Compilation to TM Code
* File: programs/2.tm
* Standard prelude:
  0:     LD  6,0(0) 	
  1:    LDA  5,0(6) 	
  2:     ST  0,0(0) 	
* Jump around i/o routines here
* code for input routine
  4:     ST  0,-1(5) 	
  5:     IN  0,0,0 	
  6:     LD  7,-1(5) 	
* code for output routine
  7:     ST  0,-1(5) 	
  8:     LD  0,-2(5) 	
  9:    OUT  0,0,0 	
 10:     LD  7,-1(5) 	
  3:    LDA  7,7(7) 	
* End of standard prelude.
* processing function: printIntegers
 12:     ST  0,-1(5) 	
* allocating parameter: size
* allocating local var: i
* Looking up id: i
 13:    LDA  0,-3(5) 	load id
 14:     ST  0,-4(5) 	push left
 15:    LDC  0,0(0) 	load constant
 16:     LD  1,-4(5) 	
 17:     ST  0,0(1) 	assign: store value
* -> while
* Looking up id: i
 18:     LD  0,-3(5) 	load id
 19:     ST  0,-5(5) 	push left
* Looking up id: size
 20:     LD  0,-2(5) 	load id
 21:     LD  1,-5(5) 	load left
 22:    SUB  0,1,0 	
 23:    JLT  0,2(7) 	br if true
 24:    LDC  0,0(0) 	false case
 25:    LDA  7,1(7) 	unconditional jump
 26:    LDC  0,1(0) 	true case
* Looking up id: i
 28:     LD  0,-3(5) 	load id
 29:     ST  0,-6(5) 	store arg val
 30:     LD  0,-6(5) 	load arg val
 31:     ST  0,-9(5) 	store arg val in next frame
* call to function: output
 32:     ST  5,-7(5) 	push ofp
 33:    LDA  5,-7(5) 	push frame
 34:    LDA  0,1(7) 	load ac with ret ptr
 35:    LDA  7,-29(7) 	jump to output loc
 36:     LD  5,0(5) 	pop frame
* Looking up id: i
 37:    LDA  0,-3(5) 	load id
 38:     ST  0,-7(5) 	push left
* Looking up id: i
 39:     LD  0,-3(5) 	load id
 40:     ST  0,-8(5) 	push left
 41:    LDC  0,1(0) 	load constant
 42:     LD  1,-8(5) 	load left
 43:    ADD  0,1,0 	
 44:     LD  1,-7(5) 	
 45:     ST  0,0(1) 	assign: store value
 46:    LDA  7,-29(7) 	while: unconditional jmp to start
 27:    JEQ  0,19(7) 	while: jmp around on false
* <- while
 47:     LD  7,-1(5) 	
 11:    LDA  7,36(7) 	jump around printIntegers body
* processing function: main
 49:     ST  0,-1(5) 	
 50:    LDC  0,5(0) 	load constant
 51:     ST  0,-2(5) 	store arg val
 52:     LD  0,-2(5) 	load arg val
 53:     ST  0,-5(5) 	store arg val in next frame
* call to function: printIntegers
 54:     ST  5,-3(5) 	push ofp
 55:    LDA  5,-3(5) 	push frame
 56:    LDA  0,1(7) 	load ac with ret ptr
 57:    LDA  7,-46(7) 	jump to printIntegers loc
 58:     LD  5,0(5) 	pop frame
 59:     LD  7,-1(5) 	
 48:    LDA  7,11(7) 	jump around main body
 60:     ST  5,0(5) 	push ofp
 61:    LDA  5,0(5) 	push frame
 62:    LDA  0,1(7) 	load ac with ret ptr
 63:    LDA  7,-15(7) 	jump to main loc
 64:     LD  5,0(5) 	pop frame
* End of execution:
 65:   HALT  0,0,0 	
