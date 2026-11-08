000f3e74: f0b5	push	{r4, r5, r6, r7, lr}
000f3e76: 5f46	mov	r7, fp
000f3e78: 5646	mov	r6, sl
000f3e7a: 4d46	mov	r5, sb
000f3e7c: 4446	mov	r4, r8
000f3e7e: f0b4	push	{r4, r5, r6, r7}
000f3e80: 8b46	mov	fp, r1
000f3e82: 83b0	sub	sp, #0xc
000f3e84: 5845	cmp	r0, fp
000f3e86: 39d2	bhs	#0xf3efc
000f3e88: 0028	cmp	r0, #0
000f3e8a: 37d0	beq	#0xf3efc
000f3e8c: 464b	ldr	r3, [pc, #0x118]
000f3e8e: 0678	ldrb	r6, [r0]
000f3e90: 3427	movs	r7, #0x34
000f3e92: 9a46	mov	sl, r3
000f3e94: fa44	add	sl, pc
000f3e96: 454b	ldr	r3, [pc, #0x114]
000f3e98: 5546	mov	r5, sl
000f3e9a: 0235	adds	r5, #2
000f3e9c: 0195	str	r5, [sp, #4]
000f3e9e: 9c46	mov	ip, r3
000f3ea0: 0225	movs	r5, #2
000f3ea2: fc44	add	ip, pc
000f3ea4: a946	mov	sb, r5
000f3ea6: 8046	mov	r8, r0
000f3ea8: 0024	movs	r4, #0
000f3eaa: 7f21	movs	r1, #0x7f
000f3eac: e144	add	sb, ip
000f3eae: 381c	adds	r0, r7, #0
000f3eb0: 019d	ldr	r5, [sp, #4]
000f3eb2: 2318	adds	r3, r4, r0
000f3eb4: 5b10	asrs	r3, r3, #1
000f3eb6: 5a00	lsls	r2, r3, #1
000f3eb8: aa18	adds	r2, r5, r2
000f3eba: 1778	ldrb	r7, [r2]
000f3ebc: 5578	ldrb	r5, [r2, #1]
000f3ebe: 3f02	lsls	r7, r7, #8
000f3ec0: 2f43	orrs	r7, r5
000f3ec2: 5744	add	r7, sl
000f3ec4: 3d78	ldrb	r5, [r7]
000f3ec6: 2a1c	adds	r2, r5, #0
000f3ec8: 0a40	ands	r2, r1
000f3eca: b242	cmp	r2, r6
000f3ecc: 11d1	bne	#0xf3ef2
000f3ece: 1de0	b	#0xf3f0c
000f3ed0: 181c	adds	r0, r3, #0
000f3ed2: 9c42	cmp	r4, r3
000f3ed4: 12da	bge	#0xf3efc
000f3ed6: 1b19	adds	r3, r3, r4
000f3ed8: 5b10	asrs	r3, r3, #1
000f3eda: 5a00	lsls	r2, r3, #1
000f3edc: 4a44	add	r2, sb
000f3ede: 1778	ldrb	r7, [r2]
000f3ee0: 5578	ldrb	r5, [r2, #1]
000f3ee2: 3f02	lsls	r7, r7, #8
000f3ee4: 2f43	orrs	r7, r5
000f3ee6: 6744	add	r7, ip
000f3ee8: 3d78	ldrb	r5, [r7]
000f3eea: 2a1c	adds	r2, r5, #0
000f3eec: 0a40	ands	r2, r1
000f3eee: b242	cmp	r2, r6
000f3ef0: 0cd0	beq	#0xf3f0c
000f3ef2: 9642	cmp	r6, r2
000f3ef4: ecdd	ble	#0xf3ed0
000f3ef6: 5c1c	adds	r4, r3, #1
000f3ef8: a042	cmp	r0, r4
000f3efa: d9dc	bgt	#0xf3eb0
000f3efc: 0020	movs	r0, #0
000f3efe: 03b0	add	sp, #0xc
000f3f00: 3cbc	pop	{r2, r3, r4, r5}
000f3f02: 9046	mov	r8, r2
000f3f04: 9946	mov	sb, r3
000f3f06: a246	mov	sl, r4
000f3f08: ab46	mov	fp, r5
000f3f0a: f0bd	pop	{r4, r5, r6, r7, pc}
000f3f0c: 4046	mov	r0, r8
000f3f0e: 0130	adds	r0, #1
000f3f10: 8446	mov	ip, r0
000f3f12: 8345	cmp	fp, r0
000f3f14: 45d9	bls	#0xf3fa2
000f3f16: 264b	ldr	r3, [pc, #0x98]
000f3f18: 2648	ldr	r0, [pc, #0x98]
000f3f1a: 7f24	movs	r4, #0x7f
000f3f1c: 9946	mov	sb, r3
000f3f1e: f944	add	sb, pc
000f3f20: 7844	add	r0, pc
000f3f22: 6346	mov	r3, ip
000f3f24: 1e78	ldrb	r6, [r3]
000f3f26: 2b06	lsls	r3, r5, #0x18
000f3f28: 32d4	bmi	#0xf3f90
000f3f2a: 7b78	ldrb	r3, [r7, #1]
000f3f2c: 791c	adds	r1, r7, #1
000f3f2e: 1a1c	adds	r2, r3, #0
000f3f30: 1b06	lsls	r3, r3, #0x18
000f3f32: 2240	ands	r2, r4
000f3f34: 002b	cmp	r3, #0
000f3f36: 32db	blt	#0xf3f9e
000f3f38: 002a	cmp	r2, #0
000f3f3a: dfd0	beq	#0xf3efc
000f3f3c: 4b1c	adds	r3, r1, #1
000f3f3e: 4f78	ldrb	r7, [r1, #1]
000f3f40: 5d78	ldrb	r5, [r3, #1]
000f3f42: 3f02	lsls	r7, r7, #8
000f3f44: 2f43	orrs	r7, r5
000f3f46: 4f44	add	r7, sb
000f3f48: 3978	ldrb	r1, [r7]
000f3f4a: 0d1c	adds	r5, r1, #0
000f3f4c: 2540	ands	r5, r4
000f3f4e: b542	cmp	r5, r6
000f3f50: 0bd1	bne	#0xf3f6a
000f3f52: 0ee0	b	#0xf3f72
000f3f54: 0233	adds	r3, #2
000f3f56: 1f78	ldrb	r7, [r3]
000f3f58: 5978	ldrb	r1, [r3, #1]
000f3f5a: 3f02	lsls	r7, r7, #8
000f3f5c: 0f43	orrs	r7, r1
000f3f5e: c719	adds	r7, r0, r7
000f3f60: 3978	ldrb	r1, [r7]
000f3f62: 0d1c	adds	r5, r1, #0
000f3f64: 2540	ands	r5, r4
000f3f66: b542	cmp	r5, r6
000f3f68: 03d0	beq	#0xf3f72
000f3f6a: 013a	subs	r2, #1
000f3f6c: 002a	cmp	r2, #0
000f3f6e: f1d1	bne	#0xf3f54
000f3f70: c4e7	b	#0xf3efc
000f3f72: 0d1c	adds	r5, r1, #0
000f3f74: 0123	movs	r3, #1
000f3f76: 9c44	add	ip, r3
000f3f78: dc45	cmp	ip, fp
000f3f7a: d2d1	bne	#0xf3f22
000f3f7c: 7f2d	cmp	r5, #0x7f
000f3f7e: bdd8	bhi	#0xf3efc
000f3f80: 7b78	ldrb	r3, [r7, #1]
000f3f82: 7f2b	cmp	r3, #0x7f
000f3f84: bad9	bls	#0xf3efc
000f3f86: b878	ldrb	r0, [r7, #2]
000f3f88: fb78	ldrb	r3, [r7, #3]
000f3f8a: 0002	lsls	r0, r0, #8
000f3f8c: 1843	orrs	r0, r3
000f3f8e: b6e7	b	#0xf3efe
000f3f90: 0137	adds	r7, #1
000f3f92: 3d78	ldrb	r5, [r7]
000f3f94: 2b1c	adds	r3, r5, #0
000f3f96: 2340	ands	r3, r4
000f3f98: b342	cmp	r3, r6
000f3f9a: afd1	bne	#0xf3efc
000f3f9c: eae7	b	#0xf3f74
000f3f9e: f91c	adds	r1, r7, #3
000f3fa0: cae7	b	#0xf3f38
000f3fa2: 3d78	ldrb	r5, [r7]
000f3fa4: eae7	b	#0xf3f7c
000f3fa6: c046	mov	r8, r8
000f3fa8: 5c4d	ldr	r5, [pc, #0x170]
000f3faa: 0400	movs	r4, r0
000f3fac: 4e4d	ldr	r5, [pc, #0x138]
000f3fae: 0400	movs	r4, r0
000f3fb0: d24c	ldr	r4, [pc, #0x348]
000f3fb2: 0400	movs	r4, r0
000f3fb4: d04c	ldr	r4, [pc, #0x340]
000f3fb6: 0400	movs	r4, r0
