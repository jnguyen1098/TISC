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
13: LD 0, -3(5)
14: LDC 1, 0(0)
15: SUB 0,0,1
16: JNE 0, 2(7)
17: LDC 0, 1(0)
18: LDA 7, 1(7)
19: LDC 0, 0(0)
20: ST 0, -4(5)
22: LD 0, -2(5)
23: LD 7, -1(5)
21: JEQ 0, 3(7)
25: LD 0, -3(5)
26: ST 0, -6(5) STORE ARG VAL
27: LD 0, -2(5)
28: LD 1, -3(5)
29: DIV 0,0,1
30: ST 0, -8(5)
31: LD 0, -8(5)
32: LD 1, -3(5)
33: MUL 0,0,1
34: ST 0, -9(5)
35: LD 1, -9(5)
36: LD 0, -2(5)
37: SUB 0,0,1
38: ST 0, -10(5)
39: LD 0, -10(5)
40: ST 0, -7(5) STORE ARG VAL
41: ST  5, -4(5)
42: LDA  5, -4(5)
43: LDA  0,1(7)
44: LDA  7,-33(7)
45: LD  5,0(5)
46: LD 7, -1(5)
24: LDA 7, 22(7)
47: LD 7,-1(5)
11: LDA 7,36(7)
49: ST 0,-1(5)
50: ST  5,-4(5)
51: LDA  5,-4(5)
52: LDA  0,1(7)
53: LDA 7,-50(7)
54: LD 5,0(5)
55: LDA 3,0(0)
56: ST 3, -2(5)
57: LDC 3, 10(0)
58: ST 3, 0(6)
59: LD 0, -2(5)
60: ST 0, -6(5) STORE ARG VAL
61: LD 0, 0(6)
62: ST 0, -7(5) STORE ARG VAL
63: ST  5, -4(5)
64: LDA  5, -4(5)
65: LDA  0,1(7)
66: LDA  7,-55(7)
67: LD  5,0(5)
68: ST  0, -6(5)
69: ST  5, -4(5)
70: LDA  5, -4(5)
71: LDA  0, 1(7)
72: LDA  7, -66(7)
73: LD 5, 0(5)
74: LD 7,-1(5)
48: LDA 7,26(7)
75: ST  5,-1(5)
76: LDA  5,-1(5)
77: LDA  0,1(7)
78: LDA  7,-30(7)
79: LD  5,0(5)
80: HALT  0,0,0