000efce0: f0b5	push	{r4, r5, r6, r7, lr}
000efce2: 5f46	mov	r7, fp
000efce4: 5646	mov	r6, sl
000efce6: 4d46	mov	r5, sb
000efce8: 4446	mov	r4, r8
000efcea: f0b4	push	{r4, r5, r6, r7}
000efcec: 87b0	sub	sp, #0x1c
000efcee: 0292	str	r2, [sp, #8]
000efcf0: 0468	ldr	r4, [r0]
000efcf2: 0d1c	adds	r5, r1, #0
000efcf4: 8346	mov	fp, r0
000efcf6: 0594	str	r4, [sp, #0x14]
000efcf8: 0026	movs	r6, #0
000efcfa: ac42	cmp	r4, r5
000efcfc: 39d2	bhs	#0xefd72
000efcfe: 2278	ldrb	r2, [r4]
000efd00: 5d21	movs	r1, #0x5d
000efd02: 8946	mov	sb, r1
000efd04: 5b2a	cmp	r2, #0x5b
000efd06: 47d0	beq	#0xefd98
000efd08: 0021	movs	r1, #0
000efd0a: 8946	mov	sb, r1
000efd0c: 7b2a	cmp	r2, #0x7b
000efd0e: 41d0	beq	#0xefd94
000efd10: 1f1c	adds	r7, r3, #0
000efd12: 391c	adds	r1, r7, #0
000efd14: 05ab	add	r3, sp, #0x14
000efd16: 6a46	mov	r2, sp
000efd18: 9a46	mov	sl, r3
000efd1a: 1032	adds	r2, #0x10
000efd1c: 4b1e	subs	r3, r1, #1
000efd1e: 9941	sbcs	r1, r3
000efd20: 0026	movs	r6, #0
000efd22: 0191	str	r1, [sp, #4]
000efd24: 0392	str	r2, [sp, #0xc]
000efd26: a542	cmp	r5, r4
000efd28: 23d9	bls	#0xefd72
000efd2a: 5046	mov	r0, sl
000efd2c: 291c	adds	r1, r5, #0
000efd2e: fff773f8	bl	#0xeee18
000efd32: 059c	ldr	r4, [sp, #0x14]
000efd34: a542	cmp	r5, r4
000efd36: 1cd9	bls	#0xefd72
000efd38: 2378	ldrb	r3, [r4]
000efd3a: 4b45	cmp	r3, sb
000efd3c: 2fd0	beq	#0xefd9e
000efd3e: 029b	ldr	r3, [sp, #8]
000efd40: 9e42	cmp	r6, r3
000efd42: 20db	blt	#0xefd86
000efd44: 0199	ldr	r1, [sp, #4]
000efd46: 0029	cmp	r1, #0
000efd48: 13d1	bne	#0xefd72
000efd4a: 039b	ldr	r3, [sp, #0xc]
000efd4c: 9846	mov	r8, r3
000efd4e: 291c	adds	r1, r5, #0
000efd50: 5046	mov	r0, sl
000efd52: 109a	ldr	r2, [sp, #0x40]
000efd54: fff74efe	bl	#0xef9f4
000efd58: 4146	mov	r1, r8
000efd5a: 0860	str	r0, [r1]
000efd5c: 059b	ldr	r3, [sp, #0x14]
000efd5e: 9c42	cmp	r4, r3
000efd60: 1fd0	beq	#0xefda2
000efd62: 4a46	mov	r2, sb
000efd64: 0136	adds	r6, #1
000efd66: 0437	adds	r7, #4
000efd68: 002a	cmp	r2, #0
000efd6a: 11d0	beq	#0xefd90
000efd6c: 1c1c	adds	r4, r3, #0
000efd6e: a542	cmp	r5, r4
000efd70: dbd8	bhi	#0xefd2a
000efd72: 5b46	mov	r3, fp
000efd74: 07b0	add	sp, #0x1c
000efd76: 301c	adds	r0, r6, #0
000efd78: 1c60	str	r4, [r3]
000efd7a: 3cbc	pop	{r2, r3, r4, r5}
000efd7c: 9046	mov	r8, r2
000efd7e: 9946	mov	sb, r3
000efd80: a246	mov	sl, r4
000efd82: ab46	mov	fp, r5
000efd84: f0bd	pop	{r4, r5, r6, r7, pc}
000efd86: 019a	ldr	r2, [sp, #4]
000efd88: b846	mov	r8, r7
000efd8a: 002a	cmp	r2, #0
000efd8c: dfd1	bne	#0xefd4e
000efd8e: dce7	b	#0xefd4a
000efd90: 1c1c	adds	r4, r3, #0
000efd92: eee7	b	#0xefd72
000efd94: 7d22	movs	r2, #0x7d
000efd96: 9146	mov	sb, r2
000efd98: 0134	adds	r4, #1
000efd9a: 0594	str	r4, [sp, #0x14]
000efd9c: b8e7	b	#0xefd10
000efd9e: 0134	adds	r4, #1
000efda0: e7e7	b	#0xefd72
000efda2: 0126	movs	r6, #1
000efda4: 7642	rsbs	r6, r6, #0
000efda6: e4e7	b	#0xefd72
