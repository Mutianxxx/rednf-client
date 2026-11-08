000f2b5c: f0b5	push	{r4, r5, r6, r7, lr}
000f2b5e: 5f46	mov	r7, fp
000f2b60: 5646	mov	r6, sl
000f2b62: 4d46	mov	r5, sb
000f2b64: 4446	mov	r4, r8
000f2b66: f0b4	push	{r4, r5, r6, r7}
000f2b68: 87b0	sub	sp, #0x1c
000f2b6a: 0392	str	r2, [sp, #0xc]
000f2b6c: 0d1c	adds	r5, r1, #0
000f2b6e: 2c68	ldr	r4, [r5]
000f2b70: 1099	ldr	r1, [sp, #0x40]
000f2b72: 0023	movs	r3, #0
000f2b74: 6700	lsls	r7, r4, #1
000f2b76: 8146	mov	sb, r0
000f2b78: 0093	str	r3, [sp]
000f2b7a: 081c	adds	r0, r1, #0
000f2b7c: 0022	movs	r2, #0
000f2b7e: 8846	mov	r8, r1
000f2b80: 05ae	add	r6, sp, #0x14
000f2b82: 0421	movs	r1, #4
000f2b84: 3b1c	adds	r3, r7, #0
000f2b86: 0196	str	r6, [sp, #4]
000f2b88: f6f79efb	bl	#0xe92c8
000f2b8c: 4a46	mov	r2, sb
000f2b8e: d060	str	r0, [r2, #0xc]
000f2b90: 0598	ldr	r0, [sp, #0x14]
000f2b92: 0028	cmp	r0, #0
000f2b94: 06d0	beq	#0xf2ba4
000f2b96: 07b0	add	sp, #0x1c
000f2b98: 3cbc	pop	{r2, r3, r4, r5}
000f2b9a: 9046	mov	r8, r2
000f2b9c: 9946	mov	sb, r3
000f2b9e: a246	mov	sl, r4
000f2ba0: ab46	mov	fp, r5
000f2ba2: f0bd	pop	{r4, r5, r6, r7, pc}
000f2ba4: 0090	str	r0, [sp]
000f2ba6: 231c	adds	r3, r4, #0
000f2ba8: 4046	mov	r0, r8
000f2baa: 1c21	movs	r1, #0x1c
000f2bac: 0022	movs	r2, #0
000f2bae: 0196	str	r6, [sp, #4]
000f2bb0: f6f78afb	bl	#0xe92c8
000f2bb4: 4b46	mov	r3, sb
000f2bb6: 9860	str	r0, [r3, #8]
000f2bb8: 0598	ldr	r0, [sp, #0x14]
000f2bba: 0028	cmp	r0, #0
000f2bbc: ebd1	bne	#0xf2b96
000f2bbe: 0090	str	r0, [sp]
000f2bc0: 1021	movs	r1, #0x10
000f2bc2: 7b1c	adds	r3, r7, #1
000f2bc4: 4046	mov	r0, r8
000f2bc6: 0022	movs	r2, #0
000f2bc8: 0196	str	r6, [sp, #4]
000f2bca: f6f77dfb	bl	#0xe92c8
000f2bce: 4946	mov	r1, sb
000f2bd0: 8861	str	r0, [r1, #0x18]
000f2bd2: 0598	ldr	r0, [sp, #0x14]
000f2bd4: 0028	cmp	r0, #0
000f2bd6: ded1	bne	#0xf2b96
000f2bd8: ca68	ldr	r2, [r1, #0xc]
000f2bda: a300	lsls	r3, r4, #2
000f2bdc: 0c60	str	r4, [r1]
000f2bde: d318	adds	r3, r2, r3
000f2be0: 0b61	str	r3, [r1, #0x10]
000f2be2: 4860	str	r0, [r1, #4]
000f2be4: 4861	str	r0, [r1, #0x14]
000f2be6: c861	str	r0, [r1, #0x1c]
000f2be8: 8a68	ldr	r2, [r1, #8]
000f2bea: ab68	ldr	r3, [r5, #8]
000f2bec: 002c	cmp	r4, #0
000f2bee: 0ad0	beq	#0xf2c06
000f2bf0: 1968	ldr	r1, [r3]
000f2bf2: 013c	subs	r4, #1
000f2bf4: 1160	str	r1, [r2]
000f2bf6: 5968	ldr	r1, [r3, #4]
000f2bf8: 5160	str	r1, [r2, #4]
000f2bfa: 9968	ldr	r1, [r3, #8]
000f2bfc: 0c33	adds	r3, #0xc
000f2bfe: 1161	str	r1, [r2, #0x10]
000f2c00: 1c32	adds	r2, #0x1c
000f2c02: 002c	cmp	r4, #0
000f2c04: f4d1	bne	#0xf2bf0
000f2c06: 039a	ldr	r2, [sp, #0xc]
000f2c08: 002a	cmp	r2, #0
000f2c0a: 2ed0	beq	#0xf2c6a
000f2c0c: 9368	ldr	r3, [r2, #8]
000f2c0e: 1168	ldr	r1, [r2]
000f2c10: 9a46	mov	sl, r3
000f2c12: 4b46	mov	r3, sb
000f2c14: 8b46	mov	fp, r1
000f2c16: 1a62	str	r2, [r3, #0x20]
000f2c18: 0029	cmp	r1, #0
000f2c1a: 26d0	beq	#0xf2c6a
000f2c1c: 5146	mov	r1, sl
000f2c1e: 0a68	ldr	r2, [r1]
000f2c20: 8e68	ldr	r6, [r1, #8]
000f2c22: 9046	mov	r8, r2
000f2c24: 002a	cmp	r2, #0
000f2c26: 17d0	beq	#0xf2c58
000f2c28: 0027	movs	r7, #0
000f2c2a: 0024	movs	r4, #0
000f2c2c: 0023	movs	r3, #0
000f2c2e: 03e0	b	#0xf2c38
000f2c30: 0134	adds	r4, #1
000f2c32: 4445	cmp	r4, r8
000f2c34: 10d0	beq	#0xf2c58
000f2c36: 2b1c	adds	r3, r5, #0
000f2c38: 5d10	asrs	r5, r3, #1
000f2c3a: 002b	cmp	r3, #0
000f2c3c: 03d1	bne	#0xf2c46
000f2c3e: 3778	ldrb	r7, [r6]
000f2c40: 4025	movs	r5, #0x40
000f2c42: 0136	adds	r6, #1
000f2c44: 8023	movs	r3, #0x80
000f2c46: 3b42	tst	r3, r7
000f2c48: f2d0	beq	#0xf2c30
000f2c4a: 211c	adds	r1, r4, #0
000f2c4c: 4846	mov	r0, sb
000f2c4e: 0134	adds	r4, #1
000f2c50: fef706ff	bl	#0xf1a60
000f2c54: 4445	cmp	r4, r8
000f2c56: eed1	bne	#0xf2c36
000f2c58: 0123	movs	r3, #1
000f2c5a: 5b42	rsbs	r3, r3, #0
000f2c5c: 9b44	add	fp, r3
000f2c5e: 5946	mov	r1, fp
000f2c60: 0029	cmp	r1, #0
000f2c62: 02d0	beq	#0xf2c6a
000f2c64: 1022	movs	r2, #0x10
000f2c66: 9244	add	sl, r2
000f2c68: d8e7	b	#0xf2c1c
000f2c6a: 4b46	mov	r3, sb
000f2c6c: 1d68	ldr	r5, [r3]
000f2c6e: 5b68	ldr	r3, [r3, #4]
000f2c70: ab42	cmp	r3, r5
000f2c72: 09d0	beq	#0xf2c88
000f2c74: 0024	movs	r4, #0
000f2c76: 002d	cmp	r5, #0
000f2c78: 06d0	beq	#0xf2c88
000f2c7a: 211c	adds	r1, r4, #0
000f2c7c: 4846	mov	r0, sb
000f2c7e: 0134	adds	r4, #1
000f2c80: fef7eefe	bl	#0xf1a60
000f2c84: ac42	cmp	r4, r5
000f2c86: f8d1	bne	#0xf2c7a
000f2c88: 0598	ldr	r0, [sp, #0x14]
000f2c8a: 84e7	b	#0xf2b96
