000f6f88: f0b5	push	{r4, r5, r6, r7, lr}
000f6f8a: 4f46	mov	r7, sb
000f6f8c: 4646	mov	r6, r8
000f6f8e: c0b4	push	{r6, r7}
000f6f90: c169	ldr	r1, [r0, #0x1c]
000f6f92: 8146	mov	sb, r0
000f6f94: 481c	adds	r0, r1, #1
000f6f96: 37d0	beq	#0xf7008
000f6f98: 4b46	mov	r3, sb
000f6f9a: 9c6a	ldr	r4, [r3, #0x28]
000f6f9c: 5a6a	ldr	r2, [r3, #0x24]
000f6f9e: a046	mov	r8, r4
000f6fa0: 4245	cmp	r2, r8
000f6fa2: 31d2	bhs	#0xf7008
000f6fa4: 5300	lsls	r3, r2, #1
000f6fa6: 4d46	mov	r5, sb
000f6fa8: 9b18	adds	r3, r3, r2
000f6faa: 2869	ldr	r0, [r5, #0x10]
000f6fac: 9b00	lsls	r3, r3, #2
000f6fae: 1033	adds	r3, #0x10
000f6fb0: 0131	adds	r1, #1
000f6fb2: c318	adds	r3, r0, r3
000f6fb4: 1d78	ldrb	r5, [r3]
000f6fb6: 5c78	ldrb	r4, [r3, #1]
000f6fb8: 187a	ldrb	r0, [r3, #8]
000f6fba: 2d06	lsls	r5, r5, #0x18
000f6fbc: 2404	lsls	r4, r4, #0x10
000f6fbe: 2c43	orrs	r4, r5
000f6fc0: dd78	ldrb	r5, [r3, #3]
000f6fc2: 8446	mov	ip, r0
000f6fc4: 9e7a	ldrb	r6, [r3, #0xa]
000f6fc6: 2c43	orrs	r4, r5
000f6fc8: 9d78	ldrb	r5, [r3, #2]
000f6fca: 587a	ldrb	r0, [r3, #9]
000f6fcc: df7a	ldrb	r7, [r3, #0xb]
000f6fce: 2d02	lsls	r5, r5, #8
000f6fd0: 2c43	orrs	r4, r5
000f6fd2: a142	cmp	r1, r4
000f6fd4: 00d2	bhs	#0xf6fd8
000f6fd6: 211c	adds	r1, r4, #0
000f6fd8: 1d79	ldrb	r5, [r3, #4]
000f6fda: 5c79	ldrb	r4, [r3, #5]
000f6fdc: 2d06	lsls	r5, r5, #0x18
000f6fde: 2404	lsls	r4, r4, #0x10
000f6fe0: 2c43	orrs	r4, r5
000f6fe2: dd79	ldrb	r5, [r3, #7]
000f6fe4: 2c43	orrs	r4, r5
000f6fe6: 9d79	ldrb	r5, [r3, #6]
000f6fe8: 2d02	lsls	r5, r5, #8
000f6fea: 2c43	orrs	r4, r5
000f6fec: 8c42	cmp	r4, r1
000f6fee: 07d3	blo	#0xf7000
000f6ff0: 6546	mov	r5, ip
000f6ff2: 2c06	lsls	r4, r5, #0x18
000f6ff4: 0004	lsls	r0, r0, #0x10
000f6ff6: 2043	orrs	r0, r4
000f6ff8: 0743	orrs	r7, r0
000f6ffa: 3602	lsls	r6, r6, #8
000f6ffc: 3e43	orrs	r6, r7
000f6ffe: 0ad1	bne	#0xf7016
000f7000: 0132	adds	r2, #1
000f7002: 0c33	adds	r3, #0xc
000f7004: 4245	cmp	r2, r8
000f7006: d5d3	blo	#0xf6fb4
000f7008: 0023	movs	r3, #0
000f700a: 4a46	mov	r2, sb
000f700c: 1376	strb	r3, [r2, #0x18]
000f700e: 0cbc	pop	{r2, r3}
000f7010: 9046	mov	r8, r2
000f7012: 9946	mov	sb, r3
000f7014: f0bd	pop	{r4, r5, r6, r7, pc}
000f7016: 4846	mov	r0, sb
000f7018: c161	str	r1, [r0, #0x1c]
000f701a: 0662	str	r6, [r0, #0x20]
000f701c: 4262	str	r2, [r0, #0x24]
000f701e: f6e7	b	#0xf700e
