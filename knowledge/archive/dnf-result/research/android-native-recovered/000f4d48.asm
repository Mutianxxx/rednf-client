000f4d48: 10b5	push	{r4, lr}
000f4d4a: 9423	movs	r3, #0x94
000f4d4c: 9c22	movs	r2, #0x9c
000f4d4e: 815e	ldrsh	r1, [r0, r2]
000f4d50: c258	ldr	r2, [r0, r3]
000f4d52: 8a18	adds	r2, r1, r2
000f4d54: c250	str	r2, [r0, r3]
000f4d56: 10bd	pop	{r4, pc}
