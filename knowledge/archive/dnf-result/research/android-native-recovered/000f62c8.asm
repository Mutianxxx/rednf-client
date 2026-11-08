000f62c8: 70b5	push	{r4, r5, r6, lr}
000f62ca: 8469	ldr	r4, [r0, #0x18]
000f62cc: 224b	ldr	r3, [pc, #0x88]
000f62ce: 051c	adds	r5, r0, #0
000f62d0: 9c42	cmp	r4, r3
000f62d2: 37d8	bhi	#0xf6344
000f62d4: 826a	ldr	r2, [r0, #0x28]
000f62d6: 0134	adds	r4, #1
000f62d8: 9442	cmp	r4, r2
000f62da: 21d3	blo	#0xf6320
000f62dc: e86a	ldr	r0, [r5, #0x2c]
000f62de: 696b	ldr	r1, [r5, #0x34]
000f62e0: 2e6b	ldr	r6, [r5, #0x30]
000f62e2: 8442	cmp	r4, r0
000f62e4: 12d8	bhi	#0xf630c
000f62e6: 0029	cmp	r1, #0
000f62e8: 1cd0	beq	#0xf6324
000f62ea: a31a	subs	r3, r4, r2
000f62ec: 5b00	lsls	r3, r3, #1
000f62ee: cb18	adds	r3, r1, r3
000f62f0: 1978	ldrb	r1, [r3]
000f62f2: 5a78	ldrb	r2, [r3, #1]
000f62f4: 0902	lsls	r1, r1, #8
000f62f6: 0a43	orrs	r2, r1
000f62f8: 04d0	beq	#0xf6304
000f62fa: 9219	adds	r2, r2, r6
000f62fc: 1204	lsls	r2, r2, #0x10
000f62fe: 120c	lsrs	r2, r2, #0x10
000f6300: 002a	cmp	r2, #0
000f6302: 25d1	bne	#0xf6350
000f6304: 0134	adds	r4, #1
000f6306: 0233	adds	r3, #2
000f6308: a042	cmp	r0, r4
000f630a: f1d2	bhs	#0xf62f0
000f630c: 696a	ldr	r1, [r5, #0x24]
000f630e: 281c	adds	r0, r5, #0
000f6310: 0131	adds	r1, #1
000f6312: fff75dff	bl	#0xf61d0
000f6316: 0028	cmp	r0, #0
000f6318: 14db	blt	#0xf6344
000f631a: aa6a	ldr	r2, [r5, #0x28]
000f631c: 9442	cmp	r4, r2
000f631e: ddd2	bhs	#0xf62dc
000f6320: 141c	adds	r4, r2, #0
000f6322: dbe7	b	#0xf62dc
000f6324: a319	adds	r3, r4, r6
000f6326: 1b04	lsls	r3, r3, #0x10
000f6328: 1b0c	lsrs	r3, r3, #0x10
000f632a: 002b	cmp	r3, #0
000f632c: 07d1	bne	#0xf633e
000f632e: 0134	adds	r4, #1
000f6330: a042	cmp	r0, r4
000f6332: ebd3	blo	#0xf630c
000f6334: a319	adds	r3, r4, r6
000f6336: 1b04	lsls	r3, r3, #0x10
000f6338: 1b0c	lsrs	r3, r3, #0x10
000f633a: 002b	cmp	r3, #0
000f633c: f7d0	beq	#0xf632e
000f633e: ac61	str	r4, [r5, #0x18]
000f6340: eb61	str	r3, [r5, #0x1c]
000f6342: 04e0	b	#0xf634e
000f6344: 0123	movs	r3, #1
000f6346: 5b42	rsbs	r3, r3, #0
000f6348: ab61	str	r3, [r5, #0x18]
000f634a: 0023	movs	r3, #0
000f634c: eb61	str	r3, [r5, #0x1c]
000f634e: 70bd	pop	{r4, r5, r6, pc}
000f6350: ac61	str	r4, [r5, #0x18]
000f6352: ea61	str	r2, [r5, #0x1c]
000f6354: fbe7	b	#0xf634e
000f6356: c046	mov	r8, r8
000f6358: feff	.byte	0xfe, 0xff
000f635a: 0000	movs	r0, r0
