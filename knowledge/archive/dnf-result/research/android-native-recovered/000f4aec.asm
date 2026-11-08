000f4aec: 30b5	push	{r4, r5, lr}
000f4aee: 036f	ldr	r3, [r0, #0x70]
000f4af0: 9c22	movs	r2, #0x9c
000f4af2: 5c42	rsbs	r4, r3, #0
000f4af4: 8452	strh	r4, [r0, r2]
000f4af6: 0024	movs	r4, #0
000f4af8: 0a5f	ldrsh	r2, [r1, r4]
000f4afa: 5242	rsbs	r2, r2, #0
000f4afc: 191c	adds	r1, r3, #0
000f4afe: 5143	muls	r1, r2, r1
000f4b00: 9422	movs	r2, #0x94
000f4b02: 8150	str	r1, [r0, r2]
000f4b04: 002b	cmp	r3, #0
000f4b06: 05dd	ble	#0xf4b14
000f4b08: 856e	ldr	r5, [r0, #0x68]
000f4b0a: 013d	subs	r5, #1
000f4b0c: 1c1c	adds	r4, r3, #0
000f4b0e: 6c43	muls	r4, r5, r4
000f4b10: 0919	adds	r1, r1, r4
000f4b12: 8150	str	r1, [r0, r2]
000f4b14: 0023	movs	r3, #0
000f4b16: 9e22	movs	r2, #0x9e
000f4b18: 8352	strh	r3, [r0, r2]
000f4b1a: a022	movs	r2, #0xa0
000f4b1c: 8352	strh	r3, [r0, r2]
000f4b1e: 30bd	pop	{r4, r5, pc}
