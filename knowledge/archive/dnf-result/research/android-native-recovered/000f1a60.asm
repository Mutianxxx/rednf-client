000f1a60: f0b5	push	{r4, r5, r6, r7, lr}
000f1a62: 0368	ldr	r3, [r0]
000f1a64: 8268	ldr	r2, [r0, #8]
000f1a66: 9942	cmp	r1, r3
000f1a68: 25d2	bhs	#0xf1ab6
000f1a6a: cf00	lsls	r7, r1, #3
000f1a6c: 7f1a	subs	r7, r7, r1
000f1a6e: bf00	lsls	r7, r7, #2
000f1a70: d719	adds	r7, r2, r7
000f1a72: 3a69	ldr	r2, [r7, #0x10]
000f1a74: 0423	movs	r3, #4
000f1a76: 151c	adds	r5, r2, #0
000f1a78: 1d40	ands	r5, r3
000f1a7a: 1cd1	bne	#0xf1ab6
000f1a7c: 1343	orrs	r3, r2
000f1a7e: 3b61	str	r3, [r7, #0x10]
000f1a80: 4168	ldr	r1, [r0, #4]
000f1a82: 0469	ldr	r4, [r0, #0x10]
000f1a84: 7d61	str	r5, [r7, #0x14]
000f1a86: 0029	cmp	r1, #0
000f1a88: 0cd0	beq	#0xf1aa4
000f1a8a: 3b68	ldr	r3, [r7]
000f1a8c: 7d68	ldr	r5, [r7, #4]
000f1a8e: 9c46	mov	ip, r3
000f1a90: 6544	add	r5, ip
000f1a92: 08cc	ldm	r4!, {r3}
000f1a94: 1a68	ldr	r2, [r3]
000f1a96: aa42	cmp	r2, r5
000f1a98: 0edc	bgt	#0xf1ab8
000f1a9a: 5e68	ldr	r6, [r3, #4]
000f1a9c: 9219	adds	r2, r2, r6
000f1a9e: 6245	cmp	r2, ip
000f1aa0: 0adb	blt	#0xf1ab8
000f1aa2: 7b61	str	r3, [r7, #0x14]
000f1aa4: 4368	ldr	r3, [r0, #4]
000f1aa6: 0268	ldr	r2, [r0]
000f1aa8: 9342	cmp	r3, r2
000f1aaa: 04d2	bhs	#0xf1ab6
000f1aac: 0269	ldr	r2, [r0, #0x10]
000f1aae: 9900	lsls	r1, r3, #2
000f1ab0: 0133	adds	r3, #1
000f1ab2: 8f50	str	r7, [r1, r2]
000f1ab4: 4360	str	r3, [r0, #4]
000f1ab6: f0bd	pop	{r4, r5, r6, r7, pc}
000f1ab8: 0139	subs	r1, #1
000f1aba: 0029	cmp	r1, #0
000f1abc: e9d1	bne	#0xf1a92
000f1abe: f1e7	b	#0xf1aa4
