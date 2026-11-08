000f4be0: f0b5	push	{r4, r5, r6, r7, lr}
000f4be2: 5f46	mov	r7, fp
000f4be4: 5646	mov	r6, sl
000f4be6: 4d46	mov	r5, sb
000f4be8: 4446	mov	r4, r8
000f4bea: f0b4	push	{r4, r5, r6, r7}
000f4bec: 4768	ldr	r7, [r0, #4]
000f4bee: 83b0	sub	sp, #0xc
000f4bf0: 0091	str	r1, [sp]
000f4bf2: 7c1e	subs	r4, r7, #1
000f4bf4: 0c99	ldr	r1, [sp, #0x30]
000f4bf6: 7d42	rsbs	r5, r7, #0
000f4bf8: a418	adds	r4, r4, r2
000f4bfa: 1e1c	adds	r6, r3, #0
000f4bfc: 2c40	ands	r4, r5
000f4bfe: 2e40	ands	r6, r5
000f4c00: 8c46	mov	ip, r1
000f4c02: b442	cmp	r4, r6
000f4c04: 2cdc	bgt	#0xf4c60
000f4c06: 0368	ldr	r3, [r0]
000f4c08: 0194	str	r4, [sp, #4]
000f4c0a: 019f	ldr	r7, [sp, #4]
000f4c0c: 1f41	asrs	r7, r3
000f4c0e: 002f	cmp	r7, #0
000f4c10: 1fdb	blt	#0xf4c52
000f4c12: 038f	ldrh	r3, [r0, #0x38]
000f4c14: 9f42	cmp	r7, r3
000f4c16: 1cda	bge	#0xf4c52
000f4c18: 0723	movs	r3, #7
000f4c1a: 7a03	lsls	r2, r7, #0xd
000f4c1c: 9e21	movs	r1, #0x9e
000f4c1e: 1f40	ands	r7, r3
000f4c20: 120c	lsrs	r2, r2, #0x10
000f4c22: 455e	ldrsh	r5, [r0, r1]
000f4c24: 1304	lsls	r3, r2, #0x10
000f4c26: 1c14	asrs	r4, r3, #0x10
000f4c28: a542	cmp	r5, r4
000f4c2a: 00dd	ble	#0xf4c2e
000f4c2c: 4252	strh	r2, [r0, r1]
000f4c2e: a021	movs	r1, #0xa0
000f4c30: 455e	ldrsh	r5, [r0, r1]
000f4c32: 1c14	asrs	r4, r3, #0x10
000f4c34: a542	cmp	r5, r4
000f4c36: 00da	bge	#0xf4c3a
000f4c38: 4252	strh	r2, [r0, r1]
000f4c3a: 9422	movs	r2, #0x94
000f4c3c: 8258	ldr	r2, [r0, r2]
000f4c3e: 1b14	asrs	r3, r3, #0x10
000f4c40: 9b18	adds	r3, r3, r2
000f4c42: c26b	ldr	r2, [r0, #0x3c]
000f4c44: d318	adds	r3, r2, r3
000f4c46: 8022	movs	r2, #0x80
000f4c48: 3a41	asrs	r2, r7
000f4c4a: 171c	adds	r7, r2, #0
000f4c4c: 1a78	ldrb	r2, [r3]
000f4c4e: 1743	orrs	r7, r2
000f4c50: 1f70	strb	r7, [r3]
000f4c52: 03b0	add	sp, #0xc
000f4c54: 3cbc	pop	{r2, r3, r4, r5}
000f4c56: 9046	mov	r8, r2
000f4c58: 9946	mov	sb, r3
000f4c5a: a246	mov	sl, r4
000f4c5c: ab46	mov	fp, r5
000f4c5e: f0bd	pop	{r4, r5, r6, r7, pc}
000f4c60: c968	ldr	r1, [r1, #0xc]
000f4c62: f719	adds	r7, r6, r7
000f4c64: 0197	str	r7, [sp, #4]
000f4c66: 8946	mov	sb, r1
000f4c68: a742	cmp	r7, r4
000f4c6a: f2d1	bne	#0xf4c52
000f4c6c: 0727	movs	r7, #7
000f4c6e: 3940	ands	r1, r7
000f4c70: 8846	mov	r8, r1
000f4c72: 0129	cmp	r1, #1
000f4c74: 05d0	beq	#0xf4c82
000f4c76: 0129	cmp	r1, #1
000f4c78: 3fdd	ble	#0xf4cfa
000f4c7a: 0429	cmp	r1, #4
000f4c7c: 0fd0	beq	#0xf4c9e
000f4c7e: 0529	cmp	r1, #5
000f4c80: e7d1	bne	#0xf4c52
000f4c82: 6146	mov	r1, ip
000f4c84: c969	ldr	r1, [r1, #0x1c]
000f4c86: 0d9f	ldr	r7, [sp, #0x34]
000f4c88: 8a46	mov	sl, r1
000f4c8a: ba45	cmp	sl, r7
000f4c8c: 3ed0	beq	#0xf4d0c
000f4c8e: 0d99	ldr	r1, [sp, #0x34]
000f4c90: c969	ldr	r1, [r1, #0x1c]
000f4c92: 8a46	mov	sl, r1
000f4c94: e245	cmp	sl, ip
000f4c96: 46d0	beq	#0xf4d26
000f4c98: 4746	mov	r7, r8
000f4c9a: 012f	cmp	r7, #1
000f4c9c: 2fd0	beq	#0xf4cfe
000f4c9e: 013a	subs	r2, #1
000f4ca0: d318	adds	r3, r2, r3
000f4ca2: da0f	lsrs	r2, r3, #0x1f
000f4ca4: d318	adds	r3, r2, r3
000f4ca6: 8268	ldr	r2, [r0, #8]
000f4ca8: 5b10	asrs	r3, r3, #1
000f4caa: 9b18	adds	r3, r3, r2
000f4cac: 1d40	ands	r5, r3
000f4cae: 002d	cmp	r5, #0
000f4cb0: 27db	blt	#0xf4d02
000f4cb2: 0268	ldr	r2, [r0]
000f4cb4: 291c	adds	r1, r5, #0
000f4cb6: 1141	asrs	r1, r2
000f4cb8: 8c46	mov	ip, r1
000f4cba: 018f	ldrh	r1, [r0, #0x38]
000f4cbc: 131c	adds	r3, r2, #0
000f4cbe: 8c45	cmp	ip, r1
000f4cc0: 16db	blt	#0xf4cf0
000f4cc2: 0199	ldr	r1, [sp, #4]
000f4cc4: 0196	str	r6, [sp, #4]
000f4cc6: 1141	asrs	r1, r2
000f4cc8: 0a1e	subs	r2, r1, #0
000f4cca: 9edb	blt	#0xf4c0a
000f4ccc: 018f	ldrh	r1, [r0, #0x38]
000f4cce: 8a42	cmp	r2, r1
000f4cd0: 9bda	bge	#0xf4c0a
000f4cd2: c56b	ldr	r5, [r0, #0x3c]
000f4cd4: 9424	movs	r4, #0x94
000f4cd6: 5103	lsls	r1, r2, #0xd
000f4cd8: 0459	ldr	r4, [r0, r4]
000f4cda: 0914	asrs	r1, r1, #0x10
000f4cdc: 6918	adds	r1, r5, r1
000f4cde: 095d	ldrb	r1, [r1, r4]
000f4ce0: 0724	movs	r4, #7
000f4ce2: 2240	ands	r2, r4
000f4ce4: 8024	movs	r4, #0x80
000f4ce6: 1441	asrs	r4, r2
000f4ce8: 2142	tst	r1, r4
000f4cea: 00d1	bne	#0xf4cee
000f4cec: 8de7	b	#0xf4c0a
000f4cee: b0e7	b	#0xf4c52
000f4cf0: a542	cmp	r5, r4
000f4cf2: 08d0	beq	#0xf4d06
000f4cf4: 0199	ldr	r1, [sp, #4]
000f4cf6: 0195	str	r5, [sp, #4]
000f4cf8: e5e7	b	#0xf4cc6
000f4cfa: 0029	cmp	r1, #0
000f4cfc: a9d1	bne	#0xf4c52
000f4cfe: 351c	adds	r5, r6, #0
000f4d00: d5e7	b	#0xf4cae
000f4d02: 0268	ldr	r2, [r0]
000f4d04: 0194	str	r4, [sp, #4]
000f4d06: 131c	adds	r3, r2, #0
000f4d08: 311c	adds	r1, r6, #0
000f4d0a: dce7	b	#0xf4cc6
000f4d0c: 6146	mov	r1, ip
000f4d0e: 0969	ldr	r1, [r1, #0x10]
000f4d10: 0029	cmp	r1, #0
000f4d12: bcdc	bgt	#0xf4c8e
000f4d14: 4f46	mov	r7, sb
000f4d16: ff06	lsls	r7, r7, #0x1b
000f4d18: 9bd5	bpl	#0xf4c52
000f4d1a: 8768	ldr	r7, [r0, #8]
000f4d1c: 991a	subs	r1, r3, r2
000f4d1e: 8b46	mov	fp, r1
000f4d20: bb45	cmp	fp, r7
000f4d22: b4da	bge	#0xf4c8e
000f4d24: 95e7	b	#0xf4c52
000f4d26: 6746	mov	r7, ip
000f4d28: 7f69	ldr	r7, [r7, #0x14]
000f4d2a: 0099	ldr	r1, [sp]
000f4d2c: bc46	mov	ip, r7
000f4d2e: 8c45	cmp	ip, r1
000f4d30: b2d1	bne	#0xf4c98
000f4d32: 4f46	mov	r7, sb
000f4d34: bf06	lsls	r7, r7, #0x1a
000f4d36: 00d4	bmi	#0xf4d3a
000f4d38: 8be7	b	#0xf4c52
000f4d3a: 991a	subs	r1, r3, r2
000f4d3c: 8c46	mov	ip, r1
000f4d3e: 8168	ldr	r1, [r0, #8]
000f4d40: 8c45	cmp	ip, r1
000f4d42: a9da	bge	#0xf4c98
000f4d44: 85e7	b	#0xf4c52
