000f0078: 70b5	push	{r4, r5, r6, lr}
000f007a: 0568	ldr	r5, [r0]
000f007c: 82b0	sub	sp, #8
000f007e: 041c	adds	r4, r0, #0
000f0080: 066a	ldr	r6, [r0, #0x20]
000f0082: 002d	cmp	r5, #0
000f0084: 08d0	beq	#0xf0098
000f0086: 4168	ldr	r1, [r0, #4]
000f0088: 01aa	add	r2, sp, #4
000f008a: 301c	adds	r0, r6, #0
000f008c: f8f78cfe	bl	#0xe8da8
000f0090: 019b	ldr	r3, [sp, #4]
000f0092: 2060	str	r0, [r4]
000f0094: 002b	cmp	r3, #0
000f0096: 01d0	beq	#0xf009c
000f0098: 02b0	add	sp, #8
000f009a: 70bd	pop	{r4, r5, r6, pc}
000f009c: 291c	adds	r1, r5, #0
000f009e: 6268	ldr	r2, [r4, #4]
000f00a0: 45f720e8	blx	#0x350e4
000f00a4: 2169	ldr	r1, [r4, #0x10]
000f00a6: a369	ldr	r3, [r4, #0x18]
000f00a8: 2068	ldr	r0, [r4]
000f00aa: 8900	lsls	r1, r1, #2
000f00ac: 5918	adds	r1, r3, r1
000f00ae: 401b	subs	r0, r0, r5
000f00b0: 8b42	cmp	r3, r1
000f00b2: 07d2	bhs	#0xf00c4
000f00b4: 1a68	ldr	r2, [r3]
000f00b6: 002a	cmp	r2, #0
000f00b8: 01d0	beq	#0xf00be
000f00ba: 1218	adds	r2, r2, r0
000f00bc: 1a60	str	r2, [r3]
000f00be: 0433	adds	r3, #4
000f00c0: 9942	cmp	r1, r3
000f00c2: f7d8	bhi	#0xf00b4
000f00c4: 6368	ldr	r3, [r4, #4]
000f00c6: 301c	adds	r0, r6, #0
000f00c8: 291c	adds	r1, r5, #0
000f00ca: a360	str	r3, [r4, #8]
000f00cc: f7f7ecff	bl	#0xe80a8
000f00d0: e2e7	b	#0xf0098
