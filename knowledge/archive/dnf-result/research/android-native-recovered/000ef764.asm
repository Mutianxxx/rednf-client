000ef764: f0b5	push	{r4, r5, r6, r7, lr}
000ef766: 5f46	mov	r7, fp
000ef768: 5646	mov	r6, sl
000ef76a: 4d46	mov	r5, sb
000ef76c: 4446	mov	r4, r8
000ef76e: f0b4	push	{r4, r5, r6, r7}
000ef770: 85b0	sub	sp, #0x14
000ef772: 0193	str	r3, [sp, #4]
000ef774: 0391	str	r1, [sp, #0xc]
000ef776: 041c	adds	r4, r0, #0
000ef778: 0eab	add	r3, sp, #0x38
000ef77a: 8168	ldr	r1, [r0, #8]
000ef77c: 1d78	ldrb	r5, [r3]
000ef77e: 9046	mov	r8, r2
000ef780: fff74afb	bl	#0xeee18
000ef784: 2168	ldr	r1, [r4]
000ef786: a368	ldr	r3, [r4, #8]
000ef788: 0020	movs	r0, #0
000ef78a: 9942	cmp	r1, r3
000ef78c: 05d2	bhs	#0xef79a
000ef78e: 002d	cmp	r5, #0
000ef790: 0bd0	beq	#0xef7aa
000ef792: 0a78	ldrb	r2, [r1]
000ef794: 3c2a	cmp	r2, #0x3c
000ef796: 07d0	beq	#0xef7a8
000ef798: 0320	movs	r0, #3
000ef79a: 05b0	add	sp, #0x14
000ef79c: 3cbc	pop	{r2, r3, r4, r5}
000ef79e: 9046	mov	r8, r2
000ef7a0: 9946	mov	sb, r3
000ef7a2: a246	mov	sl, r4
000ef7a4: ab46	mov	fp, r5
000ef7a6: f0bd	pop	{r4, r5, r6, r7, pc}
000ef7a8: 0131	adds	r1, #1
000ef7aa: 4046	mov	r0, r8
000ef7ac: 4200	lsls	r2, r0, #1
000ef7ae: 581a	subs	r0, r3, r1
000ef7b0: 9042	cmp	r0, r2
000ef7b2: 4fd8	bhi	#0xef854
000ef7b4: 0023	movs	r3, #0
000ef7b6: 0028	cmp	r0, #0
000ef7b8: 3ed0	beq	#0xef838
000ef7ba: 274e	ldr	r6, [pc, #0x9c]
000ef7bc: 0123	movs	r3, #1
000ef7be: 9c46	mov	ip, r3
000ef7c0: 8023	movs	r3, #0x80
000ef7c2: b146	mov	sb, r6
000ef7c4: 0022	movs	r2, #0
000ef7c6: 7f27	movs	r7, #0x7f
000ef7c8: 5e00	lsls	r6, r3, #1
000ef7ca: 9046	mov	r8, r2
000ef7cc: f944	add	sb, pc
000ef7ce: bb46	mov	fp, r7
000ef7d0: b246	mov	sl, r6
000ef7d2: 8f5c	ldrb	r7, [r1, r2]
000ef7d4: 202f	cmp	r7, #0x20
000ef7d6: 20d0	beq	#0xef81a
000ef7d8: 0a2f	cmp	r7, #0xa
000ef7da: 1ed0	beq	#0xef81a
000ef7dc: 0d2f	cmp	r7, #0xd
000ef7de: 1cd0	beq	#0xef81a
000ef7e0: 0c2f	cmp	r7, #0xc
000ef7e2: 1ad0	beq	#0xef81a
000ef7e4: 092f	cmp	r7, #9
000ef7e6: 18d0	beq	#0xef81a
000ef7e8: 002f	cmp	r7, #0
000ef7ea: 16d0	beq	#0xef81a
000ef7ec: 7f2f	cmp	r7, #0x7f
000ef7ee: 17d8	bhi	#0xef820
000ef7f0: 5b46	mov	r3, fp
000ef7f2: 1f40	ands	r7, r3
000ef7f4: 4e46	mov	r6, sb
000ef7f6: f75d	ldrb	r7, [r6, r7]
000ef7f8: 3b06	lsls	r3, r7, #0x18
000ef7fa: 1b16	asrs	r3, r3, #0x18
000ef7fc: 0f2b	cmp	r3, #0xf
000ef7fe: 0fd8	bhi	#0xef820
000ef800: 6746	mov	r7, ip
000ef802: 3f01	lsls	r7, r7, #4
000ef804: 1f43	orrs	r7, r3
000ef806: 5346	mov	r3, sl
000ef808: bc46	mov	ip, r7
000ef80a: 1f42	tst	r7, r3
000ef80c: 05d0	beq	#0xef81a
000ef80e: 039e	ldr	r6, [sp, #0xc]
000ef810: 4346	mov	r3, r8
000ef812: f754	strb	r7, [r6, r3]
000ef814: 0126	movs	r6, #1
000ef816: b044	add	r8, r6
000ef818: b446	mov	ip, r6
000ef81a: 0132	adds	r2, #1
000ef81c: 8242	cmp	r2, r0
000ef81e: d8d1	bne	#0xef7d2
000ef820: 6746	mov	r7, ip
000ef822: 8918	adds	r1, r1, r2
000ef824: 4346	mov	r3, r8
000ef826: 012f	cmp	r7, #1
000ef828: 06d0	beq	#0xef838
000ef82a: 039a	ldr	r2, [sp, #0xc]
000ef82c: 6046	mov	r0, ip
000ef82e: 0301	lsls	r3, r0, #4
000ef830: 4646	mov	r6, r8
000ef832: 9355	strb	r3, [r2, r6]
000ef834: 4346	mov	r3, r8
000ef836: 0133	adds	r3, #1
000ef838: 019f	ldr	r7, [sp, #4]
000ef83a: 3b60	str	r3, [r7]
000ef83c: 002d	cmp	r5, #0
000ef83e: 06d0	beq	#0xef84e
000ef840: a368	ldr	r3, [r4, #8]
000ef842: 8b42	cmp	r3, r1
000ef844: 02d9	bls	#0xef84c
000ef846: 0b78	ldrb	r3, [r1]
000ef848: 3e2b	cmp	r3, #0x3e
000ef84a: a5d1	bne	#0xef798
000ef84c: 0131	adds	r1, #1
000ef84e: 2160	str	r1, [r4]
000ef850: 0020	movs	r0, #0
000ef852: a2e7	b	#0xef79a
000ef854: 101c	adds	r0, r2, #0
000ef856: ade7	b	#0xef7b4
000ef858: f08f	ldrh	r0, [r6, #0x3e]
000ef85a: 0400	movs	r4, r0
