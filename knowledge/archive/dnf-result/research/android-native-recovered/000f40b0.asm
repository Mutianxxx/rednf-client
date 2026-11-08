000f40b0: 30b5	push	{r4, r5, lr}
000f40b2: 0269	ldr	r2, [r0, #0x10]
000f40b4: 4369	ldr	r3, [r0, #0x14]
000f40b6: 013a	subs	r2, #1
000f40b8: d200	lsls	r2, r2, #3
000f40ba: 9a18	adds	r2, r3, r2
000f40bc: 9342	cmp	r3, r2
000f40be: 27d8	bhi	#0xf4110
000f40c0: d01a	subs	r0, r2, r3
000f40c2: 0011	asrs	r0, r0, #4
000f40c4: c000	lsls	r0, r0, #3
000f40c6: 1818	adds	r0, r3, r0
000f40c8: 0468	ldr	r4, [r0]
000f40ca: 0025	movs	r5, #0
000f40cc: 8c42	cmp	r4, r1
000f40ce: 0bd1	bne	#0xf40e8
000f40d0: 1ce0	b	#0xf410c
000f40d2: 031c	adds	r3, r0, #0
000f40d4: 0833	adds	r3, #8
000f40d6: 9a42	cmp	r2, r3
000f40d8: 12d3	blo	#0xf4100
000f40da: d01a	subs	r0, r2, r3
000f40dc: 0011	asrs	r0, r0, #4
000f40de: c000	lsls	r0, r0, #3
000f40e0: 1818	adds	r0, r3, r0
000f40e2: 0468	ldr	r4, [r0]
000f40e4: 8c42	cmp	r4, r1
000f40e6: 11d0	beq	#0xf410c
000f40e8: 6400	lsls	r4, r4, #1
000f40ea: 6408	lsrs	r4, r4, #1
000f40ec: 8c42	cmp	r4, r1
000f40ee: 0bd0	beq	#0xf4108
000f40f0: 9342	cmp	r3, r2
000f40f2: 05d0	beq	#0xf4100
000f40f4: a142	cmp	r1, r4
000f40f6: ecd8	bhi	#0xf40d2
000f40f8: 021c	adds	r2, r0, #0
000f40fa: 083a	subs	r2, #8
000f40fc: 9a42	cmp	r2, r3
000f40fe: ecd2	bhs	#0xf40da
000f4100: 002d	cmp	r5, #0
000f4102: 05d0	beq	#0xf4110
000f4104: 6868	ldr	r0, [r5, #4]
000f4106: 30bd	pop	{r4, r5, pc}
000f4108: 051c	adds	r5, r0, #0
000f410a: f1e7	b	#0xf40f0
000f410c: 051c	adds	r5, r0, #0
000f410e: f7e7	b	#0xf4100
000f4110: 0020	movs	r0, #0
000f4112: f8e7	b	#0xf4106
