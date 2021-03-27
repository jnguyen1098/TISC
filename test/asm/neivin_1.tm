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
*  processing function: getSmallest
*  jump around functions body here
12:  ST  0,-1(5)	store return
* -> compound statement
* processing local var: smallest
* -> op
* -> id
* looking up id: smallest
13:  LDA  0,-5(5)	load id address
* <- id
14:  ST  0,-6(5)	op: push left
* -> id
* looking up id: a
15:  LD  0,-2(5)	load id value
* <- id
16:  LD  1,-6(5)	op: load left
17:  ST  0,0(1)	assign: store value
* <- op
* -> if
* -> op
* -> id
* looking up id: b
18:  LD  0,-3(5)	load id value
* <- id
19:  ST  0,-6(5)	op: push left
* -> id
* looking up id: smallest
20:  LD  0,-5(5)	load id value
* <- id
21:  LD  1,-6(5)	op: load left
22:  SUB 0,1,0	op <
23:  JLT  0,2(7)	
24:  LDC  0,0(0)	false case
25:  LDA  7,1(7)	unconditional jump
26:  LDC  0,1(0)	true case
* <- op
* -> op
* -> id
* looking up id: smallest
28:  LDA  0,-5(5)	load id address
* <- id
29:  ST  0,-6(5)	op: push left
* -> id
* looking up id: b
30:  LD  0,-3(5)	load id value
* <- id
31:  LD  1,-6(5)	op: load left
32:  ST  0,0(1)	assign: store value
* <- op
27:  JEQ  0,5(7)	if: jump to else part
* <- if
* -> if
* -> op
* -> id
* looking up id: c
33:  LD  0,-4(5)	load id value
* <- id
34:  ST  0,-6(5)	op: push left
* -> id
* looking up id: smallest
35:  LD  0,-5(5)	load id value
* <- id
36:  LD  1,-6(5)	op: load left
37:  SUB 0,1,0	op <
38:  JLT  0,2(7)	
39:  LDC  0,0(0)	false case
40:  LDA  7,1(7)	unconditional jump
41:  LDC  0,1(0)	true case
* <- op
* -> op
* -> id
* looking up id: smallest
43:  LDA  0,-5(5)	load id address
* <- id
44:  ST  0,-6(5)	op: push left
* -> id
* looking up id: c
45:  LD  0,-4(5)	load id value
* <- id
46:  LD  1,-6(5)	op: load left
47:  ST  0,0(1)	assign: store value
* <- op
42:  JEQ  0,5(7)	if: jump to else part
* <- if
* -> return
* -> id
* looking up id: smallest
48:  LD  0,-5(5)	load id value
* <- id
49:  LD  7,-1(5)	return to caller
* <- return
* <- compound statement
50:  LD  7,-1(5)	return caller
11:  LDA  7,39(7)	Jump around function body
* <- fundecl
* -> fundecl
*  processing function: main
*  jump around functions body here
52:  ST  0,-1(5)	store return
* -> compound statement
* processing local var: x
* processing local var: y
* processing local var: z
* -> op
* -> id
* looking up id: x
53:  LDA  0,-2(5)	load id address
* <- id
54:  ST  0,-5(5)	op: push left
* -> constant
55:  LDC  0,10(0)	load const
* <- constant
56:  LD  1,-5(5)	op: load left
57:  ST  0,0(1)	assign: store value
* <- op
* -> op
* -> id
* looking up id: y
58:  LDA  0,-3(5)	load id address
* <- id
59:  ST  0,-5(5)	op: push left
* -> constant
60:  LDC  0,6(0)	load const
* <- constant
61:  LD  1,-5(5)	op: load left
62:  ST  0,0(1)	assign: store value
* <- op
* -> op
* -> id
* looking up id: z
63:  LDA  0,-4(5)	load id address
* <- id
64:  ST  0,-5(5)	op: push left
* -> constant
65:  LDC  0,12(0)	load const
* <- constant
66:  LD  1,-5(5)	op: load left
67:  ST  0,0(1)	assign: store value
* <- op
* -> call
* call of function: output
* -> call
* call of function: getSmallest
* -> id
* looking up id: x
68:  LD  0,-2(5)	load id value
* <- id
69:  ST  0,-7(5)	op: push left
* -> id
* looking up id: y
70:  LD  0,-3(5)	load id value
* <- id
71:  ST  0,-8(5)	op: push left
* -> id
* looking up id: z
72:  LD  0,-4(5)	load id value
* <- id
73:  ST  0,-9(5)	op: push left
74:  ST  5,-5(5)	push ofp
75:  LDA  5,-5(5)	Push frame
76:  LDA  0,1(7)	Load ac with ret ptr
77:  LDA  7,-66(7)	jump to fun loc
78:  LD  5,0(5)	Pop frame
* <- call
79:  ST  0,-7(5)	op: push left
80:  ST  5,-5(5)	push ofp
81:  LDA  5,-5(5)	Push frame
82:  LDA  0,1(7)	Load ac with ret ptr
83:  LDA  7,-77(7)	jump to fun loc
84:  LD  5,0(5)	Pop frame
* <- call
* <- compound statement
85:  LD  7,-1(5)	return caller
51:  LDA  7,34(7)	Jump around function body
* <- fundecl
86:  ST  5,0(5)	Push old frame pointer
87:  LDA  5,0(5)	Push frame
88:  LDA  0,1(7)	Load ac with ret ptr
89:  LDA  7,-38(7)	Jump to main
90:  LD  5,0(5)	Pop frame
91:  HALT 0,0,0	
