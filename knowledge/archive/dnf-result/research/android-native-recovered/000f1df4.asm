000f1df4: f0b5	push	{r4, r5, r6, r7, lr}
000f1df6: 4746	mov	r7, r8
000f1df8: 80b4	push	{r7}
000f1dfa: 4668	ldr	r6, [r0, #4]
000f1dfc: 071c	adds	r7, r0, #0
000f1dfe: 8846	mov	r8, r1
000f1e00: 8468	ldr	r4, [r0, #8]
000f1e02: 002e	cmp	r6, #0
000f1e04: 0dd0	beq	#0xf1e22
000f1e06: 0025	movs	r5, #0
000f1e08: a168	ldr	r1, [r4, #8]
000f1e0a: 4046	mov	r0, r8
000f1e0c: 013e	subs	r6, #1
000f1e0e: f6f74bf9	bl	#0xe80a8
000f1e12: a560	str	r5, [r4, #8]
000f1e14: 2560	str	r5, [r4]
000f1e16: 6560	str	r5, [r4, #4]
000f1e18: e560	str	r5, [r4, #0xc]
000f1e1a: 1034	adds	r4, #0x10
000f1e1c: 002e	cmp	r6, #0
000f1e1e: f3d1	bne	#0xf1e08
000f1e20: bc68	ldr	r4, [r7, #8]
000f1e22: 4046	mov	r0, r8
000f1e24: 211c	adds	r1, r4, #0
000f1e26: f6f73ff9	bl	#0xe80a8
000f1e2a: 0023	movs	r3, #0
000f1e2c: bb60	str	r3, [r7, #8]
000f1e2e: 3b60	str	r3, [r7]
000f1e30: 7b60	str	r3, [r7, #4]
000f1e32: 04bc	pop	{r2}
000f1e34: 9046	mov	r8, r2
000f1e36: f0bd	pop	{r4, r5, r6, r7, pc}
