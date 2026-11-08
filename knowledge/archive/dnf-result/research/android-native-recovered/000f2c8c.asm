000f2c8c: f0b5	push	{r4, r5, r6, r7, lr}
000f2c8e: 5f46	mov	r7, fp
000f2c90: 5646	mov	r6, sl
000f2c92: 4d46	mov	r5, sb
000f2c94: 4446	mov	r4, r8
000f2c96: f0b4	push	{r4, r5, r6, r7}
000f2c98: 4368	ldr	r3, [r0, #4]
000f2c9a: 8fb0	sub	sp, #0x3c
000f2c9c: 041c	adds	r4, r0, #0
000f2c9e: 151c	adds	r5, r2, #0
000f2ca0: 002b	cmp	r3, #0
000f2ca2: 10d1	bne	#0xf2cc6
000f2ca4: 0268	ldr	r2, [r0]
000f2ca6: 4b1e	subs	r3, r1, #1
000f2ca8: 9941	sbcs	r1, r3
000f2caa: 8846	mov	r8, r1
000f2cac: c900	lsls	r1, r1, #3
000f2cae: 0692	str	r2, [sp, #0x18]
000f2cb0: 0591	str	r1, [sp, #0x14]
000f2cb2: 0f1c	adds	r7, r1, #0
000f2cb4: 4744	add	r7, r8
000f2cb6: c368	ldr	r3, [r0, #0xc]
000f2cb8: bf00	lsls	r7, r7, #2
000f2cba: 1037	adds	r7, #0x10
000f2cbc: c719	adds	r7, r0, r7
000f2cbe: 0620	movs	r0, #6
000f2cc0: 012b	cmp	r3, #1
000f2cc2: 07d0	beq	#0xf2cd4
000f2cc4: 6060	str	r0, [r4, #4]
000f2cc6: 0fb0	add	sp, #0x3c
000f2cc8: 3cbc	pop	{r2, r3, r4, r5}
000f2cca: 9046	mov	r8, r2
000f2ccc: 9946	mov	sb, r3
000f2cce: a246	mov	sl, r4
000f2cd0: ab46	mov	fp, r5
000f2cd2: f0bd	pop	{r4, r5, r6, r7, pc}
000f2cd4: 6a46	mov	r2, sp
000f2cd6: 0aa9	add	r1, sp, #0x28
000f2cd8: 3432	adds	r2, #0x34
000f2cda: 8a46	mov	sl, r1
000f2cdc: 0e1c	adds	r6, r1, #0
000f2cde: 0992	str	r2, [sp, #0x24]
000f2ce0: 2868	ldr	r0, [r5]
000f2ce2: f3f763f8	bl	#0xe5dac
000f2ce6: 8146	mov	sb, r0
000f2ce8: 6868	ldr	r0, [r5, #4]
000f2cea: f3f75ff8	bl	#0xe5dac
000f2cee: 4b46	mov	r3, sb
000f2cf0: 1914	asrs	r1, r3, #0x10
000f2cf2: 0214	asrs	r2, r0, #0x10
000f2cf4: 069b	ldr	r3, [sp, #0x18]
000f2cf6: 381c	adds	r0, r7, #0
000f2cf8: 0096	str	r6, [sp]
000f2cfa: fff7a3fd	bl	#0xf2844
000f2cfe: 0028	cmp	r0, #0
000f2d00: e0d1	bne	#0xf2cc4
000f2d02: 0999	ldr	r1, [sp, #0x24]
000f2d04: 0436	adds	r6, #4
000f2d06: b142	cmp	r1, r6
000f2d08: 01d0	beq	#0xf2d0e
000f2d0a: 0835	adds	r5, #8
000f2d0c: e8e7	b	#0xf2ce0
000f2d0e: 0599	ldr	r1, [sp, #0x14]
000f2d10: 5246	mov	r2, sl
000f2d12: 5668	ldr	r6, [r2, #4]
000f2d14: 0b1c	adds	r3, r1, #0
000f2d16: 4344	add	r3, r8
000f2d18: 9b00	lsls	r3, r3, #2
000f2d1a: e318	adds	r3, r4, r3
000f2d1c: 9768	ldr	r7, [r2, #8]
000f2d1e: 186b	ldr	r0, [r3, #0x30]
000f2d20: 9a6a	ldr	r2, [r3, #0x28]
000f2d22: 0a9d	ldr	r5, [sp, #0x28]
000f2d24: 0d90	str	r0, [sp, #0x34]
000f2d26: 002a	cmp	r2, #0
000f2d28: 4ed0	beq	#0xf2dc8
000f2d2a: eb10	asrs	r3, r5, #3
000f2d2c: 0721	movs	r1, #7
000f2d2e: 2940	ands	r1, r5
000f2d30: 9946	mov	sb, r3
000f2d32: 8023	movs	r3, #0x80
000f2d34: 0b41	asrs	r3, r1
000f2d36: 0393	str	r3, [sp, #0xc]
000f2d38: f110	asrs	r1, r6, #3
000f2d3a: 0723	movs	r3, #7
000f2d3c: 3340	ands	r3, r6
000f2d3e: 8b46	mov	fp, r1
000f2d40: 8021	movs	r1, #0x80
000f2d42: 1941	asrs	r1, r3
000f2d44: fb10	asrs	r3, r7, #3
000f2d46: 0893	str	r3, [sp, #0x20]
000f2d48: 0723	movs	r3, #7
000f2d4a: 8a46	mov	sl, r1
000f2d4c: 3b40	ands	r3, r7
000f2d4e: 8021	movs	r1, #0x80
000f2d50: 1941	asrs	r1, r3
000f2d52: 0791	str	r1, [sp, #0x1c]
000f2d54: a446	mov	ip, r4
000f2d56: 14e0	b	#0xf2d82
000f2d58: b342	cmp	r3, r6
000f2d5a: 05d9	bls	#0xf2d68
000f2d5c: 8168	ldr	r1, [r0, #8]
000f2d5e: 5c46	mov	r4, fp
000f2d60: 095d	ldrb	r1, [r1, r4]
000f2d62: 5446	mov	r4, sl
000f2d64: 2142	tst	r1, r4
000f2d66: 15d1	bne	#0xf2d94
000f2d68: bb42	cmp	r3, r7
000f2d6a: 05d9	bls	#0xf2d78
000f2d6c: 8368	ldr	r3, [r0, #8]
000f2d6e: 0899	ldr	r1, [sp, #0x20]
000f2d70: 079c	ldr	r4, [sp, #0x1c]
000f2d72: 5b5c	ldrb	r3, [r3, r1]
000f2d74: 2342	tst	r3, r4
000f2d76: 0dd1	bne	#0xf2d94
000f2d78: 1030	adds	r0, #0x10
000f2d7a: 013a	subs	r2, #1
000f2d7c: 0d90	str	r0, [sp, #0x34]
000f2d7e: 002a	cmp	r2, #0
000f2d80: 21d0	beq	#0xf2dc6
000f2d82: 0368	ldr	r3, [r0]
000f2d84: 9d42	cmp	r5, r3
000f2d86: e7d2	bhs	#0xf2d58
000f2d88: 8168	ldr	r1, [r0, #8]
000f2d8a: 4c46	mov	r4, sb
000f2d8c: 095d	ldrb	r1, [r1, r4]
000f2d8e: 039c	ldr	r4, [sp, #0xc]
000f2d90: 2142	tst	r1, r4
000f2d92: e1d0	beq	#0xf2d58
000f2d94: 6446	mov	r4, ip
000f2d96: 291c	adds	r1, r5, #0
000f2d98: 069a	ldr	r2, [sp, #0x18]
000f2d9a: fff733fd	bl	#0xf2804
000f2d9e: 0028	cmp	r0, #0
000f2da0: 00d0	beq	#0xf2da4
000f2da2: 8fe7	b	#0xf2cc4
000f2da4: 0d98	ldr	r0, [sp, #0x34]
000f2da6: 311c	adds	r1, r6, #0
000f2da8: 069a	ldr	r2, [sp, #0x18]
000f2daa: fff72bfd	bl	#0xf2804
000f2dae: 0028	cmp	r0, #0
000f2db0: 00d0	beq	#0xf2db4
000f2db2: 87e7	b	#0xf2cc4
000f2db4: 0d98	ldr	r0, [sp, #0x34]
000f2db6: 391c	adds	r1, r7, #0
000f2db8: 069a	ldr	r2, [sp, #0x18]
000f2dba: fff723fd	bl	#0xf2804
000f2dbe: 0028	cmp	r0, #0
000f2dc0: 00d1	bne	#0xf2dc4
000f2dc2: 80e7	b	#0xf2cc6
000f2dc4: 7ee7	b	#0xf2cc4
000f2dc6: 6446	mov	r4, ip
000f2dc8: 0599	ldr	r1, [sp, #0x14]
000f2dca: 099a	ldr	r2, [sp, #0x24]
000f2dcc: 081c	adds	r0, r1, #0
000f2dce: 4044	add	r0, r8
000f2dd0: 8000	lsls	r0, r0, #2
000f2dd2: 2830	adds	r0, #0x28
000f2dd4: 2018	adds	r0, r4, r0
000f2dd6: 0699	ldr	r1, [sp, #0x18]
000f2dd8: fff78efc	bl	#0xf26f8
000f2ddc: 0028	cmp	r0, #0
000f2dde: 00d0	beq	#0xf2de2
000f2de0: 70e7	b	#0xf2cc4
000f2de2: 0d98	ldr	r0, [sp, #0x34]
000f2de4: d7e7	b	#0xf2d96
