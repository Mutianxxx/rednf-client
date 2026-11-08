000f4d5c: 30b5	push	{r4, r5, lr}
000f4d5e: 4468	ldr	r4, [r0, #4]
000f4d60: 9d1a	subs	r5, r3, r2
000f4d62: a542	cmp	r5, r4
000f4d64: 06da	bge	#0xf4d74
000f4d66: 6542	rsbs	r5, r4, #0
000f4d68: 013c	subs	r4, #1
000f4d6a: a218	adds	r2, r4, r2
000f4d6c: 2a40	ands	r2, r5
000f4d6e: 2b40	ands	r3, r5
000f4d70: 9a42	cmp	r2, r3
000f4d72: 00d0	beq	#0xf4d76
000f4d74: 30bd	pop	{r4, r5, pc}
000f4d76: 0468	ldr	r4, [r0]
000f4d78: c36b	ldr	r3, [r0, #0x3c]
000f4d7a: 2241	asrs	r2, r4
000f4d7c: 002a	cmp	r2, #0
000f4d7e: f9db	blt	#0xf4d74
000f4d80: 846e	ldr	r4, [r0, #0x68]
000f4d82: a242	cmp	r2, r4
000f4d84: f6da	bge	#0xf4d74
000f4d86: 006f	ldr	r0, [r0, #0x70]
000f4d88: cd10	asrs	r5, r1, #3
000f4d8a: 5b19	adds	r3, r3, r5
000f4d8c: 051c	adds	r5, r0, #0
000f4d8e: 5543	muls	r5, r2, r5
000f4d90: 5b1b	subs	r3, r3, r5
000f4d92: 0028	cmp	r0, #0
000f4d94: 03dd	ble	#0xf4d9e
000f4d96: 013c	subs	r4, #1
000f4d98: 021c	adds	r2, r0, #0
000f4d9a: 6243	muls	r2, r4, r2
000f4d9c: 9b18	adds	r3, r3, r2
000f4d9e: 0722	movs	r2, #7
000f4da0: 1140	ands	r1, r2
000f4da2: 8022	movs	r2, #0x80
000f4da4: 0a41	asrs	r2, r1
000f4da6: 111c	adds	r1, r2, #0
000f4da8: 1a78	ldrb	r2, [r3]
000f4daa: 1143	orrs	r1, r2
000f4dac: 1970	strb	r1, [r3]
000f4dae: e1e7	b	#0xf4d74
