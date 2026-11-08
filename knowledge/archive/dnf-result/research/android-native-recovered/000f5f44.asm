000f5f44: f0b5	push	{r4, r5, r6, r7, lr}
000f5f46: 041c	adds	r4, r0, #0
000f5f48: 059e	ldr	r6, [sp, #0x14]
000f5f4a: d834	adds	r4, #0xd8
000f5f4c: 0029	cmp	r1, #0
000f5f4e: 02d0	beq	#0xf5f56
000f5f50: 9621	movs	r1, #0x96
000f5f52: 4900	lsls	r1, r1, #1
000f5f54: 4418	adds	r4, r0, r1
000f5f56: 618c	ldrh	r1, [r4, #0x22]
000f5f58: 0029	cmp	r1, #0
000f5f5a: 14d0	beq	#0xf5f86
000f5f5c: 676a	ldr	r7, [r4, #0x24]
000f5f5e: 002f	cmp	r7, #0
000f5f60: 11d0	beq	#0xf5f86
000f5f62: 8425	movs	r5, #0x84
000f5f64: 6d00	lsls	r5, r5, #1
000f5f66: 405b	ldrh	r0, [r0, r5]
000f5f68: 9042	cmp	r0, r2
000f5f6a: 0cd9	bls	#0xf5f86
000f5f6c: 8a42	cmp	r2, r1
000f5f6e: 0fd3	blo	#0xf5f90
000f5f70: a06a	ldr	r0, [r4, #0x28]
000f5f72: 521a	subs	r2, r2, r1
000f5f74: 5200	lsls	r2, r2, #1
000f5f76: 125a	ldrh	r2, [r2, r0]
000f5f78: 0139	subs	r1, #1
000f5f7a: 8900	lsls	r1, r1, #2
000f5f7c: 1a80	strh	r2, [r3]
000f5f7e: 636a	ldr	r3, [r4, #0x24]
000f5f80: cb5a	ldrh	r3, [r1, r3]
000f5f82: 3380	strh	r3, [r6]
000f5f84: 02e0	b	#0xf5f8c
000f5f86: 0022	movs	r2, #0
000f5f88: 3280	strh	r2, [r6]
000f5f8a: 1a80	strh	r2, [r3]
000f5f8c: 0020	movs	r0, #0
000f5f8e: f0bd	pop	{r4, r5, r6, r7, pc}
000f5f90: 9200	lsls	r2, r2, #2
000f5f92: bf18	adds	r7, r7, r2
000f5f94: 7a88	ldrh	r2, [r7, #2]
000f5f96: 1a80	strh	r2, [r3]
000f5f98: 3b88	ldrh	r3, [r7]
000f5f9a: 3380	strh	r3, [r6]
000f5f9c: f6e7	b	#0xf5f8c
