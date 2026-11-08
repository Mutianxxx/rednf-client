000ef530: 10b5	push	{r4, lr}
000ef532: 0268	ldr	r2, [r0]
000ef534: f223	movs	r3, #0xf2
000ef536: 5b00	lsls	r3, r3, #1
000ef538: d358	ldr	r3, [r2, r3]
000ef53a: 9b68	ldr	r3, [r3, #8]
000ef53c: 9847	blx	r3
000ef53e: 10bd	pop	{r4, pc}
