000f2804: 70b5	push	{r4, r5, r6, lr}
000f2806: 051c	adds	r5, r0, #0
000f2808: 0c1c	adds	r4, r1, #0
000f280a: 0020	movs	r0, #0
000f280c: 0029	cmp	r1, #0
000f280e: 0edb	blt	#0xf282e
000f2810: 2b68	ldr	r3, [r5]
000f2812: 9942	cmp	r1, r3
000f2814: 0cd2	bhs	#0xf2830
000f2816: aa68	ldr	r2, [r5, #8]
000f2818: e310	asrs	r3, r4, #3
000f281a: 0020	movs	r0, #0
000f281c: d318	adds	r3, r2, r3
000f281e: 0722	movs	r2, #7
000f2820: 1440	ands	r4, r2
000f2822: 8022	movs	r2, #0x80
000f2824: 2241	asrs	r2, r4
000f2826: 141c	adds	r4, r2, #0
000f2828: 1a78	ldrb	r2, [r3]
000f282a: 1443	orrs	r4, r2
000f282c: 1c70	strb	r4, [r3]
000f282e: 70bd	pop	{r4, r5, r6, pc}
000f2830: 4e1c	adds	r6, r1, #1
000f2832: 281c	adds	r0, r5, #0
000f2834: 311c	adds	r1, r6, #0
000f2836: fff7c1ff	bl	#0xf27bc
000f283a: 0028	cmp	r0, #0
000f283c: f7d1	bne	#0xf282e
000f283e: 2e60	str	r6, [r5]
000f2840: e9e7	b	#0xf2816
