
asm long __lmul__(long left:__D0,long right:__D1):__D0;
asm long __ldivu__(unsigned long left:__D0,unsigned long right:__D1):__D0;
asm long __ldiv__(long left:__D0,long right:__D1):__D0;
asm long __lmodu__(unsigned long left:__D0,unsigned long right:__D1):__D0;
asm long __lmod__(long left:__D0,long right:__D1):__D0;
asm void __wswtch__(void);
asm void __lswtch__(void);

asm long __lmul__(long left:__D0,long right:__D1):__D0
{				/* d0: operand a ; d1: operand b */
#if __CFM68K__
	move.l	(a1), a5
#endif

	movem.l	d2-d3,-(sp)
	move.l	d0,d2
	swap	d2
	mulu.w	d1,d2		/* HiWord(a)*LoWord(b)->d2 */
	move.l	d1,d3
	swap	d3
	mulu.w	d0,d3		/* LoWord(a)*HiWord(b)->d3 */
	add.w	d3,d2		/* add the two results */
	swap	d2		/* and put LoWord of result in HiWord(d2) */
	clr.w	d2		/* clr LoWord(d2) */
	mulu	d1,d0		/* LoWord(a)*LoWord(b)->d0 */
	add.l	d2,d0		/* result:=d0+d2 */
	movem.l	(sp)+,d2-d3
	rts
}
asm long __ldivu__(unsigned long left:__D0,unsigned long right:__D1):__D0
{				/* d0: unsigned operand a ; d1: unsigned operand b */
#if __CFM68K__
	move.l	(a1), a5
#endif

	movem.l	d2-d3,-(sp)
	move.l	d1,d2		/* test if HiWord(b)==0 */
	clr.w	d2
	swap	d2
	bne.s	lldiv
	move.w	d0,d3		/* long division of a/b (divu version b<0x00010000) */
	clr.w	d0
	swap	d0
	beq.s	hizero		/* test if high word of a==0 */
	divu.w	d1,d0		/* HiWord(a)/LoWord(b) */
	move.w	d0,d2		/* HiWord(d0): modulo result of division */
	swap	d2		/* HiWord(d2): high word div result */
hizero:	move.w	d3,d0
	divu.w	d1,d0		/* (modulo div result+LoWord(a))/LoWord(b) */
	move.w	d0,d2
	move.l	d2,d0		/* div result -> d0 */
	movem.l	(sp)+,d2-d3
	rts
lldiv:	move.w	d0,d2		/* long division of a/b (bit version b>=0x00010000) */
	clr.w	d0		/* HiWord(a) -> d0 */
	swap	d0
	swap	d2		/* LoWord(a) -> HiWord(d2) */
	move.l	d1,d3		/* b -> d3 */
	moveq	#16-1,d1
dloop:	add.l	d2,d2		/* d0:d2 64 bit dividend (result is shifted into d2) */
	addx.l	d0,d0
	cmp.l	d3,d0
	bcs.s	dloope		/* is divisor>=dividend */
	sub.l	d3,d0
	addq.b	#1,d2		/* shift one into result */
dloope:	dbf	d1,dloop
	move.l	d2,d0
	movem.l	(sp)+,d2-d3
	rts
}

asm long __ldiv__(long left:__D0,long right:__D1):__D0
{				/* d0: signed operand a ; d1: signed operand b */
#if __CFM68K__
	move.l	(a1), a5
#endif

	tst.l	d0
	bge.s	apos
	neg.l	d0
	tst.l	d1
	bge	negres
	neg.l	d1
	jmp	__ldivu__	/* both operands were negative (result>=0) */
apos:	tst.l	d1
	blt.s	bneg
	jmp	__ldivu__	/* both operands were positive (result>=0) */
bneg:	neg.l	d1
negres:	jsr	__ldivu__	/* one operand was negative (result<=0) */
	neg.l	d0
	rts
}

asm long __lmodu__(unsigned long left:__D0,unsigned long right:__D1):__D0
{
#if __CFM68K__
	move.l	(a1), a5
#endif

	movem.l	d2-d3,-(sp)
	move.l	d1,d2		/* test if HiWord(b)==0 */
	clr.w	d2
	swap	d2
	bne.s	lmod
	move.w	d0,d3		/* long modulo of a%b (divu version b<0x00010000) */
	clr.w	d0
	swap	d0
	beq.s	hizero		/* test if high word of a==0 */
	divu.w	d1,d0		/* HiWord(a)/LoWord(b) */
	move.w	d0,d2		/* HiWord(d0): modulo result of division */
	swap	d2		/* HiWord(d2): high word div result */
hizero:	move.w	d3,d0
	divu.w	d1,d0		/* (modulodivresult+LoWord(a))/LoWord(b) */
	clr.w	d0
	swap	d0		/* mod result -> d0 */
	movem.l	(sp)+,d2-d3
	rts
lmod:	move.w	d0,d2		/* long modulo of a%b (bit version b>=0x00010000) */
	clr.w	d0		/* HiWord(a) -> d0 */
	swap	d0
	swap	d2		/* LoWord(a) -> HiWord(d2) */
	move.l	d1,d3		/* b -> d3 */
	moveq	#16-1,d1
dloop:	add.l	d2,d2		/* d0:d2 64 bit dividend */
	addx.l	d0,d0
	cmp.l	d3,d0
	bcs.s	dloope		/* is divisor>=dividend */
	sub.l	d3,d0
dloope:	dbf	d1,dloop
	movem.l	(sp)+,d2-d3
	rts
}

asm long __lmod__(long left:__D0,long right:__D1):__D0
{
#if __CFM68K__
	move.l	(a1), a5
#endif

	tst.l	d1
	bge.s	bpos
	neg.l	d1
bpos:	tst.l	d0
	blt.s	aneg
	jmp	__lmodu__
aneg:	neg.l	d0
	jsr	__lmodu__	/* one operand was negative (result<=0) */
	neg.l	d0
	rts
}


asm void __wswtch__(void)
{
#if __CFM68K__
	move.l	(a1), a5
#endif

	move.l	(sp)+,a0	/* a0: address of switchtable */
	move.l	a0,a1		/* a1: address of default label */
	add.w	(a0)+,a1
	cmp.w	(a0)+,d0	/* compare minimum */
	bge.s	L0
	jmp	(a1)
L0:	cmp.w	(a0)+,d0	/* compare maximum */
	ble.s	L1
	jmp	(a1)
L1:	move.w	(a0)+,d1	/* number of compares */
L2:	cmp.w	(a0)+,d0	/* compare loop */
	bne.s	L3
	add.w	(a0),a0		/* add offset and branch */
	jmp	(a0)
L3:	addq.w	#2,a0
	dbf	d1,L2
	jmp	(a1)		/* value was not in table */
}

asm void __lswtch__(void)
{
#if __CFM68K__
	move.l	(a1), a5
#endif

	move.l	(sp)+,a0	/* a0: address of switchtable */
	move.l	a0,a1		/* a1: address of default label */
	add.w	(a0)+,a1
	cmp.l	(a0)+,d0	/* compare minimum */
	bge.s	L0
	jmp	(a1)
L0:	cmp.l	(a0)+,d0	/* compare maximum */
	ble.s	L1
	jmp	(a1)
L1:	move.w	(a0)+,d1	/* number of compares */
L2:	cmp.l	(a0)+,d0	/* compare loop */
	bne.s	L3
	add.w	(a0),a0		/* add offset and branch */
	jmp	(a0)
L3:	addq.w	#2,a0
	dbf	d1,L2
	jmp	(a1)		/* value was not in table */
}
