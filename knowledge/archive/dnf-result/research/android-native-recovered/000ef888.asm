000ef888: 70b5	push	{r4, r5, r6, lr}
000ef88a: c268	ldr	r2, [r0, #0xc]
000ef88c: 0b4b	ldr	r3, [pc, #0x2c]
000ef88e: 041c	adds	r4, r0, #0
000ef890: 056a	ldr	r5, [r0, #0x20]
000ef892: 9a42	cmp	r2, r3
000ef894: 00d0	beq	#0xef898
000ef896: 70bd	pop	{r4, r5, r6, pc}
000ef898: 0026	movs	r6, #0
000ef89a: 0168	ldr	r1, [r0]
000ef89c: 281c	adds	r0, r5, #0
000ef89e: f8f703fc	bl	#0xe80a8
000ef8a2: a169	ldr	r1, [r4, #0x18]
000ef8a4: 281c	adds	r0, r5, #0
000ef8a6: 2660	str	r6, [r4]
000ef8a8: f8f7fefb	bl	#0xe80a8
000ef8ac: a661	str	r6, [r4, #0x18]
000ef8ae: e169	ldr	r1, [r4, #0x1c]
000ef8b0: 281c	adds	r0, r5, #0
000ef8b2: f8f7f9fb	bl	#0xe80a8
000ef8b6: e661	str	r6, [r4, #0x1c]
000ef8b8: e660	str	r6, [r4, #0xc]
000ef8ba: ece7	b	#0xef896
000ef8bc: efbe	bkpt	#0xef
000ef8be: adde	udf	#0xad
