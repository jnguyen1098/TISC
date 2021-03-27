* C-Minus Compilation to TM Code
* File: programs/1.tm
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
* processing function: largest
 12:     ST  0,-1(5) 	
* allocating parameter: a
* allocating parameter: b
* allocating parameter: c
* allocating local var: result
* Looking up id: result
 13:    LDA  0,-5(5) 	load id
 14:     ST  0,-6(5) 	push left
* Looking up id: a
 15:     LD  0,-2(5) 	load id
 16:     LD  1,-6(5) 	
 17:     ST  0,0(1) 	assign: store value
* -> if
* Looking up id: b
 18:     LD  0,-3(5) 	load id
 19:     ST  0,-7(5) 	push left
* Looking up id: result
 20:     LD  0,-5(5) 	load id
 21:     LD  1,-7(5) 	load left
 22:    SUB  0,1,0 	
 23:    JGT  0,2(7) 	br if true
 24:    LDC  0,0(0) 	false case
 25:    LDA  7,1(7) 	unconditional jump
 26:    LDC  0,1(0) 	true case
* Looking up id: result
 28:    LDA  0,-5(5) 	load id
 29:     ST  0,-8(5) 	push left
* Looking up id: b
 30:     LD  0,-3(5) 	load id
 31:     LD  1,-8(5) 	
 32:     ST  0,0(1) 	assign: store value
 27:    JEQ  0,6(7) 	if: jmp to else
* <- if
* -> if
* Looking up id: c
 33:     LD  0,-4(5) 	load id
 34:     ST  0,-9(5) 	push left
* Looking up id: result
 35:     LD  0,-5(5) 	load id
 36:     LD  1,-9(5) 	load left
 37:    SUB  0,1,0 	
 38:    JGT  0,2(7) 	br if true
 39:    LDC  0,0(0) 	false case
 40:    LDA  7,1(7) 	unconditional jump
 41:    LDC  0,1(0) 	true case
* Looking up id: result
 43:    LDA  0,-5(5) 	load id
 44:     ST  0,-10(5) 	push left
* Looking up id: c
 45:     LD  0,-4(5) 	load id
 46:     LD  1,-10(5) 	
 47:     ST  0,0(1) 	assign: store value
 42:    JEQ  0,6(7) 	if: jmp to else
* <- if
* Looking up id: result
 48:    LDA  0,-5(5) 	load id
 49:     ST  0,-11(5) 	push left
 50:    LDC  0,1(0) 	load constant
 51:     ST  0,-12(5) 	push left
 52:    LDC  0,2(0) 	load constant
 53:     ST  0,-13(5) 	push left
 54:    LDC  0,3(0) 	load constant
 55:     LD  1,-13(5) 	load left
 56:    DIV  0,1,0 	
 57:     ST  0,-14(5) 	push left
 58:    LDC  0,4(0) 	load constant
 59:     LD  1,-14(5) 	load left
 60:    MUL  0,1,0 	
 61:     LD  1,-12(5) 	load left
 62:    SUB  0,1,0 	
 63:     LD  1,-11(5) 	
 64:     ST  0,0(1) 	assign: store value
* Looking up id: result
 65:     LD  0,-5(5) 	load id
 66:     LD  7,-1(5) 	return to caller
 67:     LD  7,-1(5) 	
 11:    LDA  7,56(7) 	jump around largest body
* processing function: main
 69:     ST  0,-1(5) 	
* allocating local var: x
* allocating local var: y
* allocating local var: z
* Looking up id: x
 70:    LDA  0,-2(5) 	load id
 71:     ST  0,-5(5) 	push left
 72:    LDC  0,6(0) 	load constant
 73:     LD  1,-5(5) 	
 74:     ST  0,0(1) 	assign: store value
* Looking up id: y
 75:    LDA  0,-3(5) 	load id
 76:     ST  0,-6(5) 	push left
 77:    LDC  0,2(0) 	load constant
 78:     LD  1,-6(5) 	
 79:     ST  0,0(1) 	assign: store value
* Looking up id: z
 80:    LDA  0,-4(5) 	load id
 81:     ST  0,-7(5) 	push left
 82:    LDC  0,13(0) 	load constant
 83:     LD  1,-7(5) 	
 84:     ST  0,0(1) 	assign: store value
* Looking up id: x
 85:     LD  0,-2(5) 	load id
 86:     ST  0,-8(5) 	store arg val
* Looking up id: y
 87:     LD  0,-3(5) 	load id
 88:     ST  0,-9(5) 	store arg val
* Looking up id: z
 89:     LD  0,-4(5) 	load id
 90:     ST  0,-10(5) 	store arg val
 91:     LD  0,-8(5) 	load arg val
 92:     ST  0,-13(5) 	store arg val in next frame
 93:     LD  0,-9(5) 	load arg val
 94:     ST  0,-14(5) 	store arg val in next frame
 95:     LD  0,-10(5) 	load arg val
 96:     ST  0,-15(5) 	store arg val in next frame
* call to function: largest
 97:     ST  5,-11(5) 	push ofp
 98:    LDA  5,-11(5) 	push frame
 99:    LDA  0,1(7) 	load ac with ret ptr
100:    LDA  7,-89(7) 	jump to largest loc
101:     LD  5,0(5) 	pop frame
102:     ST  0,-11(5) 	store arg val
103:     LD  0,-11(5) 	load arg val
104:     ST  0,-14(5) 	store arg val in next frame
* call to function: output
105:     ST  5,-12(5) 	push ofp
106:    LDA  5,-12(5) 	push frame
107:    LDA  0,1(7) 	load ac with ret ptr
108:    LDA  7,-102(7) 	jump to output loc
109:     LD  5,0(5) 	pop frame
110:     LD  7,-1(5) 	
 68:    LDA  7,42(7) 	jump around main body
111:     ST  5,0(5) 	push ofp
112:    LDA  5,0(5) 	push frame
113:    LDA  0,1(7) 	load ac with ret ptr
114:    LDA  7,-46(7) 	jump to main loc
115:     LD  5,0(5) 	pop frame
* End of execution:
116:   HALT  0,0,0 	
