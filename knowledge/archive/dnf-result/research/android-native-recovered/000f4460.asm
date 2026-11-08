000f4460: 10b5	push	{r4, lr}
000f4462: 846d	ldr	r4, [r0, #0x58]
000f4464: 836a	ldr	r3, [r0, #0x28]
000f4466: a268	ldr	r2, [r4, #8]
000f4468: 9a1a	subs	r2, r3, r2
000f446a: 9210	asrs	r2, r2, #2
000f446c: 002a	cmp	r2, #0
000f446e: 2edb	blt	#0xf44ce
000f4470: 002a	cmp	r2, #0
000f4472: 14d0	beq	#0xf449e
000f4474: 2261	str	r2, [r4, #0x10]
000f4476: 0029	cmp	r1, #0
000f4478: 1dd1	bne	#0xf44b6
000f447a: 836a	ldr	r3, [r0, #0x28]
000f447c: 826d	ldr	r2, [r0, #0x58]
000f447e: 191c	adds	r1, r3, #0
000f4480: 2031	adds	r1, #0x20
000f4482: 8162	str	r1, [r0, #0x28]
000f4484: 0021	movs	r1, #0
000f4486: 8365	str	r3, [r0, #0x58]
000f4488: 1961	str	r1, [r3, #0x10]
000f448a: 836d	ldr	r3, [r0, #0x58]
000f448c: 816a	ldr	r1, [r0, #0x28]
000f448e: 9960	str	r1, [r3, #8]
000f4490: 836d	ldr	r3, [r0, #0x58]
000f4492: d361	str	r3, [r2, #0x1c]
000f4494: 5423	movs	r3, #0x54
000f4496: c25a	ldrh	r2, [r0, r3]
000f4498: 0132	adds	r2, #1
000f449a: c252	strh	r2, [r0, r3]
000f449c: 836a	ldr	r3, [r0, #0x28]
000f449e: 426a	ldr	r2, [r0, #0x24]
000f44a0: 9a42	cmp	r2, r3
000f44a2: 04d9	bls	#0xf44ae
000f44a4: 0022	movs	r2, #0
000f44a6: 5723	movs	r3, #0x57
000f44a8: c254	strb	r2, [r0, r3]
000f44aa: 0020	movs	r0, #0
000f44ac: 10bd	pop	{r4, pc}
000f44ae: 6223	movs	r3, #0x62
000f44b0: c362	str	r3, [r0, #0x2c]
000f44b2: 0120	movs	r0, #1
000f44b4: fae7	b	#0xf44ac
000f44b6: 836d	ldr	r3, [r0, #0x58]
000f44b8: da68	ldr	r2, [r3, #0xc]
000f44ba: 1107	lsls	r1, r2, #0x1c
000f44bc: 03d5	bpl	#0xf44c6
000f44be: 1021	movs	r1, #0x10
000f44c0: 0a43	orrs	r2, r1
000f44c2: da60	str	r2, [r3, #0xc]
000f44c4: d9e7	b	#0xf447a
000f44c6: 2021	movs	r1, #0x20
000f44c8: 0a43	orrs	r2, r1
000f44ca: da60	str	r2, [r3, #0xc]
000f44cc: d5e7	b	#0xf447a
000f44ce: 6323	movs	r3, #0x63
000f44d0: c362	str	r3, [r0, #0x2c]
000f44d2: 0120	movs	r0, #1
000f44d4: eae7	b	#0xf44ac
