000f5ef4: 30b5	push	{r4, r5, lr}
000f5ef6: 83b0	sub	sp, #0xc
000f5ef8: 0023	movs	r3, #0
000f5efa: 0b60	str	r3, [r1]
000f5efc: 0c1c	adds	r4, r1, #0
000f5efe: 01aa	add	r2, sp, #4
000f5f00: 1821	movs	r1, #0x18
000f5f02: 051c	adds	r5, r0, #0
000f5f04: f2f750ff	bl	#0xe8da8
000f5f08: 019b	ldr	r3, [sp, #4]
000f5f0a: 002b	cmp	r3, #0
000f5f0c: 02d1	bne	#0xf5f14
000f5f0e: 8560	str	r5, [r0, #8]
000f5f10: 019b	ldr	r3, [sp, #4]
000f5f12: 2060	str	r0, [r4]
000f5f14: 03b0	add	sp, #0xc
000f5f16: 181c	adds	r0, r3, #0
000f5f18: 30bd	pop	{r4, r5, pc}
