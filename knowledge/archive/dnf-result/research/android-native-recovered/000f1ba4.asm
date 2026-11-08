000f1ba4: f0b5	push	{r4, r5, r6, r7, lr}
000f1ba6: 5f46	mov	r7, fp
000f1ba8: 5646	mov	r6, sl
000f1baa: 4d46	mov	r5, sb
000f1bac: 4446	mov	r4, r8
000f1bae: f0b4	push	{r4, r5, r6, r7}
000f1bb0: c468	ldr	r4, [r0, #0xc]
000f1bb2: 87b0	sub	sp, #0x1c
000f1bb4: 109e	ldr	r6, [sp, #0x40]
000f1bb6: 0294	str	r4, [sp, #8]
000f1bb8: 4468	ldr	r4, [r0, #4]
000f1bba: 002a	cmp	r2, #0
000f1bbc: 77d0	beq	#0xf1cae
000f1bbe: 1027	movs	r7, #0x10
000f1bc0: ba46	mov	sl, r7
000f1bc2: 8220	movs	r0, #0x82
000f1bc4: 8427	movs	r7, #0x84
000f1bc6: c000	lsls	r0, r0, #3
000f1bc8: bf00	lsls	r7, r7, #2
000f1bca: 0490	str	r0, [sp, #0x10]
000f1bcc: 0397	str	r7, [sp, #0xc]
000f1bce: 0193	str	r3, [sp, #4]
000f1bd0: 0d69	ldr	r5, [r1, #0x10]
000f1bd2: 5346	mov	r3, sl
000f1bd4: 486a	ldr	r0, [r1, #0x24]
000f1bd6: 1d42	tst	r5, r3
000f1bd8: 38d1	bne	#0xf1c4c
000f1bda: 1427	movs	r7, #0x14
000f1bdc: cf57	ldrsb	r7, [r1, r7]
000f1bde: bc46	mov	ip, r7
000f1be0: 371c	adds	r7, r6, #0
000f1be2: b445	cmp	ip, r6
000f1be4: 38d0	beq	#0xf1c58
000f1be6: 7742	rsbs	r7, r6, #0
000f1be8: bc45	cmp	ip, r7
000f1bea: 35d0	beq	#0xf1c58
000f1bec: 1523	movs	r3, #0x15
000f1bee: cb56	ldrsb	r3, [r1, r3]
000f1bf0: 9c46	mov	ip, r3
000f1bf2: b445	cmp	ip, r6
000f1bf4: 2fd0	beq	#0xf1c56
000f1bf6: 6745	cmp	r7, ip
000f1bf8: 2ed0	beq	#0xf1c58
000f1bfa: 4023	movs	r3, #0x40
000f1bfc: 1d42	tst	r5, r3
000f1bfe: 25d0	beq	#0xf1c4c
000f1c00: 022e	cmp	r6, #2
000f1c02: 00d1	bne	#0xf1c06
000f1c04: b7e0	b	#0xf1d76
000f1c06: 8027	movs	r7, #0x80
000f1c08: bc46	mov	ip, r7
000f1c0a: 7f00	lsls	r7, r7, #1
000f1c0c: 2f42	tst	r7, r5
000f1c0e: 00d1	bne	#0xf1c12
000f1c10: 6ee0	b	#0xf1cf0
000f1c12: 002c	cmp	r4, #0
000f1c14: 00d1	bne	#0xf1c18
000f1c16: 8fe0	b	#0xf1d38
000f1c18: 9146	mov	sb, r2
000f1c1a: 019a	ldr	r2, [sp, #4]
000f1c1c: 029b	ldr	r3, [sp, #8]
000f1c1e: 8846	mov	r8, r1
000f1c20: 0027	movs	r7, #0
000f1c22: ac46	mov	ip, r5
000f1c24: 111c	adds	r1, r2, #0
000f1c26: 04cb	ldm	r3!, {r2}
000f1c28: 1568	ldr	r5, [r2]
000f1c2a: 451b	subs	r5, r0, r5
000f1c2c: a942	cmp	r1, r5
000f1c2e: 03dd	ble	#0xf1c38
000f1c30: 6d42	rsbs	r5, r5, #0
000f1c32: a942	cmp	r1, r5
000f1c34: 00dd	ble	#0xf1c38
000f1c36: ade0	b	#0xf1d94
000f1c38: 0137	adds	r7, #1
000f1c3a: a742	cmp	r7, r4
000f1c3c: f3d1	bne	#0xf1c26
000f1c3e: 0191	str	r1, [sp, #4]
000f1c40: 4146	mov	r1, r8
000f1c42: 0f6a	ldr	r7, [r1, #0x20]
000f1c44: 4a46	mov	r2, sb
000f1c46: 002f	cmp	r7, #0
000f1c48: 00d1	bne	#0xf1c4c
000f1c4a: 79e0	b	#0xf1d40
000f1c4c: 013a	subs	r2, #1
000f1c4e: 002a	cmp	r2, #0
000f1c50: 2dd0	beq	#0xf1cae
000f1c52: 3031	adds	r1, #0x30
000f1c54: bce7	b	#0xf1bd0
000f1c56: 371c	adds	r7, r6, #0
000f1c58: 002f	cmp	r7, #0
000f1c5a: ced0	beq	#0xf1bfa
000f1c5c: b742	cmp	r7, r6
000f1c5e: 2dd0	beq	#0xf1cbc
000f1c60: 7342	rsbs	r3, r6, #0
000f1c62: 9c46	mov	ip, r3
000f1c64: bc45	cmp	ip, r7
000f1c66: f1d1	bne	#0xf1c4c
000f1c68: 002c	cmp	r4, #0
000f1c6a: efd0	beq	#0xf1c4c
000f1c6c: 029f	ldr	r7, [sp, #8]
000f1c6e: 8846	mov	r8, r1
000f1c70: 0199	ldr	r1, [sp, #4]
000f1c72: 0023	movs	r3, #0
000f1c74: b346	mov	fp, r6
000f1c76: ac46	mov	ip, r5
000f1c78: 261c	adds	r6, r4, #0
000f1c7a: 9146	mov	sb, r2
000f1c7c: 041c	adds	r4, r0, #0
000f1c7e: 3d1c	adds	r5, r7, #0
000f1c80: 181c	adds	r0, r3, #0
000f1c82: 80cd	ldm	r5!, {r7}
000f1c84: 3a68	ldr	r2, [r7]
000f1c86: 7b68	ldr	r3, [r7, #4]
000f1c88: a21a	subs	r2, r4, r2
000f1c8a: d31a	subs	r3, r2, r3
000f1c8c: 9942	cmp	r1, r3
000f1c8e: 03dd	ble	#0xf1c98
000f1c90: 5b42	rsbs	r3, r3, #0
000f1c92: 9942	cmp	r1, r3
000f1c94: 00dd	ble	#0xf1c98
000f1c96: 89e0	b	#0xf1dac
000f1c98: 0130	adds	r0, #1
000f1c9a: b042	cmp	r0, r6
000f1c9c: f1d1	bne	#0xf1c82
000f1c9e: 4a46	mov	r2, sb
000f1ca0: 013a	subs	r2, #1
000f1ca2: 341c	adds	r4, r6, #0
000f1ca4: 0191	str	r1, [sp, #4]
000f1ca6: 5e46	mov	r6, fp
000f1ca8: 4146	mov	r1, r8
000f1caa: 002a	cmp	r2, #0
000f1cac: d1d1	bne	#0xf1c52
000f1cae: 07b0	add	sp, #0x1c
000f1cb0: 3cbc	pop	{r2, r3, r4, r5}
000f1cb2: 9046	mov	r8, r2
000f1cb4: 9946	mov	sb, r3
000f1cb6: a246	mov	sl, r4
000f1cb8: ab46	mov	fp, r5
000f1cba: f0bd	pop	{r4, r5, r6, r7, pc}
000f1cbc: 002c	cmp	r4, #0
000f1cbe: c5d0	beq	#0xf1c4c
000f1cc0: 029f	ldr	r7, [sp, #8]
000f1cc2: 9146	mov	sb, r2
000f1cc4: 019a	ldr	r2, [sp, #4]
000f1cc6: b846	mov	r8, r7
000f1cc8: ac46	mov	ip, r5
000f1cca: 0027	movs	r7, #0
000f1ccc: 4546	mov	r5, r8
000f1cce: 8846	mov	r8, r1
000f1cd0: 011c	adds	r1, r0, #0
000f1cd2: 08cd	ldm	r5!, {r3}
000f1cd4: 1868	ldr	r0, [r3]
000f1cd6: 081a	subs	r0, r1, r0
000f1cd8: 9042	cmp	r0, r2
000f1cda: 02da	bge	#0xf1ce2
000f1cdc: 4042	rsbs	r0, r0, #0
000f1cde: 8242	cmp	r2, r0
000f1ce0: 4edc	bgt	#0xf1d80
000f1ce2: 0137	adds	r7, #1
000f1ce4: a742	cmp	r7, r4
000f1ce6: f4d1	bne	#0xf1cd2
000f1ce8: 0192	str	r2, [sp, #4]
000f1cea: 4146	mov	r1, r8
000f1cec: 4a46	mov	r2, sb
000f1cee: ade7	b	#0xf1c4c
000f1cf0: 6746	mov	r7, ip
000f1cf2: 2f42	tst	r7, r5
000f1cf4: 20d0	beq	#0xf1d38
000f1cf6: 002c	cmp	r4, #0
000f1cf8: 1ed0	beq	#0xf1d38
000f1cfa: 0595	str	r5, [sp, #0x14]
000f1cfc: 9146	mov	sb, r2
000f1cfe: 059a	ldr	r2, [sp, #0x14]
000f1d00: b346	mov	fp, r6
000f1d02: 029b	ldr	r3, [sp, #8]
000f1d04: 261c	adds	r6, r4, #0
000f1d06: 041c	adds	r4, r0, #0
000f1d08: 0198	ldr	r0, [sp, #4]
000f1d0a: 0027	movs	r7, #0
000f1d0c: 3d1c	adds	r5, r7, #0
000f1d0e: 8846	mov	r8, r1
000f1d10: 9446	mov	ip, r2
000f1d12: 80cb	ldm	r3!, {r7}
000f1d14: 3968	ldr	r1, [r7]
000f1d16: 7a68	ldr	r2, [r7, #4]
000f1d18: 611a	subs	r1, r4, r1
000f1d1a: 8a1a	subs	r2, r1, r2
000f1d1c: 9042	cmp	r0, r2
000f1d1e: 02dd	ble	#0xf1d26
000f1d20: 5242	rsbs	r2, r2, #0
000f1d22: 9042	cmp	r0, r2
000f1d24: 4ddc	bgt	#0xf1dc2
000f1d26: 0135	adds	r5, #1
000f1d28: b542	cmp	r5, r6
000f1d2a: f2d1	bne	#0xf1d12
000f1d2c: 0190	str	r0, [sp, #4]
000f1d2e: 4146	mov	r1, r8
000f1d30: 201c	adds	r0, r4, #0
000f1d32: 4a46	mov	r2, sb
000f1d34: 341c	adds	r4, r6, #0
000f1d36: 5e46	mov	r6, fp
000f1d38: 0f6a	ldr	r7, [r1, #0x20]
000f1d3a: 002f	cmp	r7, #0
000f1d3c: 00d0	beq	#0xf1d40
000f1d3e: 85e7	b	#0xf1c4c
000f1d40: 002c	cmp	r4, #0
000f1d42: 00d1	bne	#0xf1d46
000f1d44: 82e7	b	#0xf1c4c
000f1d46: 019b	ldr	r3, [sp, #4]
000f1d48: 029f	ldr	r7, [sp, #8]
000f1d4a: 9046	mov	r8, r2
000f1d4c: 9946	mov	sb, r3
000f1d4e: 0025	movs	r5, #0
000f1d50: 8c46	mov	ip, r1
000f1d52: 3b1c	adds	r3, r7, #0
000f1d54: 021c	adds	r2, r0, #0
000f1d56: 80cb	ldm	r3!, {r7}
000f1d58: 3868	ldr	r0, [r7]
000f1d5a: 8242	cmp	r2, r0
000f1d5c: 03db	blt	#0xf1d66
000f1d5e: 7968	ldr	r1, [r7, #4]
000f1d60: 4018	adds	r0, r0, r1
000f1d62: 8242	cmp	r2, r0
000f1d64: 39dd	ble	#0xf1dda
000f1d66: 0135	adds	r5, #1
000f1d68: a542	cmp	r5, r4
000f1d6a: f4d1	bne	#0xf1d56
000f1d6c: 4846	mov	r0, sb
000f1d6e: 6146	mov	r1, ip
000f1d70: 4246	mov	r2, r8
000f1d72: 0190	str	r0, [sp, #4]
000f1d74: 6ae7	b	#0xf1c4c
000f1d76: 8023	movs	r3, #0x80
000f1d78: 5f00	lsls	r7, r3, #1
000f1d7a: bc46	mov	ip, r7
000f1d7c: 8027	movs	r7, #0x80
000f1d7e: 45e7	b	#0xf1c0c
000f1d80: 101c	adds	r0, r2, #0
000f1d82: 0190	str	r0, [sp, #4]
000f1d84: 0398	ldr	r0, [sp, #0xc]
000f1d86: 6546	mov	r5, ip
000f1d88: 4146	mov	r1, r8
000f1d8a: 0543	orrs	r5, r0
000f1d8c: 4a46	mov	r2, sb
000f1d8e: 0d61	str	r5, [r1, #0x10]
000f1d90: 0b62	str	r3, [r1, #0x20]
000f1d92: 5be7	b	#0xf1c4c
000f1d94: 6546	mov	r5, ip
000f1d96: cc46	mov	ip, sb
000f1d98: 9146	mov	sb, r2
000f1d9a: 0191	str	r1, [sp, #4]
000f1d9c: 4f46	mov	r7, sb
000f1d9e: 4146	mov	r1, r8
000f1da0: 0f62	str	r7, [r1, #0x20]
000f1da2: 039b	ldr	r3, [sp, #0xc]
000f1da4: 6246	mov	r2, ip
000f1da6: 1d43	orrs	r5, r3
000f1da8: 0d61	str	r5, [r1, #0x10]
000f1daa: c6e7	b	#0xf1d3a
000f1dac: 0498	ldr	r0, [sp, #0x10]
000f1dae: 6546	mov	r5, ip
000f1db0: 0191	str	r1, [sp, #4]
000f1db2: 0543	orrs	r5, r0
000f1db4: 4146	mov	r1, r8
000f1db6: 341c	adds	r4, r6, #0
000f1db8: 4a46	mov	r2, sb
000f1dba: 5e46	mov	r6, fp
000f1dbc: 0d61	str	r5, [r1, #0x10]
000f1dbe: 0f62	str	r7, [r1, #0x20]
000f1dc0: 44e7	b	#0xf1c4c
000f1dc2: 4146	mov	r1, r8
000f1dc4: 0190	str	r0, [sp, #4]
000f1dc6: 0f62	str	r7, [r1, #0x20]
000f1dc8: 049b	ldr	r3, [sp, #0x10]
000f1dca: 6546	mov	r5, ip
000f1dcc: 201c	adds	r0, r4, #0
000f1dce: 1d43	orrs	r5, r3
000f1dd0: 341c	adds	r4, r6, #0
000f1dd2: 4a46	mov	r2, sb
000f1dd4: 5e46	mov	r6, fp
000f1dd6: 0d61	str	r5, [r1, #0x10]
000f1dd8: afe7	b	#0xf1d3a
000f1dda: 6146	mov	r1, ip
000f1ddc: 4846	mov	r0, sb
000f1dde: 0190	str	r0, [sp, #4]
000f1de0: 4246	mov	r2, r8
000f1de2: 0f62	str	r7, [r1, #0x20]
000f1de4: 32e7	b	#0xf1c4c
