0:  LD  6,0(0)	Load GP with max address
1:  LDA  5,0(6)	Copy GP to FP
2:  ST  0,0(0)	Clear location 0
* Jump around I/O functions here
* Code for input routine
4:  ST  0,-1(5)	Store return
5:  IN 0,0,0	
6:  LD  7,-1(5)	Return caller
* Code for output routine
7:  ST  0,-1(5)	Store return
8:  LD  0,-2(5)	Load output value
9:  OUT 0,0,0	
10:  LD  7,-1(5)	Return caller
3:  LDA  7,7(7)	Jump around I/O functions
* End of standard prelude
* -> fundecl
*  processing function: main
*  jump around functions body here
12:  ST  0,-1(5)	store return
* -> compound statement
* processing local var: i
* processing local var: x
* -> op
* -> id
* looking up id: x
13:  LDA  0,-3(5)	load id address
* <- id
14:  ST  0,-4(5)	op: push left
* -> call
* call of function: input
15:  ST  5,-5(5)	push ofp
16:  LDA  5,-5(5)	Push frame
17:  LDA  0,1(7)	Load ac with ret ptr
18:  LDA  7,-15(7)	jump to fun loc
19:  LD  5,0(5)	Pop frame
* <- call
20:  LD  1,-4(5)	op: load left
21:  ST  0,0(1)	assign: store value
* <- op
* -> op
* -> id
* looking up id: i
22:  LDA  0,-2(5)	load id address
* <- id
23:  ST  0,-4(5)	op: push left
* -> constant
24:  LDC  0,1(0)	load const
* <- constant
25:  LD  1,-4(5)	op: load left
26:  ST  0,0(1)	assign: store value
* <- op
* -> While
* While: jump after body comes back here
* -> op
* -> id
* looking up id: i
27:  LD  0,-2(5)	load id value
* <- id
28:  ST  0,-4(5)	op: push left
* -> id
* looking up id: x
29:  LD  0,-3(5)	load id value
* <- id
30:  LD  1,-4(5)	op: load left
31:  SUB 0,1,0	op <=
32:  JLE  0,2(7)	
33:  LDC  0,0(0)	false case
34:  LDA  7,1(7)	unconditional jump
35:  LDC  0,1(0)	true case
* <- op
* -> compound statement
* -> call
* call of function: output
* -> id
* looking up id: i
37:  LD  0,-2(5)	load id value
* <- id
38:  ST  0,-6(5)	op: push left
39:  ST  5,-4(5)	push ofp
40:  LDA  5,-4(5)	Push frame
41:  LDA  0,1(7)	Load ac with ret ptr
42:  LDA  7,-36(7)	jump to fun loc
43:  LD  5,0(5)	Pop frame
* <- call
* -> op
* -> id
* looking up id: i
44:  LDA  0,-2(5)	load id address
* <- id
45:  ST  0,-4(5)	op: push left
* -> op
* -> id
* looking up id: i
46:  LD  0,-2(5)	load id value
* <- id
47:  ST  0,-5(5)	op: push left
* -> constant
48:  LDC  0,1(0)	load const
* <- constant
49:  LD  1,-5(5)	op: load left
50:  ADD 0,1,0	op +
* <- op
51:  LD  1,-4(5)	op: load left
52:  ST  0,0(1)	assign: store value
* <- op
* <- compound statement
53:  LDA  7,-27(7)	While: absolute jmp to test
36:  JEQ  0,17(7)	While: jmp to end
* <- While
* <- compound statement
54:  LD  7,-1(5)	return caller
11:  LDA  7,43(7)	Jump around function body
* <- fundecl
55:  ST  5,0(5)	Push old frame pointer
56:  LDA  5,0(5)	Push frame
57:  LDA  0,1(7)	Load ac with ret ptr
58:  LDA  7,-47(7)	Jump to main
59:  LD  5,0(5)	Pop frame
60:  HALT 0,0,0	
