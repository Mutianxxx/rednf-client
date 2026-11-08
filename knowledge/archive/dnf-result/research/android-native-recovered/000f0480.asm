000f0480: 10b5	push	{r4, lr}
000f0482: 0029	cmp	r1, #0
000f0484: 09d0	beq	#0xf049a
000f0486: c068	ldr	r0, [r0, #0xc]
000f0488: 3a23	movs	r3, #0x3a
000f048a: c25e	ldrsh	r2, [r0, r3]
000f048c: 1624	movs	r4, #0x16
000f048e: 035f	ldrsh	r3, [r0, r4]
000f0490: d218	adds	r2, r2, r3
000f0492: 4368	ldr	r3, [r0, #4]
000f0494: 8a18	adds	r2, r1, r2
000f0496: 9a42	cmp	r2, r3
000f0498: 01d8	bhi	#0xf049e
000f049a: 0020	movs	r0, #0
000f049c: 10bd	pop	{r4, pc}
000f049e: 0022	movs	r2, #0
000f04a0: faf7befe	bl	#0xeb220
000f04a4: fae7	b	#0xf049c
