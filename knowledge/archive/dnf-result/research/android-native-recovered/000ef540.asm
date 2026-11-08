000ef540: 10b5	push	{r4, lr}
000ef542: 0268	ldr	r2, [r0]
000ef544: f223	movs	r3, #0xf2
000ef546: 5b00	lsls	r3, r3, #1
000ef548: d358	ldr	r3, [r2, r3]
000ef54a: db68	ldr	r3, [r3, #0xc]
000ef54c: 9847	blx	r3
000ef54e: 10bd	pop	{r4, pc}
