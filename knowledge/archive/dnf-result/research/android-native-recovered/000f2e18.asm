000f2e18: f0b5	push	{r4, r5, r6, r7, lr}
000f2e1a: 5f46	mov	r7, fp
000f2e1c: 5646	mov	r6, sl
000f2e1e: 4d46	mov	r5, sb
000f2e20: 4446	mov	r4, r8
000f2e22: f0b4	push	{r4, r5, r6, r7}
000f2e24: a5b0	sub	sp, #0x94
000f2e26: 0190	str	r0, [sp, #4]
000f2e28: 0291	str	r1, [sp, #8]
000f2e2a: 0393	str	r3, [sp, #0xc]
000f2e2c: 002a	cmp	r2, #0
000f2e2e: 2edd	ble	#0xf2e8e
000f2e30: 9146	mov	sb, r2
000f2e32: 04aa	add	r2, sp, #0x10
000f2e34: 0027	movs	r7, #0
000f2e36: 9346	mov	fp, r2
000f2e38: 4b46	mov	r3, sb
000f2e3a: ca46	mov	sl, sb
000f2e3c: 102b	cmp	r3, #0x10
000f2e3e: 2ddd	ble	#0xf2e9c
000f2e40: 1022	movs	r2, #0x10
000f2e42: 2023	movs	r3, #0x20
000f2e44: 9246	mov	sl, r2
000f2e46: 9846	mov	r8, r3
000f2e48: 039e	ldr	r6, [sp, #0xc]
000f2e4a: 5d46	mov	r5, fp
000f2e4c: 0024	movs	r4, #0
000f2e4e: 08ce	ldm	r6!, {r3}
000f2e50: 0134	adds	r4, #1
000f2e52: ff18	adds	r7, r7, r3
000f2e54: 381c	adds	r0, r7, #0
000f2e56: f2f7a9ff	bl	#0xe5dac
000f2e5a: 0014	asrs	r0, r0, #0x10
000f2e5c: 01c5	stm	r5!, {r0}
000f2e5e: 4445	cmp	r4, r8
000f2e60: f5d1	bne	#0xf2e4e
000f2e62: 5b46	mov	r3, fp
000f2e64: 0022	movs	r2, #0
000f2e66: 5868	ldr	r0, [r3, #4]
000f2e68: 1968	ldr	r1, [r3]
000f2e6a: 0232	adds	r2, #2
000f2e6c: 411a	subs	r1, r0, r1
000f2e6e: 5960	str	r1, [r3, #4]
000f2e70: 0833	adds	r3, #8
000f2e72: 4245	cmp	r2, r8
000f2e74: f7db	blt	#0xf2e66
000f2e76: 5246	mov	r2, sl
000f2e78: 5b46	mov	r3, fp
000f2e7a: 0198	ldr	r0, [sp, #4]
000f2e7c: 0299	ldr	r1, [sp, #8]
000f2e7e: fff777fd	bl	#0xf2970
000f2e82: 4b46	mov	r3, sb
000f2e84: 5246	mov	r2, sl
000f2e86: 9b1a	subs	r3, r3, r2
000f2e88: 9946	mov	sb, r3
000f2e8a: 002b	cmp	r3, #0
000f2e8c: d4dc	bgt	#0xf2e38
000f2e8e: 25b0	add	sp, #0x94
000f2e90: 3cbc	pop	{r2, r3, r4, r5}
000f2e92: 9046	mov	r8, r2
000f2e94: 9946	mov	sb, r3
000f2e96: a246	mov	sl, r4
000f2e98: ab46	mov	fp, r5
000f2e9a: f0bd	pop	{r4, r5, r6, r7, pc}
000f2e9c: 4a46	mov	r2, sb
000f2e9e: 5200	lsls	r2, r2, #1
000f2ea0: 9046	mov	r8, r2
000f2ea2: 002a	cmp	r2, #0
000f2ea4: d0dc	bgt	#0xf2e48
000f2ea6: dce7	b	#0xf2e62
