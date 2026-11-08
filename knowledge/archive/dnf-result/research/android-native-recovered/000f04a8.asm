000f04a8: f8b5	push	{r3, r4, r5, r6, r7, lr}
000f04aa: 0e1c	adds	r6, r1, #0
000f04ac: 0121	movs	r1, #1
000f04ae: 051c	adds	r5, r0, #0
000f04b0: 171c	adds	r7, r2, #0
000f04b2: fff7e5ff	bl	#0xf0480
000f04b6: 041e	subs	r4, r0, #0
000f04b8: 05d1	bne	#0xf04c6
000f04ba: 281c	adds	r0, r5, #0
000f04bc: 311c	adds	r1, r6, #0
000f04be: 3a1c	adds	r2, r7, #0
000f04c0: 0123	movs	r3, #1
000f04c2: fff707fe	bl	#0xf00d4
000f04c6: 201c	adds	r0, r4, #0
000f04c8: f8bd	pop	{r3, r4, r5, r6, r7, pc}
