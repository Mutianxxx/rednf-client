000f6d0c: f0b5	push	{r4, r5, r6, r7, lr}
000f6d0e: 5f46	mov	r7, fp
000f6d10: 5646	mov	r6, sl
000f6d12: 4d46	mov	r5, sb
000f6d14: 4446	mov	r4, r8
000f6d16: f0b4	push	{r4, r5, r6, r7}
000f6d18: c269	ldr	r2, [r0, #0x1c]
000f6d1a: 531c	adds	r3, r2, #1
000f6d1c: 4dd0	beq	#0xf6dba
000f6d1e: 866a	ldr	r6, [r0, #0x28]
000f6d20: 416a	ldr	r1, [r0, #0x24]
000f6d22: b346	mov	fp, r6
000f6d24: 5945	cmp	r1, fp
000f6d26: 48d2	bhs	#0xf6dba
000f6d28: 4b00	lsls	r3, r1, #1
000f6d2a: 5b18	adds	r3, r3, r1
000f6d2c: 0469	ldr	r4, [r0, #0x10]
000f6d2e: 9b00	lsls	r3, r3, #2
000f6d30: 1033	adds	r3, #0x10
000f6d32: 0132	adds	r2, #1
000f6d34: e318	adds	r3, r4, r3
000f6d36: 1d78	ldrb	r5, [r3]
000f6d38: 5c78	ldrb	r4, [r3, #1]
000f6d3a: 1e79	ldrb	r6, [r3, #4]
000f6d3c: 2d06	lsls	r5, r5, #0x18
000f6d3e: 2404	lsls	r4, r4, #0x10
000f6d40: 2c43	orrs	r4, r5
000f6d42: dd78	ldrb	r5, [r3, #3]
000f6d44: 3606	lsls	r6, r6, #0x18
000f6d46: 1f7a	ldrb	r7, [r3, #8]
000f6d48: 2c43	orrs	r4, r5
000f6d4a: 9d78	ldrb	r5, [r3, #2]
000f6d4c: b946	mov	sb, r7
000f6d4e: 9f7a	ldrb	r7, [r3, #0xa]
000f6d50: 2d02	lsls	r5, r5, #8
000f6d52: 2c43	orrs	r4, r5
000f6d54: 5d79	ldrb	r5, [r3, #5]
000f6d56: ba46	mov	sl, r7
000f6d58: 2d04	lsls	r5, r5, #0x10
000f6d5a: 3543	orrs	r5, r6
000f6d5c: de79	ldrb	r6, [r3, #7]
000f6d5e: 3543	orrs	r5, r6
000f6d60: 9e79	ldrb	r6, [r3, #6]
000f6d62: 3602	lsls	r6, r6, #8
000f6d64: 3543	orrs	r5, r6
000f6d66: 5e7a	ldrb	r6, [r3, #9]
000f6d68: b046	mov	r8, r6
000f6d6a: de7a	ldrb	r6, [r3, #0xb]
000f6d6c: b446	mov	ip, r6
000f6d6e: a242	cmp	r2, r4
000f6d70: 00d2	bhs	#0xf6d74
000f6d72: 221c	adds	r2, r4, #0
000f6d74: 9542	cmp	r5, r2
000f6d76: 1cd3	blo	#0xf6db2
000f6d78: 4f46	mov	r7, sb
000f6d7a: 4646	mov	r6, r8
000f6d7c: 3604	lsls	r6, r6, #0x10
000f6d7e: 3f06	lsls	r7, r7, #0x18
000f6d80: 3743	orrs	r7, r6
000f6d82: 6646	mov	r6, ip
000f6d84: 3743	orrs	r7, r6
000f6d86: bc46	mov	ip, r7
000f6d88: 5746	mov	r7, sl
000f6d8a: 3e02	lsls	r6, r7, #8
000f6d8c: 6746	mov	r7, ip
000f6d8e: 3e43	orrs	r6, r7
000f6d90: 341b	subs	r4, r6, r4
000f6d92: 1419	adds	r4, r2, r4
000f6d94: 002c	cmp	r4, #0
000f6d96: 03d1	bne	#0xf6da0
000f6d98: 0132	adds	r2, #1
000f6d9a: 9542	cmp	r5, r2
000f6d9c: 09d3	blo	#0xf6db2
000f6d9e: 0124	movs	r4, #1
000f6da0: c261	str	r2, [r0, #0x1c]
000f6da2: 0462	str	r4, [r0, #0x20]
000f6da4: 4162	str	r1, [r0, #0x24]
000f6da6: 3cbc	pop	{r2, r3, r4, r5}
000f6da8: 9046	mov	r8, r2
000f6daa: 9946	mov	sb, r3
000f6dac: a246	mov	sl, r4
000f6dae: ab46	mov	fp, r5
000f6db0: f0bd	pop	{r4, r5, r6, r7, pc}
000f6db2: 0131	adds	r1, #1
000f6db4: 0c33	adds	r3, #0xc
000f6db6: 5945	cmp	r1, fp
000f6db8: bdd3	blo	#0xf6d36
000f6dba: 0023	movs	r3, #0
000f6dbc: 0376	strb	r3, [r0, #0x18]
000f6dbe: f2e7	b	#0xf6da6
