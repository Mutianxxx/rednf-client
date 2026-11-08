000f0350: f0b5	push	{r4, r5, r6, r7, lr}
000f0352: 5f46	mov	r7, fp
000f0354: 5646	mov	r6, sl
000f0356: 4d46	mov	r5, sb
000f0358: 4446	mov	r4, r8
000f035a: f0b4	push	{r4, r5, r6, r7}
000f035c: efb0	sub	sp, #0x1bc
000f035e: 64ac	add	r4, sp, #0x190
000f0360: 0391	str	r1, [sp, #0xc]
000f0362: 171c	adds	r7, r2, #0
000f0364: 9946	mov	sb, r3
000f0366: 0a1c	adds	r2, r1, #0
000f0368: 231c	adds	r3, r4, #0
000f036a: 061c	adds	r6, r0, #0
000f036c: 23ca	ldm	r2!, {r0, r1, r5}
000f036e: 23c3	stm	r3!, {r0, r1, r5}
000f0370: 23ca	ldm	r2!, {r0, r1, r5}
000f0372: 23c3	stm	r3!, {r0, r1, r5}
000f0374: 23ca	ldm	r2!, {r0, r1, r5}
000f0376: 23c3	stm	r3!, {r0, r1, r5}
000f0378: 0398	ldr	r0, [sp, #0xc]
000f037a: 0223	movs	r3, #2
000f037c: a360	str	r3, [r4, #8]
000f037e: 8368	ldr	r3, [r0, #8]
000f0380: 072b	cmp	r3, #7
000f0382: 43d0	beq	#0xf040c
000f0384: 092b	cmp	r3, #9
000f0386: 41d0	beq	#0xf040c
000f0388: 04a9	add	r1, sp, #0x10
000f038a: 301c	adds	r0, r6, #0
000f038c: 6dab	add	r3, sp, #0x1b4
000f038e: 2022	movs	r2, #0x20
000f0390: 8846	mov	r8, r1
000f0392: fef74bff	bl	#0xef22c
000f0396: 6d9b	ldr	r3, [sp, #0x1b4]
000f0398: a220	movs	r0, #0xa2
000f039a: 002b	cmp	r3, #0
000f039c: 2fdb	blt	#0xf03fe
000f039e: 039d	ldr	r5, [sp, #0xc]
000f03a0: aa69	ldr	r2, [r5, #0x18]
000f03a2: 9342	cmp	r3, r2
000f03a4: 35d8	bhi	#0xf0412
000f03a6: 039d	ldr	r5, [sp, #0xc]
000f03a8: 3068	ldr	r0, [r6]
000f03aa: b168	ldr	r1, [r6, #8]
000f03ac: aa68	ldr	r2, [r5, #8]
000f03ae: 8246	mov	sl, r0
000f03b0: 8b46	mov	fp, r1
000f03b2: 072a	cmp	r2, #7
000f03b4: 03d0	beq	#0xf03be
000f03b6: ea69	ldr	r2, [r5, #0x1c]
000f03b8: 002a	cmp	r2, #0
000f03ba: 2dd1	bne	#0xf0418
000f03bc: 6d9b	ldr	r3, [sp, #0x1b4]
000f03be: 002b	cmp	r3, #0
000f03c0: 18dd	ble	#0xf03f4
000f03c2: 0020	movs	r0, #0
000f03c4: 4546	mov	r5, r8
000f03c6: 8046	mov	r8, r0
000f03c8: 2b68	ldr	r3, [r5]
000f03ca: 4146	mov	r1, r8
000f03cc: 3a1c	adds	r2, r7, #0
000f03ce: 3360	str	r3, [r6]
000f03d0: 6b68	ldr	r3, [r5, #4]
000f03d2: 301c	adds	r0, r6, #0
000f03d4: 0091	str	r1, [sp]
000f03d6: b360	str	r3, [r6, #8]
000f03d8: 211c	adds	r1, r4, #0
000f03da: 4b46	mov	r3, sb
000f03dc: fff7a2fe	bl	#0xf0124
000f03e0: 227d	ldrb	r2, [r4, #0x14]
000f03e2: 2369	ldr	r3, [r4, #0x10]
000f03e4: 0c35	adds	r5, #0xc
000f03e6: d318	adds	r3, r2, r3
000f03e8: 2361	str	r3, [r4, #0x10]
000f03ea: 6d9b	ldr	r3, [sp, #0x1b4]
000f03ec: 013b	subs	r3, #1
000f03ee: 6d93	str	r3, [sp, #0x1b4]
000f03f0: 002b	cmp	r3, #0
000f03f2: e9dc	bgt	#0xf03c8
000f03f4: 5246	mov	r2, sl
000f03f6: 5b46	mov	r3, fp
000f03f8: 3260	str	r2, [r6]
000f03fa: b360	str	r3, [r6, #8]
000f03fc: 0020	movs	r0, #0
000f03fe: 6fb0	add	sp, #0x1bc
000f0400: 3cbc	pop	{r2, r3, r4, r5}
000f0402: 9046	mov	r8, r2
000f0404: 9946	mov	sb, r3
000f0406: a246	mov	sl, r4
000f0408: ab46	mov	fp, r5
000f040a: f0bd	pop	{r4, r5, r6, r7, pc}
000f040c: 0323	movs	r3, #3
000f040e: a360	str	r3, [r4, #8]
000f0410: bae7	b	#0xf0388
000f0412: 131c	adds	r3, r2, #0
000f0414: 6d92	str	r2, [sp, #0x1b4]
000f0416: c6e7	b	#0xf03a6
000f0418: 3968	ldr	r1, [r7]
000f041a: 8b54	strb	r3, [r1, r2]
000f041c: cee7	b	#0xf03bc
