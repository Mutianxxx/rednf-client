000f6c48: f0b5	push	{r4, r5, r6, r7, lr}
000f6c4a: 0369	ldr	r3, [r0, #0x10]
000f6c4c: 0c68	ldr	r4, [r1]
000f6c4e: 187b	ldrb	r0, [r3, #0xc]
000f6c50: 5a7b	ldrb	r2, [r3, #0xd]
000f6c52: 1e7c	ldrb	r6, [r3, #0x10]
000f6c54: 0006	lsls	r0, r0, #0x18
000f6c56: 1204	lsls	r2, r2, #0x10
000f6c58: 0243	orrs	r2, r0
000f6c5a: d87b	ldrb	r0, [r3, #0xf]
000f6c5c: dd7c	ldrb	r5, [r3, #0x13]
000f6c5e: 1f1c	adds	r7, r3, #0
000f6c60: 0243	orrs	r2, r0
000f6c62: 987b	ldrb	r0, [r3, #0xe]
000f6c64: 3606	lsls	r6, r6, #0x18
000f6c66: 0134	adds	r4, #1
000f6c68: 0002	lsls	r0, r0, #8
000f6c6a: 0243	orrs	r2, r0
000f6c6c: 587c	ldrb	r0, [r3, #0x11]
000f6c6e: 9b7c	ldrb	r3, [r3, #0x12]
000f6c70: 1437	adds	r7, #0x14
000f6c72: 0004	lsls	r0, r0, #0x10
000f6c74: 0643	orrs	r6, r0
000f6c76: 2e43	orrs	r6, r5
000f6c78: 1b02	lsls	r3, r3, #8
000f6c7a: 1e43	orrs	r6, r3
000f6c7c: 151c	adds	r5, r2, #0
000f6c7e: a242	cmp	r2, r4
000f6c80: 00d2	bhs	#0xf6c84
000f6c82: 251c	adds	r5, r4, #0
000f6c84: aa1a	subs	r2, r5, r2
000f6c86: 0020	movs	r0, #0
000f6c88: 9642	cmp	r6, r2
000f6c8a: 14d9	bls	#0xf6cb6
000f6c8c: 5000	lsls	r0, r2, #1
000f6c8e: 3818	adds	r0, r7, r0
000f6c90: 4478	ldrb	r4, [r0, #1]
000f6c92: 831c	adds	r3, r0, #2
000f6c94: 0078	ldrb	r0, [r0]
000f6c96: 271c	adds	r7, r4, #0
000f6c98: 0002	lsls	r0, r0, #8
000f6c9a: 0743	orrs	r7, r0
000f6c9c: 06d0	beq	#0xf6cac
000f6c9e: 09e0	b	#0xf6cb4
000f6ca0: 1c78	ldrb	r4, [r3]
000f6ca2: 5878	ldrb	r0, [r3, #1]
000f6ca4: 0233	adds	r3, #2
000f6ca6: 2402	lsls	r4, r4, #8
000f6ca8: 2043	orrs	r0, r4
000f6caa: 04d1	bne	#0xf6cb6
000f6cac: 0132	adds	r2, #1
000f6cae: 0135	adds	r5, #1
000f6cb0: 9642	cmp	r6, r2
000f6cb2: f5d8	bhi	#0xf6ca0
000f6cb4: 381c	adds	r0, r7, #0
000f6cb6: 0d60	str	r5, [r1]
000f6cb8: f0bd	pop	{r4, r5, r6, r7, pc}
