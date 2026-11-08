000f1ac0: f0b5	push	{r4, r5, r6, r7, lr}
000f1ac2: 5f46	mov	r7, fp
000f1ac4: 5646	mov	r6, sl
000f1ac6: 4d46	mov	r5, sb
000f1ac8: 4446	mov	r4, r8
000f1aca: f0b4	push	{r4, r5, r6, r7}
000f1acc: 8d68	ldr	r5, [r1, #8]
000f1ace: 0968	ldr	r1, [r1]
000f1ad0: 83b0	sub	sp, #0xc
000f1ad2: 0191	str	r1, [sp, #4]
000f1ad4: 0268	ldr	r2, [r0]
000f1ad6: 8368	ldr	r3, [r0, #8]
000f1ad8: 002a	cmp	r2, #0
000f1ada: 0ad0	beq	#0xf1af2
000f1adc: 0124	movs	r4, #1
000f1ade: 0426	movs	r6, #4
000f1ae0: 6442	rsbs	r4, r4, #0
000f1ae2: 1969	ldr	r1, [r3, #0x10]
000f1ae4: 013a	subs	r2, #1
000f1ae6: 9c61	str	r4, [r3, #0x18]
000f1ae8: b143	bics	r1, r6
000f1aea: 1961	str	r1, [r3, #0x10]
000f1aec: 1c33	adds	r3, #0x1c
000f1aee: 002a	cmp	r2, #0
000f1af0: f7d1	bne	#0xf1ae2
000f1af2: 019b	ldr	r3, [sp, #4]
000f1af4: 002b	cmp	r3, #0
000f1af6: 51d0	beq	#0xf1b9c
000f1af8: 0022	movs	r2, #0
000f1afa: 0023	movs	r3, #0
000f1afc: 0424	movs	r4, #4
000f1afe: 0021	movs	r1, #0
000f1b00: 9346	mov	fp, r2
000f1b02: 9846	mov	r8, r3
000f1b04: a146	mov	sb, r4
000f1b06: 00e0	b	#0xf1b0a
000f1b08: 231c	adds	r3, r4, #0
000f1b0a: 5c10	asrs	r4, r3, #1
000f1b0c: 002b	cmp	r3, #0
000f1b0e: 04d1	bne	#0xf1b1a
000f1b10: 2e78	ldrb	r6, [r5]
000f1b12: 4024	movs	r4, #0x40
000f1b14: 0135	adds	r5, #1
000f1b16: b346	mov	fp, r6
000f1b18: 8023	movs	r3, #0x80
000f1b1a: 5f46	mov	r7, fp
000f1b1c: 1f42	tst	r7, r3
000f1b1e: 14d0	beq	#0xf1b4a
000f1b20: 8368	ldr	r3, [r0, #8]
000f1b22: 4f46	mov	r7, sb
000f1b24: 5b18	adds	r3, r3, r1
000f1b26: 1e69	ldr	r6, [r3, #0x10]
000f1b28: 3e42	tst	r6, r7
000f1b2a: 0ed1	bne	#0xf1b4a
000f1b2c: 3e43	orrs	r6, r7
000f1b2e: 1e61	str	r6, [r3, #0x10]
000f1b30: 0668	ldr	r6, [r0]
000f1b32: b446	mov	ip, r6
000f1b34: c445	cmp	ip, r8
000f1b36: 08d9	bls	#0xf1b4a
000f1b38: c768	ldr	r7, [r0, #0xc]
000f1b3a: 4646	mov	r6, r8
000f1b3c: b600	lsls	r6, r6, #2
000f1b3e: bc46	mov	ip, r7
000f1b40: 371c	adds	r7, r6, #0
000f1b42: 6744	add	r7, ip
000f1b44: 3b60	str	r3, [r7]
000f1b46: 0123	movs	r3, #1
000f1b48: 9844	add	r8, r3
000f1b4a: 019e	ldr	r6, [sp, #4]
000f1b4c: 0132	adds	r2, #1
000f1b4e: 1c31	adds	r1, #0x1c
000f1b50: b242	cmp	r2, r6
000f1b52: d9d1	bne	#0xf1b08
000f1b54: 4746	mov	r7, r8
000f1b56: 4346	mov	r3, r8
000f1b58: 4760	str	r7, [r0, #4]
000f1b5a: c768	ldr	r7, [r0, #0xc]
000f1b5c: 012b	cmp	r3, #1
000f1b5e: 16dd	ble	#0xf1b8e
000f1b60: 0124	movs	r4, #1
000f1b62: 6442	rsbs	r4, r4, #0
000f1b64: a446	mov	ip, r4
000f1b66: 0437	adds	r7, #4
000f1b68: c444	add	ip, r8
000f1b6a: 0026	movs	r6, #0
000f1b6c: 01cf	ldm	r7!, {r0}
000f1b6e: 321c	adds	r2, r6, #0
000f1b70: 3b1c	adds	r3, r7, #0
000f1b72: 083b	subs	r3, #8
000f1b74: 1968	ldr	r1, [r3]
000f1b76: 0468	ldr	r4, [r0]
000f1b78: 0d68	ldr	r5, [r1]
000f1b7a: a542	cmp	r5, r4
000f1b7c: 04db	blt	#0xf1b88
000f1b7e: 5960	str	r1, [r3, #4]
000f1b80: 1860	str	r0, [r3]
000f1b82: 043b	subs	r3, #4
000f1b84: 013a	subs	r2, #1
000f1b86: f5d2	bhs	#0xf1b74
000f1b88: 0136	adds	r6, #1
000f1b8a: 6645	cmp	r6, ip
000f1b8c: eed1	bne	#0xf1b6c
000f1b8e: 03b0	add	sp, #0xc
000f1b90: 3cbc	pop	{r2, r3, r4, r5}
000f1b92: 9046	mov	r8, r2
000f1b94: 9946	mov	sb, r3
000f1b96: a246	mov	sl, r4
000f1b98: ab46	mov	fp, r5
000f1b9a: f0bd	pop	{r4, r5, r6, r7, pc}
000f1b9c: 019e	ldr	r6, [sp, #4]
000f1b9e: 4660	str	r6, [r0, #4]
000f1ba0: f5e7	b	#0xf1b8e
