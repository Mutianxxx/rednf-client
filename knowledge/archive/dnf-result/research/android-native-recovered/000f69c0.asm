000f69c0: f0b5	push	{r4, r5, r6, r7, lr}
000f69c2: 0369	ldr	r3, [r0, #0x10]
000f69c4: 0c68	ldr	r4, [r1]
000f69c6: 1f1c	adds	r7, r3, #0
000f69c8: 9e79	ldrb	r6, [r3, #6]
000f69ca: d879	ldrb	r0, [r3, #7]
000f69cc: 1d7a	ldrb	r5, [r3, #8]
000f69ce: 5a7a	ldrb	r2, [r3, #9]
000f69d0: 174b	ldr	r3, [pc, #0x5c]
000f69d2: 0134	adds	r4, #1
000f69d4: 0a37	adds	r7, #0xa
000f69d6: 9c42	cmp	r4, r3
000f69d8: 1dd8	bhi	#0xf6a16
000f69da: 3602	lsls	r6, r6, #8
000f69dc: 0643	orrs	r6, r0
000f69de: 2d02	lsls	r5, r5, #8
000f69e0: 1543	orrs	r5, r2
000f69e2: b446	mov	ip, r6
000f69e4: a642	cmp	r6, r4
000f69e6: 1ad3	blo	#0xf6a1e
000f69e8: 6346	mov	r3, ip
000f69ea: 9e1b	subs	r6, r3, r6
000f69ec: b542	cmp	r5, r6
000f69ee: 12d9	bls	#0xf6a16
000f69f0: 7300	lsls	r3, r6, #1
000f69f2: ff18	adds	r7, r7, r3
000f69f4: 3a78	ldrb	r2, [r7]
000f69f6: 7878	ldrb	r0, [r7, #1]
000f69f8: bb1c	adds	r3, r7, #2
000f69fa: 1202	lsls	r2, r2, #8
000f69fc: 1043	orrs	r0, r2
000f69fe: 14d1	bne	#0xf6a2a
000f6a00: 321c	adds	r2, r6, #0
000f6a02: 05e0	b	#0xf6a10
000f6a04: 1c78	ldrb	r4, [r3]
000f6a06: 5878	ldrb	r0, [r3, #1]
000f6a08: 0233	adds	r3, #2
000f6a0a: 2402	lsls	r4, r4, #8
000f6a0c: 2043	orrs	r0, r4
000f6a0e: 08d1	bne	#0xf6a22
000f6a10: 0132	adds	r2, #1
000f6a12: 9542	cmp	r5, r2
000f6a14: f6d8	bhi	#0xf6a04
000f6a16: 0020	movs	r0, #0
000f6a18: 0022	movs	r2, #0
000f6a1a: 0a60	str	r2, [r1]
000f6a1c: f0bd	pop	{r4, r5, r6, r7, pc}
000f6a1e: a446	mov	ip, r4
000f6a20: e2e7	b	#0xf69e8
000f6a22: 6346	mov	r3, ip
000f6a24: 9e1b	subs	r6, r3, r6
000f6a26: b218	adds	r2, r6, r2
000f6a28: f7e7	b	#0xf6a1a
000f6a2a: 6246	mov	r2, ip
000f6a2c: f5e7	b	#0xf6a1a
000f6a2e: c046	mov	r8, r8
000f6a30: ffff	.byte	0xff, 0xff
000f6a32: 0000	movs	r0, r0
