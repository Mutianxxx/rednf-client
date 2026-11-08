000f6ef8: 70b5	push	{r4, r5, r6, lr}
000f6efa: c369	ldr	r3, [r0, #0x1c]
000f6efc: 041c	adds	r4, r0, #0
000f6efe: 0d1c	adds	r5, r1, #0
000f6f00: 0020	movs	r0, #0
000f6f02: 5a1c	adds	r2, r3, #1
000f6f04: 0ad0	beq	#0xf6f1c
000f6f06: 227e	ldrb	r2, [r4, #0x18]
000f6f08: 002a	cmp	r2, #0
000f6f0a: 02d0	beq	#0xf6f12
000f6f0c: 0a68	ldr	r2, [r1]
000f6f0e: 9342	cmp	r3, r2
000f6f10: 05d0	beq	#0xf6f1e
000f6f12: 201c	adds	r0, r4, #0
000f6f14: 291c	adds	r1, r5, #0
000f6f16: 0122	movs	r2, #1
000f6f18: fff752ff	bl	#0xf6dc0
000f6f1c: 70bd	pop	{r4, r5, r6, pc}
000f6f1e: 201c	adds	r0, r4, #0
000f6f20: fff7f4fe	bl	#0xf6d0c
000f6f24: 237e	ldrb	r3, [r4, #0x18]
000f6f26: 0020	movs	r0, #0
000f6f28: 002b	cmp	r3, #0
000f6f2a: f7d0	beq	#0xf6f1c
000f6f2c: 206a	ldr	r0, [r4, #0x20]
000f6f2e: 0028	cmp	r0, #0
000f6f30: f4d0	beq	#0xf6f1c
000f6f32: e369	ldr	r3, [r4, #0x1c]
000f6f34: 2b60	str	r3, [r5]
000f6f36: f1e7	b	#0xf6f1c
