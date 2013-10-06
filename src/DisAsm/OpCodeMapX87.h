/*
* Filename: OpCodeMapX87.h
* Author:   DisAsmCompany
* Date:     05/10/2013
*
* Description: Opcode Map for x87 FPU
*              (OpCode D8h - DFh)
*              
*
*/

/* x87 FPU Opcode Map (OpCodes D8h - DFh) */

/*

ModR/M Mod != 3 (ModR/M 00h - BFh)

   0 1 2 3 4 5 6 7
D8 X X X X X X X X DB
D9 X U X X X X X X D9
DA X X X X X X X X DA
DB X X X X I X I X DB
DC X X X X X X X X DC
DD X X X X X I X X DD
DE X X X X X X X X DE
DF X X X X X X X X DF
   0 1 2 3 4 5 6 7

ModR/M Mod == 3 (ModR/M C0h - FFh)

D8

  0 1 2 3 4 5 6 7
0 X X X X X X X X 0
1 X X X X X X X X 1
2 X X X X X X X X 2
3 X X X X X X X X 3
4 X X X X X X X X 4
5 X X X X X X X X 5
6 X X X X X X X X 6
7 X X X X X X X X 7
  0 1 2 3 4 5 6 7

D9

  0 1 2 3 4 5 6 7
0 X X X X X X X X 0
1 X X X X X X X X 1
2 X I I I I I I I 2
3 R R R R R R R R 3
4 X X I I X X I I 4
5 X X X X X X X I 5
6 X X X X X X X X 6
7 X X X X X X X X 7
  0 1 2 3 4 5 6 7

DA

  0 1 2 3 4 5 6 7
0 X X X X X X X X 0
1 X X X X X X X X 1
2 X X X X X X X X 2
3 X X X X X X X X 3
4 I I I I I I I I 4
5 I X I I I I I I 5
6 I I I I I I I I 6
7 I I I I I I I I 7
  0 1 2 3 4 5 6 7

DB

  0 1 2 3 4 5 6 7
0 X X X X X X X X 0
1 X X X X X X X X 1
2 X X X X X X X X 2
3 X X X X X X X X 3
4 I X X I I I I I 4
5 X X X X X X X X 5
6 X X X X X X X X 6
7 I I I I I I I I 7
  0 1 2 3 4 5 6 7

DC

  0 1 2 3 4 5 6 7
0 X X X X X X X X 0
1 X X X X X X X X 1
2 R R R R R R R R 2
3 R R R R R R R R 3
4 X X X X X X X X 4
5 X X X X X X X X 5
6 X X X X X X X X 6
7 X X X X X X X X 7
  0 1 2 3 4 5 6 7

DD

  0 1 2 3 4 5 6 7
0 X X X X X X X X 0
1 R R R R R R R R 1
2 X X X X X X X X 2
3 X X X X X X X X 3
4 X X X X X X X X 4
5 X X X X X X X X 5
6 I I I I I I I I 6
7 I I I I I I I I 7
  0 1 2 3 4 5 6 7

DE

  0 1 2 3 4 5 6 7
0 X X X X X X X X 0
1 X X X X X X X X 1
2 R R R R R R R R 2
3 I X I I I I I I 3
4 X X X X X X X X 4
5 X X X X X X X X 5
6 X X X X X X X X 6
7 X X X X X X X X 7
  0 1 2 3 4 5 6 7

DF

  0 1 2 3 4 5 6 7
0 R R R R R R R R 0
1 R R R R R R R R 1
2 R R R R R R R R 2
3 R R R R R R R R 3
4 X I I I I I I I 4
5 X X X X X X X X 5
6 X X X X X X X X 6
7 I I I I I I I I 7
  0 1 2 3 4 5 6 7

*/

#ifndef __OPCODEMAPX87_H__
#define __OPCODEMAPX87_H__

#define X87ELEMENT1(X, Y) {X, OP1(Y)}
#define X87ELEMENT2(X, Y, Z) {X, OP2(Y, Z)}

#define X87LINE1(X) \
	X87ELEMENT1(X, ST0), \
	X87ELEMENT1(X, ST1), \
	X87ELEMENT1(X, ST2), \
	X87ELEMENT1(X, ST3), \
	X87ELEMENT1(X, ST4), \
	X87ELEMENT1(X, ST5), \
	X87ELEMENT1(X, ST6), \
	X87ELEMENT1(X, ST7), \

#define X87LINE2(X) \
	X87ELEMENT2(X, ST0, ST0), \
	X87ELEMENT2(X, ST0, ST1), \
	X87ELEMENT2(X, ST0, ST2), \
	X87ELEMENT2(X, ST0, ST3), \
	X87ELEMENT2(X, ST0, ST4), \
	X87ELEMENT2(X, ST0, ST5), \
	X87ELEMENT2(X, ST0, ST6), \
	X87ELEMENT2(X, ST0, ST7), \

#define X87LINE2I(X) \
	X87ELEMENT2(X, ST0, ST0), \
	X87ELEMENT2(X, ST1, ST0), \
	X87ELEMENT2(X, ST2, ST0), \
	X87ELEMENT2(X, ST3, ST0), \
	X87ELEMENT2(X, ST4, ST0), \
	X87ELEMENT2(X, ST5, ST0), \
	X87ELEMENT2(X, ST6, ST0), \
	X87ELEMENT2(X, ST7, ST0), \

OpCodeMapElement OpCodeMapX87[] =
{
	/* ModR/M Mod != 3 (ModR/M 00h - BFh) */
	/* D8 */
	{FADD, OP1(Ev)}, {FMUL, OP1(Ev)}, {FCOM, OP1(Ev)}, {FCOMP, OP1(Ev)}, {FSUB, OP1(Ev)}, {FSUBR, OP1(Ev)}, {FDIV, OP1(Ev)}, {FDIVR, OP1(Ev)},
	/* D9 */
	{FLD, OP1(Ev)}, {DB}, {FST, OP1(Ev)}, {FSTP, OP1(Ev)}, {FLDENV, OP1(Ev)}, {FLDCW, OP1(Ev)}, {FSTENV, OP1(Ev)}, {FSTCW, OP1(Ev)},
	/* DA */
	{FIADD, OP1(Ev)}, {FIMUL, OP1(Ev)}, {FICOM, OP1(Ev)}, {FICOMP, OP1(Ev)}, {FISUB, OP1(Ev)}, {FISUBR, OP1(Ev)}, {FIDIV, OP1(Ev)}, {FIDIVR, OP1(Ev)},
	/* DB */
	{FILD, OP1(Ev)}, {FISTTP, OP1(Ev)}, {FIST, OP1(Ev)}, {FISTP, OP1(Ev)}, {DB}, {FLD, OP1(Ev)}, {DB}, {FSTP, OP1(Ev)},
	/* DC */
	{FADD, OP1(Eq)}, {FMUL, OP1(Eq)}, {FCOM, OP1(Eq)}, {FCOMP, OP1(Eq)}, {FSUB, OP1(Eq)}, {FSUBR, OP1(Eq)}, {FDIV, OP1(Eq)}, {FDIVR, OP1(Eq)},
	/* DD */
	{FLD, OP1(Eq)}, {FISTTP, OP1(Eq)}, {FST, OP1(Eq)}, {FSTP, OP1(Eq)}, {FRSTOR, OP1(Eq)}, {DB}, {FNSAVE, OP1(Eq)}, {FNSTSW, OP1(Eq)},
	/* DE */
	{FIADD, OP1(Ew)}, {FIMUL, OP1(Ew)}, {FICOM, OP1(Ew)}, {FICOMP, OP1(Ew)}, {FISUB, OP1(Ew)}, {FISUBR, OP1(Ew)}, {FIDIV, OP1(Ew)}, {FIDIVR, OP1(Ew)},
	/* DF */
	{FILD, OP1(Ew)}, {FISTTP, OP1(Ew)}, {FIST, OP1(Ew)}, {FISTP, OP1(Ew)}, {FBLD, OP1(Eq)}, {FILD, OP1(Eq)}, {FBSTP, OP1(Eq)}, {FISTP, OP1(Eq)},
	/* ModR/M Mod == 3 (ModR/M C0h - FFh) */
	/* D8 */
	X87LINE2(FADD)
	X87LINE2(FMUL)
	X87LINE2(FCOM)
	X87LINE2(FCOMP)
	X87LINE2(FSUB)
	X87LINE2(FSUBR)
	X87LINE2(FDIV)
	X87LINE2(FDIVR)
	/* D9 */
	X87LINE2(FLD)
	X87LINE2(FXCH)
	{FNOP}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{FCHS}, {FABS}, {DB}, {DB}, {FTST}, {FXAM}, {DB}, {DB},
	{FLD1}, {FLDL2T}, {FLDL2E}, {FLDPI}, {FLDLG2}, {FLDLN2}, {FLDZ}, {DB},
	{F2XM1}, {FYL2X}, {FPTAN}, {FPATAN}, {FXTRACT}, {FPREM1}, {FDECSTP}, {FINCSTP},
	{FPREM}, {FYL2XP1}, {FSQRT}, {FSINCOS}, {FRNDINT}, {FSCALE}, {FSIN}, {FCOS},
	/* DA */
	X87LINE2(FCMOVB)
	X87LINE2(FCMOVE)
	X87LINE2(FCMOVBE)
	X87LINE2(FCMOVU)
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {FUCOMPP}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* DB */
	X87LINE2(FCMOVNB)
	X87LINE2(FCMOVNE)
	X87LINE2(FCMOVNBE)
	X87LINE2(FCMOVNU)
	{DB}, {DB}, {FNCLEX}, {FNINIT}, {DB}, {DB}, {DB}, {DB},
	X87LINE2(FUCOMI)
	X87LINE2(FCOMI)
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* DC */
	X87LINE2I(FADD)
	X87LINE2I(FMUL)
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	X87LINE2I(FSUBR)
	X87LINE2I(FSUB)
	X87LINE2I(FDIVR)
	X87LINE2I(FDIV)
	/* DD */
	X87LINE1(FFREE)
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	X87LINE1(FST)
	X87LINE1(FSTP)
	X87LINE2I(FUCOM)
	X87LINE1(FUCOMP)
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* DE */
	X87LINE2I(FADDP)
	X87LINE2I(FMULP)
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {FCOMPP}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	X87LINE2I(FSUBRP)
	X87LINE2I(FSUBP)
	X87LINE2I(FDIVRP)
	X87LINE2I(FDIVP)
	/* DF */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{FNSTSW, OP1(AX)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	X87LINE2(FCOMIP)
	X87LINE2(FUCOMIP)
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
};

#endif /* __OPCODEMAPX87_H__ */
