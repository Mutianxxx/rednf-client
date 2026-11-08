000f4b20: f0b5	push	{r4, r5, r6, r7, lr}
000f4b22: 4746	mov	r7, r8
000f4b24: 80b4	push	{r7}
000f4b26: 4468	ldr	r4, [r0, #4]
000f4b28: 0668	ldr	r6, [r0]
000f4b2a: 651e	subs	r5, r4, #1
000f4b2c: ad18	adds	r5, r5, r2
000f4b2e: 9a1a	subs	r2, r3, r2
000f4b30: 6742	rsbs	r7, r4, #0
000f4b32: 141b	subs	r4, r2, r4
000f4b34: 4269	ldr	r2, [r0, #0x14]
000f4b36: 3d40	ands	r5, r7
000f4b38: 3541	asrs	r5, r6
000f4b3a: 291c	adds	r1, r5, #0
000f4b3c: 9442	cmp	r4, r2
000f4b3e: 02dd	ble	#0xf4b46
000f4b40: 1f40	ands	r7, r3
000f4b42: 391c	adds	r1, r7, #0
000f4b44: 3141	asrs	r1, r6
000f4b46: 0029	cmp	r1, #0
000f4b48: 42db	blt	#0xf4bd0
000f4b4a: 038f	ldrh	r3, [r0, #0x38]
000f4b4c: 9d42	cmp	r5, r3
000f4b4e: 3fda	bge	#0xf4bd0
000f4b50: ea43	mvns	r2, r5
000f4b52: d217	asrs	r2, r2, #0x1f
000f4b54: 1540	ands	r5, r2
000f4b56: 9942	cmp	r1, r3
000f4b58: 00db	blt	#0xf4b5c
000f4b5a: 591e	subs	r1, r3, #1
000f4b5c: 6b03	lsls	r3, r5, #0xd
000f4b5e: 1a0c	lsrs	r2, r3, #0x10
000f4b60: 9446	mov	ip, r2
000f4b62: 4a03	lsls	r2, r1, #0xd
000f4b64: 140c	lsrs	r4, r2, #0x10
000f4b66: a046	mov	r8, r4
000f4b68: 0724	movs	r4, #7
000f4b6a: 2540	ands	r5, r4
000f4b6c: ff26	movs	r6, #0xff
000f4b6e: 2e41	asrs	r6, r5
000f4b70: 2140	ands	r1, r4
000f4b72: 3506	lsls	r5, r6, #0x18
000f4b74: 7f26	movs	r6, #0x7f
000f4b76: 0e41	asrs	r6, r1
000f4b78: 9e21	movs	r1, #0x9e
000f4b7a: 445e	ldrsh	r4, [r0, r1]
000f4b7c: f643	mvns	r6, r6
000f4b7e: 3606	lsls	r6, r6, #0x18
000f4b80: 1b14	asrs	r3, r3, #0x10
000f4b82: 1214	asrs	r2, r2, #0x10
000f4b84: 2d0e	lsrs	r5, r5, #0x18
000f4b86: 360e	lsrs	r6, r6, #0x18
000f4b88: a342	cmp	r3, r4
000f4b8a: 01da	bge	#0xf4b90
000f4b8c: 6446	mov	r4, ip
000f4b8e: 4452	strh	r4, [r0, r1]
000f4b90: a021	movs	r1, #0xa0
000f4b92: 445e	ldrsh	r4, [r0, r1]
000f4b94: a242	cmp	r2, r4
000f4b96: 01dd	ble	#0xf4b9c
000f4b98: 4446	mov	r4, r8
000f4b9a: 4452	strh	r4, [r0, r1]
000f4b9c: 9421	movs	r1, #0x94
000f4b9e: 4158	ldr	r1, [r0, r1]
000f4ba0: c06b	ldr	r0, [r0, #0x3c]
000f4ba2: 5918	adds	r1, r3, r1
000f4ba4: d31a	subs	r3, r2, r3
000f4ba6: 4018	adds	r0, r0, r1
000f4ba8: 002b	cmp	r3, #0
000f4baa: 14dd	ble	#0xf4bd6
000f4bac: 0278	ldrb	r2, [r0]
000f4bae: 5c1e	subs	r4, r3, #1
000f4bb0: 1543	orrs	r5, r2
000f4bb2: 0570	strb	r5, [r0]
000f4bb4: 231e	subs	r3, r4, #0
000f4bb6: 08d0	beq	#0xf4bca
000f4bb8: 0121	movs	r1, #1
000f4bba: 021c	adds	r2, r0, #0
000f4bbc: 4942	rsbs	r1, r1, #0
000f4bbe: 0132	adds	r2, #1
000f4bc0: 013b	subs	r3, #1
000f4bc2: 1170	strb	r1, [r2]
000f4bc4: 002b	cmp	r3, #0
000f4bc6: fad1	bne	#0xf4bbe
000f4bc8: 0019	adds	r0, r0, r4
000f4bca: 4578	ldrb	r5, [r0, #1]
000f4bcc: 2e43	orrs	r6, r5
000f4bce: 4670	strb	r6, [r0, #1]
000f4bd0: 04bc	pop	{r2}
000f4bd2: 9046	mov	r8, r2
000f4bd4: f0bd	pop	{r4, r5, r6, r7, pc}
000f4bd6: 0378	ldrb	r3, [r0]
000f4bd8: 3540	ands	r5, r6
000f4bda: 1d43	orrs	r5, r3
000f4bdc: 0570	strb	r5, [r0]
000f4bde: f7e7	b	#0xf4bd0
