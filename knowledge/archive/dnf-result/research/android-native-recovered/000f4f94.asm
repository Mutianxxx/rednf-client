000f4f94: 10b5	push	{r4, lr}
000f4f96: 0024	movs	r4, #0
000f4f98: 131c	adds	r3, r2, #0
000f4f9a: 10c3	stm	r3!, {r4}
000f4f9c: 0433	adds	r3, #4
000f4f9e: 5460	str	r4, [r2, #4]
000f4fa0: 10c3	stm	r3!, {r4}
000f4fa2: 1c60	str	r4, [r3]
000f4fa4: 8c6c	ldr	r4, [r1, #0x48]
000f4fa6: 8369	ldr	r3, [r0, #0x18]
000f4fa8: 9c42	cmp	r4, r3
000f4faa: 00d0	beq	#0xf4fae
000f4fac: 10bd	pop	{r4, pc}
000f4fae: 081c	adds	r0, r1, #0
000f4fb0: 6c30	adds	r0, #0x6c
000f4fb2: 111c	adds	r1, r2, #0
000f4fb4: f2f756f9	bl	#0xe7264
000f4fb8: f8e7	b	#0xf4fac
