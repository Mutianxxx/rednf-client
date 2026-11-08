000f00d4: f0b5	push	{r4, r5, r6, r7, lr}
000f00d6: 4746	mov	r7, r8
000f00d8: 80b4	push	{r7}
000f00da: 1f1c	adds	r7, r3, #0
000f00dc: 4423	movs	r3, #0x44
000f00de: c35c	ldrb	r3, [r0, r3]
000f00e0: 151c	adds	r5, r2, #0
000f00e2: 4469	ldr	r4, [r0, #0x14]
000f00e4: 002b	cmp	r3, #0
000f00e6: 17d0	beq	#0xf0118
000f00e8: 0222	movs	r2, #2
000f00ea: a35e	ldrsh	r3, [r4, r2]
000f00ec: 6668	ldr	r6, [r4, #4]
000f00ee: 081c	adds	r0, r1, #0
000f00f0: da00	lsls	r2, r3, #3
000f00f2: b618	adds	r6, r6, r2
000f00f4: a268	ldr	r2, [r4, #8]
000f00f6: d218	adds	r2, r2, r3
000f00f8: 9046	mov	r8, r2
000f00fa: f5f757fe	bl	#0xe5dac
000f00fe: 0014	asrs	r0, r0, #0x10
000f0100: 3060	str	r0, [r6]
000f0102: 281c	adds	r0, r5, #0
000f0104: f5f752fe	bl	#0xe5dac
000f0108: 7b1e	subs	r3, r7, #1
000f010a: 9f41	sbcs	r7, r3
000f010c: 0223	movs	r3, #2
000f010e: df1b	subs	r7, r3, r7
000f0110: 0014	asrs	r0, r0, #0x10
000f0112: 4346	mov	r3, r8
000f0114: 7060	str	r0, [r6, #4]
000f0116: 1f70	strb	r7, [r3]
000f0118: 6388	ldrh	r3, [r4, #2]
000f011a: 0133	adds	r3, #1
000f011c: 6380	strh	r3, [r4, #2]
000f011e: 04bc	pop	{r2}
000f0120: 9046	mov	r8, r2
000f0122: f0bd	pop	{r4, r5, r6, r7, pc}
