0: LD  6,0(0)
1: LDA  5,0(6)
2: ST  0,0(0)
4: ST  0,-1(5)
5: IN  0,0,0
6: LD  7,-1(5)
7: ST  0,-1(5)
8: LD  0,-2(5)
9: OUT  0,0,0
10: LD  7,-1(5)
3: LDA  7,7(7)
12: ST 0,-1(5)
13: LDC 3, 0(0)
14: ST 3, -3(5)
15: LD 3, -3(5)
16: ST 3, -2(5)
17: LD 0, -2(5)
18: LDC 1, 10(0)
19: SUB 0,0,1
20: JGE 0, 2(7)
21: LDC 0, 1(0)
22: LDA 7, 1(7)
23: LDC 0, 0(0)
24: ST 0, -14(5)
26: LD 3, -2(5)
27: LD 2, -2(5)
28: JLT 2, 3(7)
29: LDC 4, 10(0)
30: SUB 4,2,4
31: JLT 4, 3(7)
32: LDC 4,-1000(0)
33: OUT 4,0,0
34: HALT 0,0,0
35: SUB 2,5,2
36: ST 3, -4(2)
37: LD 0, -2(5)
38: LDC 1, 1(0)
39: ADD 0,0,1
40: ST 0, -15(5)
41: LD 3, -15(5)
42: ST 3, -2(5)
43: LDA 7, -27(7)
25: JEQ 0, 18(7)
44: LDC 3, 0(0)
45: ST 3, -2(5)
46: LD 0, -2(5)
47: LDC 1, 10(0)
48: SUB 0,0,1
49: JGE 0, 2(7)
50: LDC 0, 1(0)
51: LDA 7, 1(7)
52: LDC 0, 0(0)
53: ST 0, -16(5)
55: LD 2, -2(5)
56: JLT 2, 3(7)
57: LDC 4, 10(0)
58: SUB 4,2,4
59: JLT 4, 3(7)
60: LDC 4,-1000(0)
61: OUT 4,0,0
62: HALT 0,0,0
63: SUB 2,5,2
64: LD 0, -4(2)
65: ST  0, -16(5)
66: ST  5, -14(5)
67: LDA  5, -14(5)
68: LDA  0, 1(7)
69: LDA  7, -63(7)
70: LD 5, 0(5)
71: LD 0, -2(5)
72: LDC 1, 1(0)
73: ADD 0,0,1
74: ST 0, -17(5)
75: LD 3, -17(5)
76: ST 3, -2(5)
77: LDA 7, -32(7)
54: JEQ 0, 23(7)
78: LD 0, -3(5)
79: ST  0, -16(5)
80: ST  5, -14(5)
81: LDA  5, -14(5)
82: LDA  0, 1(7)
83: LDA  7, -77(7)
84: LD 5, 0(5)
85: LD 7,-1(5)
11: LDA 7,74(7)
86: ST  5,0(5)
87: LDA  5,0(5)
88: LDA  0,1(7)
89: LDA  7,-78(7)
90: LD  5,0(5)
91: HALT  0,0,0