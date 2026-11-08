001080a0: 10b5	push	{r4, lr}
001080a2: d224	movs	r4, #0xd2
001080a4: 6400	lsls	r4, r4, #1
001080a6: 0059	ldr	r0, [r0, r4]
001080a8: 8900	lsls	r1, r1, #2
001080aa: 0958	ldr	r1, [r1, r0]
001080ac: 101c	adds	r0, r2, #0
001080ae: 1a1c	adds	r2, r3, #0
001080b0: e0f7a2f9	bl	#0xe83f8
001080b4: 0020	movs	r0, #0
001080b6: 10bd	pop	{r4, pc}
