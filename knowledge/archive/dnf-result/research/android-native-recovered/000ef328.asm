000ef328: 10b5	push	{r4, lr}
000ef32a: 8368	ldr	r3, [r0, #8]
000ef32c: 002b	cmp	r3, #0
000ef32e: 05d0	beq	#0xef33c
000ef330: 0269	ldr	r2, [r0, #0x10]
000ef332: 6c33	adds	r3, #0x6c
000ef334: 13ca	ldm	r2!, {r0, r1, r4}
000ef336: 13c3	stm	r3!, {r0, r1, r4}
000ef338: 03ca	ldm	r2!, {r0, r1}
000ef33a: 03c3	stm	r3!, {r0, r1}
000ef33c: 10bd	pop	{r4, pc}
