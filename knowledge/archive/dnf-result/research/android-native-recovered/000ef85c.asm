000ef85c: 10b5	push	{r4, lr}
000ef85e: 0368	ldr	r3, [r0]
000ef860: 041c	adds	r4, r0, #0
000ef862: 6169	ldr	r1, [r4, #0x14]
000ef864: 586e	ldr	r0, [r3, #0x64]
000ef866: f8f71ffc	bl	#0xe80a8
000ef86a: 0023	movs	r3, #0
000ef86c: 6361	str	r3, [r4, #0x14]
000ef86e: 2361	str	r3, [r4, #0x10]
000ef870: 10bd	pop	{r4, pc}
