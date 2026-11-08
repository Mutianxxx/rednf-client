000f4a84: 30b5	push	{r4, r5, lr}
000f4a86: 0368	ldr	r3, [r0]
000f4a88: 002b	cmp	r3, #0
000f4a8a: 2dd0	beq	#0xf4ae8
000f4a8c: 0825	movs	r5, #8
000f4a8e: 9968	ldr	r1, [r3, #8]
000f4a90: dc68	ldr	r4, [r3, #0xc]
000f4a92: 0a68	ldr	r2, [r1]
000f4a94: 1a60	str	r2, [r3]
000f4a96: 0422	movs	r2, #4
000f4a98: 2542	tst	r5, r4
000f4a9a: 00d1	bne	#0xf4a9e
000f4a9c: 5242	rsbs	r2, r2, #0
000f4a9e: 8a18	adds	r2, r1, r2
000f4aa0: 9a60	str	r2, [r3, #8]
000f4aa2: 1a69	ldr	r2, [r3, #0x10]
000f4aa4: 013a	subs	r2, #1
000f4aa6: 1a61	str	r2, [r3, #0x10]
000f4aa8: 5b68	ldr	r3, [r3, #4]
000f4aaa: 002b	cmp	r3, #0
000f4aac: efd1	bne	#0xf4a8e
000f4aae: 0268	ldr	r2, [r0]
000f4ab0: 002a	cmp	r2, #0
000f4ab2: 19d0	beq	#0xf4ae8
000f4ab4: 5368	ldr	r3, [r2, #4]
000f4ab6: 002b	cmp	r3, #0
000f4ab8: 16d0	beq	#0xf4ae8
000f4aba: 051c	adds	r5, r0, #0
000f4abc: 07e0	b	#0xf4ace
000f4abe: 5168	ldr	r1, [r2, #4]
000f4ac0: 0029	cmp	r1, #0
000f4ac2: 11d0	beq	#0xf4ae8
000f4ac4: 4b68	ldr	r3, [r1, #4]
000f4ac6: 151d	adds	r5, r2, #4
000f4ac8: 002b	cmp	r3, #0
000f4aca: 0dd0	beq	#0xf4ae8
000f4acc: 0a1c	adds	r2, r1, #0
000f4ace: 1468	ldr	r4, [r2]
000f4ad0: 1968	ldr	r1, [r3]
000f4ad2: 8c42	cmp	r4, r1
000f4ad4: f3dd	ble	#0xf4abe
000f4ad6: 2b60	str	r3, [r5]
000f4ad8: 5968	ldr	r1, [r3, #4]
000f4ada: 051c	adds	r5, r0, #0
000f4adc: 5160	str	r1, [r2, #4]
000f4ade: 5a60	str	r2, [r3, #4]
000f4ae0: 0168	ldr	r1, [r0]
000f4ae2: 4b68	ldr	r3, [r1, #4]
000f4ae4: 002b	cmp	r3, #0
000f4ae6: f1d1	bne	#0xf4acc
000f4ae8: 30bd	pop	{r4, r5, pc}
