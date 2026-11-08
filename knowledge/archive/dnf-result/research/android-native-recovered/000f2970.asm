000f2970: f0b5	push	{r4, r5, r6, r7, lr}
000f2972: 4746	mov	r7, r8
000f2974: 80b4	push	{r7}
000f2976: 1c1c	adds	r4, r3, #0
000f2978: 4368	ldr	r3, [r0, #4]
000f297a: 82b0	sub	sp, #8
000f297c: 061c	adds	r6, r0, #0
000f297e: 151c	adds	r5, r2, #0
000f2980: 002b	cmp	r3, #0
000f2982: 1fd1	bne	#0xf29c4
000f2984: 0129	cmp	r1, #1
000f2986: 00d9	bls	#0xf298a
000f2988: 0121	movs	r1, #1
000f298a: f368	ldr	r3, [r6, #0xc]
000f298c: 013b	subs	r3, #1
000f298e: 012b	cmp	r3, #1
000f2990: 18d8	bhi	#0xf29c4
000f2992: cf00	lsls	r7, r1, #3
000f2994: 7f18	adds	r7, r7, r1
000f2996: bf00	lsls	r7, r7, #2
000f2998: 1037	adds	r7, #0x10
000f299a: f719	adds	r7, r6, r7
000f299c: 002d	cmp	r5, #0
000f299e: 11d0	beq	#0xf29c4
000f29a0: 0020	movs	r0, #0
000f29a2: 8046	mov	r8, r0
000f29a4: 03e0	b	#0xf29ae
000f29a6: 013d	subs	r5, #1
000f29a8: 002d	cmp	r5, #0
000f29aa: 0bd0	beq	#0xf29c4
000f29ac: 0834	adds	r4, #8
000f29ae: 4046	mov	r0, r8
000f29b0: 0090	str	r0, [sp]
000f29b2: 2168	ldr	r1, [r4]
000f29b4: 6268	ldr	r2, [r4, #4]
000f29b6: 3368	ldr	r3, [r6]
000f29b8: 381c	adds	r0, r7, #0
000f29ba: fff743ff	bl	#0xf2844
000f29be: 0028	cmp	r0, #0
000f29c0: f1d0	beq	#0xf29a6
000f29c2: 7060	str	r0, [r6, #4]
000f29c4: 02b0	add	sp, #8
000f29c6: 04bc	pop	{r2}
000f29c8: 9046	mov	r8, r2
000f29ca: f0bd	pop	{r4, r5, r6, r7, pc}
