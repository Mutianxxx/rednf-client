000f6dc0: f0b5	push	{r4, r5, r6, r7, lr}
000f6dc2: 5f46	mov	r7, fp
000f6dc4: 5646	mov	r6, sl
000f6dc6: 4d46	mov	r5, sb
000f6dc8: 4446	mov	r4, r8
000f6dca: f0b4	push	{r4, r5, r6, r7}
000f6dcc: 041c	adds	r4, r0, #0
000f6dce: 0069	ldr	r0, [r0, #0x10]
000f6dd0: 9246	mov	sl, r2
000f6dd2: 0e1c	adds	r6, r1, #0
000f6dd4: 031c	adds	r3, r0, #0
000f6dd6: 0c33	adds	r3, #0xc
000f6dd8: 027b	ldrb	r2, [r0, #0xc]
000f6dda: d978	ldrb	r1, [r3, #3]
000f6ddc: 8146	mov	sb, r0
000f6dde: 1206	lsls	r2, r2, #0x18
000f6de0: 0a43	orrs	r2, r1
000f6de2: 5978	ldrb	r1, [r3, #1]
000f6de4: 9b78	ldrb	r3, [r3, #2]
000f6de6: 3068	ldr	r0, [r6]
000f6de8: 0904	lsls	r1, r1, #0x10
000f6dea: 0a43	orrs	r2, r1
000f6dec: 83b0	sub	sp, #0xc
000f6dee: 1b02	lsls	r3, r3, #8
000f6df0: 111c	adds	r1, r2, #0
000f6df2: 8046	mov	r8, r0
000f6df4: 1943	orrs	r1, r3
000f6df6: 0191	str	r1, [sp, #4]
000f6df8: 4bd0	beq	#0xf6e92
000f6dfa: 5346	mov	r3, sl
000f6dfc: 5a1e	subs	r2, r3, #1
000f6dfe: 9341	sbcs	r3, r2
000f6e00: 9844	add	r8, r3
000f6e02: 331c	adds	r3, r6, #0
000f6e04: 0198	ldr	r0, [sp, #4]
000f6e06: 4646	mov	r6, r8
000f6e08: 0027	movs	r7, #0
000f6e0a: a446	mov	ip, r4
000f6e0c: 9846	mov	r8, r3
000f6e0e: 04e0	b	#0xf6e1a
000f6e10: 9642	cmp	r6, r2
000f6e12: 53d9	bls	#0xf6ebc
000f6e14: 4f1c	adds	r7, r1, #1
000f6e16: b842	cmp	r0, r7
000f6e18: 22d9	bls	#0xf6e60
000f6e1a: c119	adds	r1, r0, r7
000f6e1c: 4908	lsrs	r1, r1, #1
000f6e1e: 4b00	lsls	r3, r1, #1
000f6e20: 5b18	adds	r3, r3, r1
000f6e22: 9b00	lsls	r3, r3, #2
000f6e24: 1033	adds	r3, #0x10
000f6e26: 4b44	add	r3, sb
000f6e28: 1d78	ldrb	r5, [r3]
000f6e2a: da78	ldrb	r2, [r3, #3]
000f6e2c: 1c79	ldrb	r4, [r3, #4]
000f6e2e: 2d06	lsls	r5, r5, #0x18
000f6e30: 1543	orrs	r5, r2
000f6e32: 5a78	ldrb	r2, [r3, #1]
000f6e34: 2406	lsls	r4, r4, #0x18
000f6e36: 1204	lsls	r2, r2, #0x10
000f6e38: 1543	orrs	r5, r2
000f6e3a: 9a78	ldrb	r2, [r3, #2]
000f6e3c: 1202	lsls	r2, r2, #8
000f6e3e: 1543	orrs	r5, r2
000f6e40: 0822	movs	r2, #8
000f6e42: d218	adds	r2, r2, r3
000f6e44: 9346	mov	fp, r2
000f6e46: 5a79	ldrb	r2, [r3, #5]
000f6e48: 1204	lsls	r2, r2, #0x10
000f6e4a: 1443	orrs	r4, r2
000f6e4c: da79	ldrb	r2, [r3, #7]
000f6e4e: 2243	orrs	r2, r4
000f6e50: 9c79	ldrb	r4, [r3, #6]
000f6e52: 2402	lsls	r4, r4, #8
000f6e54: 2243	orrs	r2, r4
000f6e56: ae42	cmp	r6, r5
000f6e58: dad2	bhs	#0xf6e10
000f6e5a: 081c	adds	r0, r1, #0
000f6e5c: b842	cmp	r0, r7
000f6e5e: dcd8	bhi	#0xf6e1a
000f6e60: 4346	mov	r3, r8
000f6e62: 6446	mov	r4, ip
000f6e64: b046	mov	r8, r6
000f6e66: 0025	movs	r5, #0
000f6e68: 1e1c	adds	r6, r3, #0
000f6e6a: 5046	mov	r0, sl
000f6e6c: 0028	cmp	r0, #0
000f6e6e: 11d0	beq	#0xf6e94
000f6e70: 9045	cmp	r8, r2
000f6e72: 03d9	bls	#0xf6e7c
000f6e74: 019a	ldr	r2, [sp, #4]
000f6e76: 0131	adds	r1, #1
000f6e78: 9142	cmp	r1, r2
000f6e7a: 0ad0	beq	#0xf6e92
000f6e7c: 0123	movs	r3, #1
000f6e7e: 2376	strb	r3, [r4, #0x18]
000f6e80: 4346	mov	r3, r8
000f6e82: e361	str	r3, [r4, #0x1c]
000f6e84: 6162	str	r1, [r4, #0x24]
000f6e86: 002d	cmp	r5, #0
000f6e88: 0cd0	beq	#0xf6ea4
000f6e8a: 2562	str	r5, [r4, #0x20]
000f6e8c: 4746	mov	r7, r8
000f6e8e: 3760	str	r7, [r6]
000f6e90: 00e0	b	#0xf6e94
000f6e92: 0025	movs	r5, #0
000f6e94: 03b0	add	sp, #0xc
000f6e96: 281c	adds	r0, r5, #0
000f6e98: 3cbc	pop	{r2, r3, r4, r5}
000f6e9a: 9046	mov	r8, r2
000f6e9c: 9946	mov	sb, r3
000f6e9e: a246	mov	sl, r4
000f6ea0: ab46	mov	fp, r5
000f6ea2: f0bd	pop	{r4, r5, r6, r7, pc}
000f6ea4: 201c	adds	r0, r4, #0
000f6ea6: fff731ff	bl	#0xf6d0c
000f6eaa: 237e	ldrb	r3, [r4, #0x18]
000f6eac: 002b	cmp	r3, #0
000f6eae: f1d0	beq	#0xf6e94
000f6eb0: 256a	ldr	r5, [r4, #0x20]
000f6eb2: 002d	cmp	r5, #0
000f6eb4: eed0	beq	#0xf6e94
000f6eb6: e469	ldr	r4, [r4, #0x1c]
000f6eb8: a046	mov	r8, r4
000f6eba: e7e7	b	#0xf6e8c
000f6ebc: 4346	mov	r3, r8
000f6ebe: b046	mov	r8, r6
000f6ec0: 4746	mov	r7, r8
000f6ec2: 5846	mov	r0, fp
000f6ec4: 1e1c	adds	r6, r3, #0
000f6ec6: 7b1b	subs	r3, r7, r5
000f6ec8: c578	ldrb	r5, [r0, #3]
000f6eca: 0078	ldrb	r0, [r0]
000f6ecc: 5f46	mov	r7, fp
000f6ece: 6446	mov	r4, ip
000f6ed0: 0006	lsls	r0, r0, #0x18
000f6ed2: 0543	orrs	r5, r0
000f6ed4: 7878	ldrb	r0, [r7, #1]
000f6ed6: 0004	lsls	r0, r0, #0x10
000f6ed8: 0543	orrs	r5, r0
000f6eda: b878	ldrb	r0, [r7, #2]
000f6edc: 0002	lsls	r0, r0, #8
000f6ede: 0543	orrs	r5, r0
000f6ee0: 5d19	adds	r5, r3, r5
000f6ee2: c2e7	b	#0xf6e6a
