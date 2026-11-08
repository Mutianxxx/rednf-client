000ef3dc: 70b5	push	{r4, r5, r6, lr}
000ef3de: 0d1e	subs	r5, r1, #0
000ef3e0: 0fd0	beq	#0xef402
000ef3e2: 084e	ldr	r6, [pc, #0x20]
000ef3e4: 0023	movs	r3, #0
000ef3e6: c15c	ldrb	r1, [r0, r3]
000ef3e8: 140a	lsrs	r4, r2, #8
000ef3ea: 4c40	eors	r4, r1
000ef3ec: 5118	adds	r1, r2, r1
000ef3ee: 321c	adds	r2, r6, #0
000ef3f0: 4a43	muls	r2, r1, r2
000ef3f2: 0549	ldr	r1, [pc, #0x14]
000ef3f4: c454	strb	r4, [r0, r3]
000ef3f6: 0133	adds	r3, #1
000ef3f8: 5218	adds	r2, r2, r1
000ef3fa: 1204	lsls	r2, r2, #0x10
000ef3fc: 120c	lsrs	r2, r2, #0x10
000ef3fe: ab42	cmp	r3, r5
000ef400: f1d1	bne	#0xef3e6
000ef402: 70bd	pop	{r4, r5, r6, pc}
000ef404: 6dce	ldm	r6, {r0, r2, r3, r5, r6}
000ef406: 0000	movs	r0, r0
000ef408: bf58	ldr	r7, [r7, r2]
000ef40a: 0000	movs	r0, r0
