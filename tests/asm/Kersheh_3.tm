* C-Minus Compilation to TM Code
* File: programs/3.tm
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
* processing function: main
 12:     ST  0,-1(5) 	
* allocating local var: a
* Looking up id: a
* generating index
 13:    LDC  0,1(0) 	load constant
 14:     LD  1,-11(5) 	top of array
 15:    ADD  0,1,0 	
 16:    LDA  0,0(0) 	load id
 17:     ST  0,-12(5) 	push left
 18:    LDC  0,4(0) 	load constant
 19:     LD  1,-12(5) 	
 20:     ST  0,0(1) 	assign: store value
* Looking up id: a
* generating index
* Looking up id: a
* generating index
 21:    LDC  0,1(0) 	load constant
 22:     LD  1,-11(5) 	top of array
 23:    ADD  0,1,0 	
 24:     LD  0,0(0) 	load id
 25:     ST  0,-14(5) 	push left
 26:    LDC  0,2(0) 	load constant
 27:     LD  1,-14(5) 	load left
 28:    DIV  0,1,0 	
 29:     LD  1,-11(5) 	top of array
 30:    ADD  0,1,0 	
 31:    LDA  0,0(0) 	load id
 32:     ST  0,-13(5) 	push left
 33:    LDC  0,6(0) 	load constant
 34:     LD  1,-13(5) 	
 35:     ST  0,0(1) 	assign: store value
* Looking up id: a
* generating index
 36:    LDC  0,1(0) 	load constant
 37:     ST  0,-16(5) 	push left
 38:    LDC  0,2(0) 	load constant
 39:     LD  1,-16(5) 	load left
 40:    ADD  0,1,0 	
 41:     LD  1,-11(5) 	top of array
 42:    ADD  0,1,0 	
 43:    LDA  0,0(0) 	load id
 44:     ST  0,-15(5) 	push left
 45:    LDC  0,22(0) 	load constant
 46:     LD  1,-15(5) 	
 47:     ST  0,0(1) 	assign: store value
* Looking up id: a
* generating index
 48:    LDC  0,1(0) 	load constant
 49:     LD  1,-11(5) 	top of array
 50:    ADD  0,1,0 	
 51:     LD  0,0(0) 	load id
 52:     ST  0,-17(5) 	store arg val
 53:     LD  0,-17(5) 	load arg val
 54:     ST  0,-20(5) 	store arg val in next frame
* call to function: output
 55:     ST  5,-18(5) 	push ofp
 56:    LDA  5,-18(5) 	push frame
 57:    LDA  0,1(7) 	load ac with ret ptr
 58:    LDA  7,-52(7) 	jump to output loc
 59:     LD  5,0(5) 	pop frame
* Looking up id: a
* generating index
 60:    LDC  0,2(0) 	load constant
 61:     LD  1,-11(5) 	top of array
 62:    ADD  0,1,0 	
 63:     LD  0,0(0) 	load id
 64:     ST  0,-18(5) 	store arg val
 65:     LD  0,-18(5) 	load arg val
 66:     ST  0,-21(5) 	store arg val in next frame
* call to function: output
 67:     ST  5,-19(5) 	push ofp
 68:    LDA  5,-19(5) 	push frame
 69:    LDA  0,1(7) 	load ac with ret ptr
 70:    LDA  7,-64(7) 	jump to output loc
 71:     LD  5,0(5) 	pop frame
* Looking up id: a
* generating index
 72:    LDC  0,3(0) 	load constant
 73:     LD  1,-11(5) 	top of array
 74:    ADD  0,1,0 	
 75:     LD  0,0(0) 	load id
 76:     ST  0,-19(5) 	store arg val
 77:     LD  0,-19(5) 	load arg val
 78:     ST  0,-22(5) 	store arg val in next frame
* call to function: output
 79:     ST  5,-20(5) 	push ofp
 80:    LDA  5,-20(5) 	push frame
 81:    LDA  0,1(7) 	load ac with ret ptr
 82:    LDA  7,-76(7) 	jump to output loc
 83:     LD  5,0(5) 	pop frame
 84:     LD  7,-1(5) 	
 11:    LDA  7,73(7) 	jump around main body
 85:     ST  5,0(5) 	push ofp
 86:    LDA  5,0(5) 	push frame
 87:    LDA  0,1(7) 	load ac with ret ptr
 88:    LDA  7,-77(7) 	jump to main loc
 89:     LD  5,0(5) 	pop frame
* End of execution:
 90:   HALT  0,0,0 	
