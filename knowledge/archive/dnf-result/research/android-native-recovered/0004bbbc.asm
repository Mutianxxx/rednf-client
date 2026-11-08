0004bbbc: f8b5	push	{r3, r4, r5, r6, r7, lr}
0004bbbe: c469	ldr	r4, [r0, #0x1c]
0004bbc0: 061c	adds	r6, r0, #0
0004bbc2: 0d1c	adds	r5, r1, #0
0004bbc4: 636b	ldr	r3, [r4, #0x34]
0004bbc6: 002b	cmp	r3, #0
0004bbc8: 4ad0	beq	#0x4bc60
0004bbca: a26a	ldr	r2, [r4, #0x28]
0004bbcc: 002a	cmp	r2, #0
0004bbce: 1dd0	beq	#0x4bc0c
0004bbd0: 3169	ldr	r1, [r6, #0x10]
0004bbd2: 6d1a	subs	r5, r5, r1
0004bbd4: 9542	cmp	r5, r2
0004bbd6: 25d2	bhs	#0x4bc24
0004bbd8: 206b	ldr	r0, [r4, #0x30]
0004bbda: 171a	subs	r7, r2, r0
0004bbdc: af42	cmp	r7, r5
0004bbde: 2cd8	bhi	#0x4bc3a
0004bbe0: f168	ldr	r1, [r6, #0xc]
0004bbe2: 1818	adds	r0, r3, r0
0004bbe4: 3a1c	adds	r2, r7, #0
0004bbe6: 491b	subs	r1, r1, r5
0004bbe8: ed1b	subs	r5, r5, r7
0004bbea: e9f77cea	blx	#0x350e4
0004bbee: 002d	cmp	r5, #0
0004bbf0: 2bd1	bne	#0x4bc4a
0004bbf2: 226b	ldr	r2, [r4, #0x30]
0004bbf4: a36a	ldr	r3, [r4, #0x28]
0004bbf6: ba18	adds	r2, r7, r2
0004bbf8: 2263	str	r2, [r4, #0x30]
0004bbfa: 9a42	cmp	r2, r3
0004bbfc: 1fd0	beq	#0x4bc3e
0004bbfe: e26a	ldr	r2, [r4, #0x2c]
0004bc00: 0020	movs	r0, #0
0004bc02: 9342	cmp	r3, r2
0004bc04: 01d9	bls	#0x4bc0a
0004bc06: bf18	adds	r7, r7, r2
0004bc08: e762	str	r7, [r4, #0x2c]
0004bc0a: f8bd	pop	{r3, r4, r5, r6, r7, pc}
0004bc0c: 626a	ldr	r2, [r4, #0x24]
0004bc0e: 0127	movs	r7, #1
0004bc10: 0021	movs	r1, #0
0004bc12: 9740	lsls	r7, r2
0004bc14: a762	str	r7, [r4, #0x28]
0004bc16: 2163	str	r1, [r4, #0x30]
0004bc18: e162	str	r1, [r4, #0x2c]
0004bc1a: 3169	ldr	r1, [r6, #0x10]
0004bc1c: 3a1c	adds	r2, r7, #0
0004bc1e: 6d1a	subs	r5, r5, r1
0004bc20: 9542	cmp	r5, r2
0004bc22: d9d3	blo	#0x4bbd8
0004bc24: f168	ldr	r1, [r6, #0xc]
0004bc26: 181c	adds	r0, r3, #0
0004bc28: 891a	subs	r1, r1, r2
0004bc2a: e9f75cea	blx	#0x350e4
0004bc2e: 0023	movs	r3, #0
0004bc30: 2363	str	r3, [r4, #0x30]
0004bc32: a36a	ldr	r3, [r4, #0x28]
0004bc34: 0020	movs	r0, #0
0004bc36: e362	str	r3, [r4, #0x2c]
0004bc38: e7e7	b	#0x4bc0a
0004bc3a: 2f1c	adds	r7, r5, #0
0004bc3c: d0e7	b	#0x4bbe0
0004bc3e: e26a	ldr	r2, [r4, #0x2c]
0004bc40: 2563	str	r5, [r4, #0x30]
0004bc42: 0020	movs	r0, #0
0004bc44: 9342	cmp	r3, r2
0004bc46: ded8	bhi	#0x4bc06
0004bc48: dfe7	b	#0x4bc0a
0004bc4a: f168	ldr	r1, [r6, #0xc]
0004bc4c: 606b	ldr	r0, [r4, #0x34]
0004bc4e: 2a1c	adds	r2, r5, #0
0004bc50: 491b	subs	r1, r1, r5
0004bc52: e9f748ea	blx	#0x350e4
0004bc56: a36a	ldr	r3, [r4, #0x28]
0004bc58: 2563	str	r5, [r4, #0x30]
0004bc5a: 0020	movs	r0, #0
0004bc5c: e362	str	r3, [r4, #0x2c]
0004bc5e: d4e7	b	#0x4bc0a
0004bc60: 636a	ldr	r3, [r4, #0x24]
0004bc62: 0121	movs	r1, #1
0004bc64: 0122	movs	r2, #1
0004bc66: 9940	lsls	r1, r3
0004bc68: 806a	ldr	r0, [r0, #0x28]
0004bc6a: 336a	ldr	r3, [r6, #0x20]
0004bc6c: 9847	blx	r3
0004bc6e: 021c	adds	r2, r0, #0
0004bc70: 6063	str	r0, [r4, #0x34]
0004bc72: 031c	adds	r3, r0, #0
0004bc74: 0120	movs	r0, #1
0004bc76: 002a	cmp	r2, #0
0004bc78: a7d1	bne	#0x4bbca
0004bc7a: c6e7	b	#0x4bc0a
