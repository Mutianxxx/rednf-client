000f4db0: f0b5	push	{r4, r5, r6, r7, lr}
000f4db2: 5f46	mov	r7, fp
000f4db4: 5646	mov	r6, sl
000f4db6: 4d46	mov	r5, sb
000f4db8: 4446	mov	r4, r8
000f4dba: f0b4	push	{r4, r5, r6, r7}
000f4dbc: 83b0	sub	sp, #0xc
000f4dbe: 4768	ldr	r7, [r0, #4]
000f4dc0: 0c9c	ldr	r4, [sp, #0x30]
000f4dc2: 1e1c	adds	r6, r3, #0
000f4dc4: 7d42	rsbs	r5, r7, #0
000f4dc6: a446	mov	ip, r4
000f4dc8: 7c1e	subs	r4, r7, #1
000f4dca: a418	adds	r4, r4, r2
000f4dcc: 2e40	ands	r6, r5
000f4dce: 2c40	ands	r4, r5
000f4dd0: 0096	str	r6, [sp]
000f4dd2: b442	cmp	r4, r6
000f4dd4: 25dc	bgt	#0xf4e22
000f4dd6: c56b	ldr	r5, [r0, #0x3c]
000f4dd8: cb10	asrs	r3, r1, #3
000f4dda: 0268	ldr	r2, [r0]
000f4ddc: eb18	adds	r3, r5, r3
000f4dde: 0725	movs	r5, #7
000f4de0: 2940	ands	r1, r5
000f4de2: 8025	movs	r5, #0x80
000f4de4: 0d41	asrs	r5, r1
000f4de6: 2906	lsls	r1, r5, #0x18
000f4de8: 090e	lsrs	r1, r1, #0x18
000f4dea: 0194	str	r4, [sp, #4]
000f4dec: 019f	ldr	r7, [sp, #4]
000f4dee: 1741	asrs	r7, r2
000f4df0: 002f	cmp	r7, #0
000f4df2: 0fdb	blt	#0xf4e14
000f4df4: 826e	ldr	r2, [r0, #0x68]
000f4df6: 9742	cmp	r7, r2
000f4df8: 0cda	bge	#0xf4e14
000f4dfa: 006f	ldr	r0, [r0, #0x70]
000f4dfc: 041c	adds	r4, r0, #0
000f4dfe: 7c43	muls	r4, r7, r4
000f4e00: 1b1b	subs	r3, r3, r4
000f4e02: 0028	cmp	r0, #0
000f4e04: 03dd	ble	#0xf4e0e
000f4e06: 013a	subs	r2, #1
000f4e08: 041c	adds	r4, r0, #0
000f4e0a: 5443	muls	r4, r2, r4
000f4e0c: 1b19	adds	r3, r3, r4
000f4e0e: 1a78	ldrb	r2, [r3]
000f4e10: 1143	orrs	r1, r2
000f4e12: 1970	strb	r1, [r3]
000f4e14: 03b0	add	sp, #0xc
000f4e16: 3cbc	pop	{r2, r3, r4, r5}
000f4e18: 9046	mov	r8, r2
000f4e1a: 9946	mov	sb, r3
000f4e1c: a246	mov	sl, r4
000f4e1e: ab46	mov	fp, r5
000f4e20: f0bd	pop	{r4, r5, r6, r7, pc}
000f4e22: 6646	mov	r6, ip
000f4e24: f668	ldr	r6, [r6, #0xc]
000f4e26: b146	mov	sb, r6
000f4e28: 009e	ldr	r6, [sp]
000f4e2a: f719	adds	r7, r6, r7
000f4e2c: 0197	str	r7, [sp, #4]
000f4e2e: a742	cmp	r7, r4
000f4e30: f0d1	bne	#0xf4e14
000f4e32: 0727	movs	r7, #7
000f4e34: 4e46	mov	r6, sb
000f4e36: 3e40	ands	r6, r7
000f4e38: b046	mov	r8, r6
000f4e3a: 012e	cmp	r6, #1
000f4e3c: 05d0	beq	#0xf4e4a
000f4e3e: 012e	cmp	r6, #1
000f4e40: 4fdd	ble	#0xf4ee2
000f4e42: 042e	cmp	r6, #4
000f4e44: 0fd0	beq	#0xf4e66
000f4e46: 052e	cmp	r6, #5
000f4e48: e4d1	bne	#0xf4e14
000f4e4a: 6646	mov	r6, ip
000f4e4c: f669	ldr	r6, [r6, #0x1c]
000f4e4e: 0d9f	ldr	r7, [sp, #0x34]
000f4e50: b246	mov	sl, r6
000f4e52: ba45	cmp	sl, r7
000f4e54: 4ed0	beq	#0xf4ef4
000f4e56: 0d9e	ldr	r6, [sp, #0x34]
000f4e58: f669	ldr	r6, [r6, #0x1c]
000f4e5a: b246	mov	sl, r6
000f4e5c: e245	cmp	sl, ip
000f4e5e: 57d0	beq	#0xf4f10
000f4e60: 4746	mov	r7, r8
000f4e62: 012f	cmp	r7, #1
000f4e64: 3fd0	beq	#0xf4ee6
000f4e66: 013a	subs	r2, #1
000f4e68: d318	adds	r3, r2, r3
000f4e6a: da0f	lsrs	r2, r3, #0x1f
000f4e6c: d318	adds	r3, r2, r3
000f4e6e: 8268	ldr	r2, [r0, #8]
000f4e70: 5b10	asrs	r3, r3, #1
000f4e72: 9b18	adds	r3, r3, r2
000f4e74: 1d40	ands	r5, r3
000f4e76: 002d	cmp	r5, #0
000f4e78: 37db	blt	#0xf4eea
000f4e7a: 0368	ldr	r3, [r0]
000f4e7c: 2e1c	adds	r6, r5, #0
000f4e7e: 876e	ldr	r7, [r0, #0x68]
000f4e80: 1e41	asrs	r6, r3
000f4e82: b046	mov	r8, r6
000f4e84: 1a1c	adds	r2, r3, #0
000f4e86: b845	cmp	r8, r7
000f4e88: 26db	blt	#0xf4ed8
000f4e8a: 009d	ldr	r5, [sp]
000f4e8c: 019c	ldr	r4, [sp, #4]
000f4e8e: 0195	str	r5, [sp, #4]
000f4e90: c56b	ldr	r5, [r0, #0x3c]
000f4e92: 1c41	asrs	r4, r3
000f4e94: cb10	asrs	r3, r1, #3
000f4e96: eb18	adds	r3, r5, r3
000f4e98: 0725	movs	r5, #7
000f4e9a: 2940	ands	r1, r5
000f4e9c: 8025	movs	r5, #0x80
000f4e9e: 0d41	asrs	r5, r1
000f4ea0: 2906	lsls	r1, r5, #0x18
000f4ea2: 056f	ldr	r5, [r0, #0x70]
000f4ea4: 090e	lsrs	r1, r1, #0x18
000f4ea6: 2e1c	adds	r6, r5, #0
000f4ea8: 6643	muls	r6, r4, r6
000f4eaa: 9e1b	subs	r6, r3, r6
000f4eac: 002d	cmp	r5, #0
000f4eae: 08dd	ble	#0xf4ec2
000f4eb0: 876e	ldr	r7, [r0, #0x68]
000f4eb2: b846	mov	r8, r7
000f4eb4: 0127	movs	r7, #1
000f4eb6: 7f42	rsbs	r7, r7, #0
000f4eb8: b844	add	r8, r7
000f4eba: 4746	mov	r7, r8
000f4ebc: 6f43	muls	r7, r5, r7
000f4ebe: bc46	mov	ip, r7
000f4ec0: 6644	add	r6, ip
000f4ec2: 002c	cmp	r4, #0
000f4ec4: 92db	blt	#0xf4dec
000f4ec6: 856e	ldr	r5, [r0, #0x68]
000f4ec8: ac42	cmp	r4, r5
000f4eca: 00db	blt	#0xf4ece
000f4ecc: 8ee7	b	#0xf4dec
000f4ece: 3478	ldrb	r4, [r6]
000f4ed0: 2142	tst	r1, r4
000f4ed2: 00d1	bne	#0xf4ed6
000f4ed4: 8ae7	b	#0xf4dec
000f4ed6: 9de7	b	#0xf4e14
000f4ed8: a542	cmp	r5, r4
000f4eda: 08d0	beq	#0xf4eee
000f4edc: 019c	ldr	r4, [sp, #4]
000f4ede: 0195	str	r5, [sp, #4]
000f4ee0: d6e7	b	#0xf4e90
000f4ee2: 002e	cmp	r6, #0
000f4ee4: 96d1	bne	#0xf4e14
000f4ee6: 009d	ldr	r5, [sp]
000f4ee8: c5e7	b	#0xf4e76
000f4eea: 0194	str	r4, [sp, #4]
000f4eec: 0368	ldr	r3, [r0]
000f4eee: 1a1c	adds	r2, r3, #0
000f4ef0: 009c	ldr	r4, [sp]
000f4ef2: cde7	b	#0xf4e90
000f4ef4: 6646	mov	r6, ip
000f4ef6: 3669	ldr	r6, [r6, #0x10]
000f4ef8: 002e	cmp	r6, #0
000f4efa: acdc	bgt	#0xf4e56
000f4efc: 4f46	mov	r7, sb
000f4efe: ff06	lsls	r7, r7, #0x1b
000f4f00: 00d4	bmi	#0xf4f04
000f4f02: 87e7	b	#0xf4e14
000f4f04: 8768	ldr	r7, [r0, #8]
000f4f06: 9e1a	subs	r6, r3, r2
000f4f08: b346	mov	fp, r6
000f4f0a: bb45	cmp	fp, r7
000f4f0c: a3da	bge	#0xf4e56
000f4f0e: 81e7	b	#0xf4e14
000f4f10: 6746	mov	r7, ip
000f4f12: 7f69	ldr	r7, [r7, #0x14]
000f4f14: bc46	mov	ip, r7
000f4f16: 8c45	cmp	ip, r1
000f4f18: a2d1	bne	#0xf4e60
000f4f1a: 4e46	mov	r6, sb
000f4f1c: b606	lsls	r6, r6, #0x1a
000f4f1e: 00d4	bmi	#0xf4f22
000f4f20: 78e7	b	#0xf4e14
000f4f22: 8668	ldr	r6, [r0, #8]
000f4f24: 9f1a	subs	r7, r3, r2
000f4f26: b946	mov	sb, r7
000f4f28: b145	cmp	sb, r6
000f4f2a: 99da	bge	#0xf4e60
000f4f2c: 72e7	b	#0xf4e14
