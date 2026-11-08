000ef4b0: 30b5	push	{r4, r5, lr}
000ef4b2: 0c68	ldr	r4, [r1]
000ef4b4: 0369	ldr	r3, [r0, #0x10]
000ef4b6: 0134	adds	r4, #1
000ef4b8: 9c42	cmp	r4, r3
000ef4ba: 00d2	bhs	#0xef4be
000ef4bc: 1c1c	adds	r4, r3, #0
000ef4be: 4569	ldr	r5, [r0, #0x14]
000ef4c0: 5d19	adds	r5, r3, r5
000ef4c2: a542	cmp	r5, r4
000ef4c4: 14d9	bls	#0xef4f0
000ef4c6: 8269	ldr	r2, [r0, #0x18]
000ef4c8: 6300	lsls	r3, r4, #1
000ef4ca: 9b5a	ldrh	r3, [r3, r2]
000ef4cc: 181e	subs	r0, r3, #0
000ef4ce: 0dd1	bne	#0xef4ec
000ef4d0: 631c	adds	r3, r4, #1
000ef4d2: 5800	lsls	r0, r3, #1
000ef4d4: 1218	adds	r2, r2, r0
000ef4d6: 04e0	b	#0xef4e2
000ef4d8: 1088	ldrh	r0, [r2]
000ef4da: 0232	adds	r2, #2
000ef4dc: 0028	cmp	r0, #0
000ef4de: 05d1	bne	#0xef4ec
000ef4e0: 0133	adds	r3, #1
000ef4e2: 1c1c	adds	r4, r3, #0
000ef4e4: a542	cmp	r5, r4
000ef4e6: f7d8	bhi	#0xef4d8
000ef4e8: 0020	movs	r0, #0
000ef4ea: 0024	movs	r4, #0
000ef4ec: 0c60	str	r4, [r1]
000ef4ee: 30bd	pop	{r4, r5, pc}
000ef4f0: 0024	movs	r4, #0
000ef4f2: 0020	movs	r0, #0
000ef4f4: fae7	b	#0xef4ec
