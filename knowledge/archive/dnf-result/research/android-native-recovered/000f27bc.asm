000f27bc: 30b5	push	{r4, r5, lr}
000f27be: 4368	ldr	r3, [r0, #4]
000f27c0: 0731	adds	r1, #7
000f27c2: 85b0	sub	sp, #0x14
000f27c4: 0733	adds	r3, #7
000f27c6: 0025	movs	r5, #0
000f27c8: db08	lsrs	r3, r3, #3
000f27ca: c908	lsrs	r1, r1, #3
000f27cc: 041c	adds	r4, r0, #0
000f27ce: 0395	str	r5, [sp, #0xc]
000f27d0: 0020	movs	r0, #0
000f27d2: 8b42	cmp	r3, r1
000f27d4: 01d3	blo	#0xf27da
000f27d6: 05b0	add	sp, #0x14
000f27d8: 30bd	pop	{r4, r5, pc}
000f27da: cd1d	adds	r5, r1, #7
000f27dc: 0721	movs	r1, #7
000f27de: 8d43	bics	r5, r1
000f27e0: a168	ldr	r1, [r4, #8]
000f27e2: 101c	adds	r0, r2, #0
000f27e4: 1a1c	adds	r2, r3, #0
000f27e6: 0091	str	r1, [sp]
000f27e8: 03a9	add	r1, sp, #0xc
000f27ea: 0191	str	r1, [sp, #4]
000f27ec: 2b1c	adds	r3, r5, #0
000f27ee: 0121	movs	r1, #1
000f27f0: f6f76afd	bl	#0xe92c8
000f27f4: a060	str	r0, [r4, #8]
000f27f6: 0398	ldr	r0, [sp, #0xc]
000f27f8: 0028	cmp	r0, #0
000f27fa: ecd1	bne	#0xf27d6
000f27fc: ed00	lsls	r5, r5, #3
000f27fe: 6560	str	r5, [r4, #4]
000f2800: e9e7	b	#0xf27d6
