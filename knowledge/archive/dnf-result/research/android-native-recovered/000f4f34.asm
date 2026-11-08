000f4f34: 10b5	push	{r4, lr}
000f4f36: 0028	cmp	r0, #0
000f4f38: 06d0	beq	#0xf4f48
000f4f3a: 094b	ldr	r3, [pc, #0x24]
000f4f3c: 9a42	cmp	r2, r3
000f4f3e: 04dc	bgt	#0xf4f4a
000f4f40: 0023	movs	r3, #0
000f4f42: 0360	str	r3, [r0]
000f4f44: 4360	str	r3, [r0, #4]
000f4f46: c360	str	r3, [r0, #0xc]
000f4f48: 10bd	pop	{r4, pc}
000f4f4a: 0029	cmp	r1, #0
000f4f4c: f8d0	beq	#0xf4f40
000f4f4e: 8124	movs	r4, #0x81
000f4f50: e400	lsls	r4, r4, #3
000f4f52: 0b19	adds	r3, r1, r4
000f4f54: 8a18	adds	r2, r1, r2
000f4f56: 0360	str	r3, [r0]
000f4f58: d31a	subs	r3, r2, r3
000f4f5a: 4360	str	r3, [r0, #4]
000f4f5c: c160	str	r1, [r0, #0xc]
000f4f5e: f3e7	b	#0xf4f48
000f4f60: 030c	lsrs	r3, r0, #0x10
000f4f62: 0000	movs	r0, r0
